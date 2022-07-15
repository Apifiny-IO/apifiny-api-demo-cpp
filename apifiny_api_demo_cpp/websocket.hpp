//
//  websocket.hpp
//  apifiny_api_demo2
//
//  Created by Haobo Yuan on 7/3/22.
//

#ifndef websocket_hpp
#define websocket_hpp

#include <websocketpp/config/asio_client.hpp>    // TLS

#include <nlohmann/json.hpp>
using json = nlohmann::json;
#include <websocketpp/client.hpp>
#include <websocketpp/common/thread.hpp>
#include <websocketpp/common/memory.hpp>

#include "helpers.hpp"
#include <curl/curl.h>

#include <cstdlib>
#include <iostream>
#include <map>
#include <string>
#include <sstream>

using client = websocketpp::client<websocketpp::config::asio_tls_client>;    //TLS


namespace ns {
    // a simple struct to model a person
    struct person {
        std::string name;
        std::string address;
        int age;
    };
}

class connection_metadata {
public:
    using ptr = websocketpp::lib::shared_ptr<connection_metadata>;

    connection_metadata(int id, websocketpp::connection_hdl hdl, std::string uri)
      : m_id(id)
       ,m_hdl(hdl)
       ,m_status("Connecting")
       ,m_uri(uri)
       ,m_server("N/A")
    { }

    void on_open(client *c, websocketpp::connection_hdl hdl)
    {
        m_status = "Open";

        //Get a connection form a handler.
        client::connection_ptr con = c->get_con_from_hdl(hdl);
        m_server = con->get_response_header("Server");
    }

    void on_close(client *c, websocketpp::connection_hdl hdl)
    {
        m_status = "Closed";

        client::connection_ptr con = c->get_con_from_hdl(hdl);
        std::stringstream s;
        s << "close code: " << con->get_remote_close_code()
        << "("
        << websocketpp::close::status::get_string(con->get_remote_close_code())
        << "), close reason: "
        << con->get_remote_close_reason();

        m_error_reason = s.str();
    }

    void on_fail(client *c, websocketpp::connection_hdl hdl)
    {
        m_status = "Failed";

        client::connection_ptr con = c->get_con_from_hdl(hdl);
        m_server = con->get_response_header("Server");
        m_error_reason = con->get_ec().message();
    }

    void on_message(websocketpp::connection_hdl hdl, client::message_ptr msg)
    {
        if(msg->get_opcode() == websocketpp::frame::opcode::text)
        {
            m_last_message = msg->get_payload();
            m_messages.push_back("<<" + m_last_message);
            
        }
        else
        {
            m_last_message = websocketpp::utility::to_hex(msg->get_payload());
            m_messages.push_back("<<" + m_last_message);
            
        }
    }

    std::string get_status() const
    {
        return m_status;
    }

    int get_id() const
    {
        return m_id;
    }

    int get_msg_count() const
    {
        return int(m_messages.size());
    }
    std::string get_last_msg() const
    {
        return m_last_message;
    }
    websocketpp::connection_hdl get_hdl() const
    {
        return m_hdl;
    }

    void record_sent_message(std::string message)
    {
        m_messages.push_back(">>" + message);
        m_last_message = message;
    }

    inline friend std::ostream & operator<< (std::ostream & out, connection_metadata const & data){
        out
        << "> URI: " << data.m_uri << "\n"
        << "> Status: " << data.m_status << "\n"
        << "> Remote Server: " << (data.m_server.empty() ? "None Specified" : data.m_server) << "\n"
        << "> Error/close reason: " << (data.m_error_reason.empty() ? "N/A" : data.m_error_reason) << "\n";

        out
        << "> Messages Processed: (" << data.m_messages.size() <<")\n";
        std::vector<std::string>::const_iterator it;
        for (it = data.m_messages.begin(); it != data.m_messages.end(); ++it)
        {
            out << *it << "\n";
        }

        return out;
    };

private:

    int m_id;
    websocketpp::connection_hdl m_hdl;
    std::string m_status;
    std::string m_uri;
    std::string m_server;
    std::string m_error_reason;
    std::string m_last_message;
    std::vector<std::string> m_messages;

};



class websocket_endpoint
{
public:

    websocket_endpoint()
    {
        m_endpoint.clear_access_channels(websocketpp::log::alevel::all);
        m_endpoint.clear_error_channels(websocketpp::log::elevel::all);

        m_endpoint.init_asio();

        // TLS
        m_endpoint.set_tls_init_handler(websocketpp::lib::bind(&on_tls_init));

        m_endpoint.start_perpetual();

        m_thread.reset(new websocketpp::lib::thread(&client::run, &m_endpoint));

    }

