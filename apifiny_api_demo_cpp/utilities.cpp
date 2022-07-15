//
//  utilities.cpp
//  apifiny_api_demo2
//
//  Created by Haobo Yuan on 7/4/22.
//

#include "utilities.hpp"


void ExchangeApi::HttpRequestsDemo(){
     std::cout << "listVenueInfo" << std::endl;
     HttpRequest(j_empty, GET, HOST + "/ac/v2/APIFINY/utils/listVenueInfo");

     std::cout << "listCurrency" << std::endl;
     HttpRequest(j_empty, GET, HOST + "/ac/v2/BINANCE/utils/listCurrency");

     std::cout << "listSymbolInfo" << std::endl;
     HttpRequest(j_empty, GET, "https://apibn.apifiny.com/ac/v2/utils/listSymbolInfo");

     std::cout << "currentTimeMillis" << std::endl;
     HttpRequest(j_empty, GET, "https://apibn.apifiny.com/ac/v2/utils/currentTimeMillis");

     std::cout << "orderbook" << std::endl;
     HttpRequest(j_empty, GET, HOST + "/md/orderbook/v1/BTCUSD/COINBASEPRO");

     std::cout << "trades" << std::endl;
     HttpRequest(j_empty, GET, HOST + "/md/trade/v1/BTCUSD/COINBASEPRO");

     std::cout << "OHLCV" << std::endl;
     HttpRequest(http_ohlcv_params, GET, HOST + "/md/kline/v1/GBBO/BTC/USDT/1m");

     std::cout << "ticker" << std::endl;
     HttpRequest(j_empty, GET, HOST + "/md/ticker/v1/BTCUSD/COINBASEPRO");

     std::cout << "cob" << std::endl;
     HttpRequest(j_empty, GET, HOST + "/md/cob/v1/BTCUSDT");


     std::cout << "create account" << std::endl;
     HttpRequest(http_create_account, GET, HOST + "/ac/v2/APIFINY/account/createSubAccount");
     //create subaccount problems and there after the other problems


     std::cout << "query account info" << std::endl;
     HttpRequest(http_query_account, GET, HOST + "/ac/v2/APIFINY/account/queryAccountInfo");


     std::cout << "account balance" << std::endl;
     HttpRequest(http_query_balance, GET, HOST + "/ac/v2/COINBASEPRO/asset/listBalance");
     //nothing for new account: result: []

     std::cout << "query deposit address" << std::endl;
     json address = json::parse(HttpRequest(http_query_address, GET, HOST + "/ac/v2/APIFINY/asset/queryAddress"));

     std::cout << "create a withdraw ticket" << std::endl;
     string ticket_str = HttpRequest(http_create_withdraw_ticker, GET, HOST + "/ac/v2/APIFINY/asset/createWithdrawTicket");

     json ticket = json::parse(ticket_str);
     std::cout << ticket["result"]["ticket"] << std::endl;
     http_withdraw_request["address"] = address["result"]["address"];
     http_withdraw_request["ticket"] = ticket["ticket"];
     std::cout << "new_order" << std::endl;
     HttpRequest(http_withdraw_request, POST, HOST + "/ac/v2/APIFINY/asset/withdraw", BODY);



     std::cout << "transfer funds" << std::endl;
     HttpRequest(http_transfer_funds, POST, HOST + "/ac/v2/APIFINY/asset/transferToVenue", BODY);

     std::cout << "transfer funds history" << std::endl;
     HttpRequest(http_transfer_funds_history, GET, HOST + "/ac/v2/APIFINY/asset/queryAssetActivityList");


     std::cout << "transaction fees" << std::endl;
     HttpRequest(http_transaction_fee, GET, HOST + "/ac/v2/APIFINY/utils/query-transaction-fee");

     std::cout << "trading fee rate" << std::endl;
     HttpRequest(http_trading_fee_rate, GET, HOST + "/ac/v2/BINANCE/asset/getCommissionRate");


     std::cout << "query instant transfer quota" << std::endl;
     HttpRequest(http_query_inst_quota, GET, HOST + "/ac/v2/APIFINY/asset/query-max-instant-amount");

     std::cout << "create currency conversion" << std::endl;
     HttpRequest(http_create_conversion, POST, "https://apicb.apifiny.com/ac/v2/asset/currencyConversion", BODY);
     //document needs to be updated for more clear instruction


     std::cout << "create a new order" << std::endl;
     HttpRequest(http_new_order, POST, HOST + "/ac/v2/BINANCE/order/newOrder", BODY);

     std::cout << "cancel an order" << std::endl;
     HttpRequest(http_cancel_order, POST, HOST + "/ac/v2/BINANCE/order/cancelOrder", BODY);

     std::cout << "cancel all orders" << std::endl;
     HttpRequest(http_cancel_all_order, POST, HOST + "/ac/v2/BINANCE/order/cancelAccountVenueAllOrder", BODY);

     std::cout << "query order info" << std::endl;
     HttpRequest(http_query_order_info, GET, HOST + "/ac/v2/BINANCE/order/queryOrderInfo");


     std::cout << "query multi orders info" << std::endl;
     HttpRequest(http_query_muti_order, GET, HOST + "/ac/v2/BINANCE/order/listMultipleOrderInfo"); //special parsing for order ids

     std::cout << "query all open orders" << std::endl;
     HttpRequest(http_query_all_open_orders, GET, HOST + "/ac/v2/BINANCE/order/listOpenOrder");

     std::cout << "query all complete orders" << std::endl;
     HttpRequest(http_query_all_compl_orders, GET, HOST + "/ac/v2/BINANCE/order/listCompletedOrder");

     std::cout << "query list fills" << std::endl;
     HttpRequest(http_query_list_fills, GET, HOST + "/ac/v2/BINANCE/order/listFilledOrder");

     std::cout << "create new sor order" << std::endl;
     json sor_order = json::parse(HttpRequest(http_create_sor_order, POST, HOST + "/ac/v2/APIFINY/order/newOrder", BODY));

     http_cancel_sor_order["orderId"] = sor_order["result"]["orderId"];
     std::cout << http_cancel_sor_order["orderId"] << std::endl;
     std::cout << "cancel sor order" << std::endl;
     HttpRequest(http_cancel_sor_order, POST, HOST + "/ac/v2/APIFINY/order/cancelOrder", BODY);


      std::cout << "get a SOR order" << std::endl;
      HttpRequest(http_get_sor_order, GET, HOST + "/ac/v2/APIFINY/algo/query-order-info");


      std::cout << "query open orders" << std::endl;
      HttpRequest(http_query_open_orders, GET, HOST + "/ac/v2/APIFINY/algo/list-open-order");


      std::cout << "query open orders history" << std::endl;
      HttpRequest(http_query_orders_history, GET, HOST + "/ac/v2/APIFINY/algo/list-order-history");


      std::cout << "query order info" << std::endl;
      HttpRequest(http_query_order_detail, GET, HOST + "/ac/v2/APIFINY/algo/order-detail");
}