    ~websocket_endpoint()
    {
        m_endpoint.stop_perpetual();

        for(con_list::const_iterator it = m_connection_list.begin();
            it != m_connection_list.end();
            ++it)
        {
            if (it->second->get_status() != "Open")
            {
                continue;
            }

            std::cout << "> Closing connection " << it->second->get_id() << std::endl;

            websocketpp::lib::error_code ec;
            m_endpoint.close(it->second->get_hdl(), websocketpp::close::status::going_away, "", ec);
            if(ec)
            {
                std::cout
                << "> Error closing connection " << it->second->get_id() << ": "
                << ec.message() << std::endl;
            }
        }

        m_thread->join();
    }
    
    int connect(std::string const & uri, std::string const signature = "")
    {

        websocketpp::lib::error_code ec;
        client::connection_ptr con = m_endpoint.get_connection(uri, ec);
        if (signature != ""){
            con->append_header("signature", signature);
        }
        if(ec)
        {
            std::cout << "> Connect initialization error: " << ec.message() << std::endl;
            return -1;
        }

        int new_id = m_next_id++;
        connection_metadata::ptr metadata_ptr(new connection_metadata(new_id, con->get_handle(), uri));
        m_connection_list[new_id] = metadata_ptr;


        con->set_open_handler(websocketpp::lib::bind(
            &connection_metadata::on_open,
            metadata_ptr,
            &m_endpoint,
            websocketpp::lib::placeholders::_1
        ));
        con->set_fail_handler(websocketpp::lib::bind(
            &connection_metadata::on_fail,
            metadata_ptr,
            &m_endpoint,
            websocketpp::lib::placeholders::_1
        ));
        con->set_close_handler(websocketpp::lib::bind(
             &connection_metadata::on_close,
             metadata_ptr,
             &m_endpoint,
             websocketpp::lib::placeholders::_1
         ));
        con->set_message_handler(websocketpp::lib::bind(
             &connection_metadata::on_message,
             metadata_ptr,
             websocketpp::lib::placeholders::_1,
             websocketpp::lib::placeholders::_2
         ));

        m_endpoint.connect(con);
        return new_id;

    }

     void close(int id, websocketpp::close::status::value code, std::string reason) {
         websocketpp::lib::error_code ec;
  
         con_list::iterator metadata_it = m_connection_list.find(id);
         if (metadata_it == m_connection_list.end()) {
             std::cout << "> No connection found with id " << id << std::endl;
             return;
         }
  
         m_endpoint.close(metadata_it->second->get_hdl(), code, reason, ec);
         if (ec) {
             std::cout << "> Error initiating close: " << ec.message() << std::endl;
         }
     }

    void send(int id, std::string message)
    {
        websocketpp::lib::error_code ec;

        con_list::iterator metadata_it = m_connection_list.find(id);
        if (metadata_it == m_connection_list.end())
        {
            std::cout << "> No connection found with id " << id << std::endl;
            return;
        }

        m_endpoint.send(metadata_it->second->get_hdl(), message, websocketpp::frame::opcode::text, ec);
        if(ec){
            std::cout << "> Error sending message: " << ec.message() << std::endl;
            return;
        }
                
        metadata_it->second->record_sent_message(message);
    }

    connection_metadata::ptr get_metadata(int id) const
    {
        con_list::const_iterator metadata_it = m_connection_list.find(id);
        if( metadata_it == m_connection_list.end())
        {
            return connection_metadata::ptr();
        } else {
            return metadata_it->second;
        }
    }

    using context_ptr = std::shared_ptr<boost::asio::ssl::context>;

    static context_ptr on_tls_init()
    {
        context_ptr ctx = std::make_shared<boost::asio::ssl::context>(boost::asio::ssl::context::sslv23);

        try {
            ctx->set_options(
                boost::asio::ssl::context::default_workarounds
                | boost::asio::ssl::context::no_sslv2
                | boost::asio::ssl::context::no_sslv3
                | boost::asio::ssl::context::single_dh_use
            );

        } catch (std::exception &e)
        {
            std::cout << "Error in context pointer: " << e.what() << std::endl;
        }
        return ctx;
    }


private:
    using con_list = std::map<int, connection_metadata::ptr>;
    client m_endpoint;
    websocketpp::lib::shared_ptr<websocketpp::lib::thread> m_thread;
    con_list m_connection_list;
    int m_next_id;
};

#endif /* websocket_hpp */