void ExchangeApi::WsRun(){
    int cur_id;
    bool done = false;
    string input;
    websocket_endpoint endpoint;
    signal(SIGINT, SignalCallbackHandler);
    while(!done)
    {
        std::cout << "Enter Command(input help for more info):";
        std::getline(std::cin, input);

        if (input == "quit")
        {
            done = true;
        }
        else if (input == "help")
        {
            std::cout
                << "\n"
                << "Command List:\n"
                << "connect <ws url(no url input then default connect two urls together)>\n"
                << "list <connection list and connection url>\n"
                << "show <coonection_id>\n"
                << "actions <list all available actinos>\n"
                << "inspect <action name(get the info of each action)>\n"
                << "send <id action_name>\n"
                << "urls <list available ws urls>\n"
                << "close <connection_id> (<close code> <close reason>)\n"
                << "help: Display this help text\n"
                << "quit: Exit the program\n"
                << std::endl;
        } else if(input.substr(0, 7) == "connect")
        {
            string enc_str_ws;
            std::string base_url;
            std::string cmd;
            std::stringstream ss(input);
            ss >> cmd >> base_url;
            //std::cout << base_url << std::endl;
            std::string md_ws = dic.GetMdWs();
            std::string order_new_ws = dic.GetOrderNewWs();
            if (input == "connect"){
                int id = endpoint.connect(md_ws, "");
                connection_mp[std::to_string(id)] = md_ws;
                id = endpoint.connect(order_new_ws, GetToken());
                connection_mp[std::to_string(id)] = order_new_ws;
                for (auto it : connection_mp){
                    std::cout << it.first << " " << it.second << std::endl;
                }
                std::cout << GetToken() << std::endl;
                std::cout << std::endl;
            }
            else if (base_url != md_ws && base_url != order_new_ws){
                std::cout << "wrong base url!" << std::endl;
            }
            else{
                int id{};
                if (base_url == order_new_ws){
                    enc_str_ws = GetToken();
                }
                if(input.size() > 7)
                {
                    std::string conn_str = input.substr(8);
                    id = endpoint.connect(conn_str, enc_str_ws);
                    connection_mp[std::to_string(id)] = conn_str;
                }
                cur_id = id;
                if( id != -1)
                {
                    std::cout << "> Created connection with id " << id << std::endl;
                }
            }

        } else if (input.substr(0, 4) == "show")
        {
            int id = atoi(input.substr(5).c_str());
            connection_metadata::ptr metadata = endpoint.get_metadata(id);
            if (metadata){
                std::cout << *metadata << std::endl;
            }
            else
            {
                std::cout << "> Unknown connection id " << id << std::endl;
                break;
            }
        }
        else if (input.substr(0,4) == "send")
        {
            std::stringstream ss(input);
            std::string cmd;
            std::string action_name;
            int msg_count;
            int pre_count = -1;
            ss >> cmd >> cur_id >> action_name;
            if (!action_mp.count(action_name)){
                std::cout << "wrong action name!" << std::endl;
                continue;
            }
            std::string message = action_mp[action_name].GetJson().dump();
            if(message != ""){
                endpoint.send(cur_id, message);
            }
            long millisec_since_epoch;
            if (action_name.substr(action_name.size() - 7, 7) == "channel"){
                millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() + 30000;
            }
            else{
                millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() + 1000;
            }
            while(duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() != millisec_since_epoch){
                connection_metadata::ptr metadata = endpoint.get_metadata(cur_id);
                std::string last_msg;
                if(metadata)
                {
                    msg_count = metadata -> get_msg_count();
                    last_msg = metadata -> get_last_msg();

                    if (last_msg.size() > 6 && last_msg.substr(0, 7) == "> Error"){
                        break;
                    }
                    if (msg_count != pre_count){
                        std::cout << last_msg << std::endl;
                    }
                    pre_count = msg_count;
                } else
                {
                    std::cout << "> Unknown connection id " << cur_id << std::endl;
                    break;
                }
            }
            connection_metadata::ptr metadata = endpoint.get_metadata(cur_id);
            std::cout << metadata -> get_msg_count() << std::endl;
        }
        else if (input.substr(0, 5) == "close")
        {
            std::stringstream ss(input);
            std::string cmd;
            int id;
            int close_code = websocketpp::close::status::normal;
            std::string reason;
            ss >> cmd >> id >> close_code;
            std::getline(ss, reason);
            endpoint.close(id, close_code, reason);
            connection_mp.erase(std::to_string(id));
        }
        else if (input.substr(0, 4) == "list"){
            for (auto it : connection_mp){
                std::cout << it.first << " " << it.second << std::endl;
            }
            std::cout << std::endl;
        }
        else if (input.substr(0, 11) == "actions"){
            for (auto it : action_mp){
                std::cout << it.first << " " << std::endl;
            }
        }
        else if (input.substr(0, 7) == "inspect"){
            std::stringstream ss(input);
            std::string cmd;
            std::string action_name;
            ss >> cmd >> action_name;
            if (action_mp.count(action_name)){
                std::cout << "Data content: " << action_mp[action_name].GetJson().dump(2) << std::endl;
                std::cout << "URL: " << action_mp[action_name].GetUrl() << std::endl;
                std::cout << std::boolalpha << "Is Encoded Required: " << action_mp[action_name].GetEncoded() << std::endl;
                std::cout << "Response Format: " << action_mp[action_name].GetResponse().dump(2) << std::endl;
                std::cout << std::endl;
            }
            else{
                std::cout << "wrong action name!" << std::endl;
                std::cout << std::endl;
            }
        }
        else if (input.substr(0, 4) == "urls"){
            std::cout << dic.GetMdWs() << std::endl;
            std::cout << dic.GetOrderNewWs() << std::endl;
        }
        else
        {
            std::cout << "Unrecognized Command" << std::endl;
        }
    }
    return;
}

string ExchangeApi::HttpRequest(json j, Method method, string base_url, Data_Type type){
     //& reference for json, enum for type method
    std::string str;
    string enc_str;
    cpr::Response r;
    cpr::Parameters parameters;
    if (method == Method::GET || type == Data_Type::HEADER){
        json::iterator it = j.begin();
        while (it != j.end()){
            parameters.Add({it.key(), it.value()});
            it++;
        }
        str = PrepareParams(j);
        //std::cout << str << std::endl;
        enc_str = GetToken(str);
    }
    else{
        str = j.dump();
        enc_str = GetToken(str);
    }
    if (method == Method::GET){
        r = cpr::Get(cpr::Url{base_url},
                     parameters,
                     cpr::Header{{"signature", enc_str}});
    }
    else if (method == Method::POST){
        r = cpr::Post(cpr::Url{base_url},
                      cpr::Body{str},
                      cpr::Header{{"signature", enc_str}, {"Content-Type", "application/json"}});
    }
    std::cout << base_url << std::endl; //api.apifiny.com/ac/v2/GBBO/asset/listBalance
    std::cout << str << std::endl; //accountId=STA-APIFINY_1301898&venue=INDEPENDENTRESERVE
    std::cout << "account id: " << dic.GetAccountId() << std::endl;
    std::cout << "secret_key_id id: " << dic.GetApiKeyId() << std::endl;
    std::cout << "secret_key: " << dic.GetSecretKey() << std::endl;
    std::cout << "signature: " << enc_str << std::endl;
    std::cout << r.text << std::endl;
    std::cout << std::endl;
    return r.text;
}

void ExchangeApi::AddWsAction(string action_name, json action){
    mp[action_name] = action;
    return;
}
void ExchangeApi::EraseWsAction(string action_name){
    mp.erase(action_name);
    return;
}

string ExchangeApi::GetToken(string params){
    return GetJwtToken(dic.GetSecretKey(), dic.GetAccountId(), dic.GetApiKeyId(), params);
}

void ExchangeApi::SetUpActionMap(){
    action_mp["ws_orderbook_channel"] = Action(ws_orderbook_channel,ws_orderbook_payload);
    action_mp["ws_orderbook_channel_unsub"] = Action(ws_orderbook_channel_unsub, j_empty);
    action_mp["ws_trades_channel"] = Action(ws_trades_channel, ws_trades_payload);
    action_mp["ws_trades_channel_unsub"] = Action(ws_trades_channel_unsub, j_empty);
    action_mp["ws_kline_channel"] = Action(ws_kline_channel, ws_kline_payload);
    action_mp["ws_kline_channel_unsub"] = Action(ws_kline_channel_unsub, j_empty);
    action_mp["ws_ticker_channel"] = Action(ws_ticker_channel, ws_ticker_payload);
    action_mp["ws_ticker_channel_unsub"] = Action(ws_ticker_channel_unsub, j_empty);
    action_mp["ws_cob_channel"] = Action(ws_cob_channel, ws_cob_payload);
    action_mp["ws_cob_channel_unsub"] = Action(ws_cob_channel_unsub, j_empty);
    action_mp["ws_trade_new_order"] = Action(ws_trade_new_order, ws_trade_new_order_payload, ORDER_NEW_WS, true);
    action_mp["ws_trade_cancel_order"] = Action(ws_trade_cancel_order, ws_trade_cancel_order_payload, ORDER_NEW_WS, true);
    action_mp["ws_trade_cancel_all_order"] = Action(ws_trade_cancel_all_order, ws_trade_cancel_all_order_payload, ORDER_NEW_WS, true);
}



    
