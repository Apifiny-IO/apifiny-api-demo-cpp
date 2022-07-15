//
//  utilities.hpp
//  apifiny_api_demo2
//
//  Created by Haobo Yuan on 7/4/22.
//

#ifndef utilities_hpp
#define utilities_hpp

#include <stdio.h>
#include <cpr/cpr.h>
#include <chrono>
#include <vector>
#include <map>
#include <unordered_set>
#include "helpers.hpp"
#include "websocket.hpp"
#include "actionList.h"
#include<unistd.h>

using string = std::string;
using vector = std::vector<std::string>;
using unordered_map = std::unordered_map<std::string, json>;



enum Method {GET, POST};

enum Data_Type {BODY, HEADER};

class Action{
public:
    Action(){
        base_url = MD_WS;
        encoded = false;
    }
    
    Action(json j_action, json j_res_modal, std::string base_url = MD_WS, bool encoded = false): j_action(j_action),j_res_modal(j_res_modal), base_url(base_url), encoded(encoded){

    }
    inline json GetJson(){
        return j_action;
    }
    inline std::string GetUrl(){
        return base_url;
    }
    inline bool GetEncoded(){
        return encoded;
    }
    inline json GetResponse(){
        return j_res_modal;
    }
private:
    json j_action;
    json j_res_modal;
    std::string base_url;
    bool encoded;
};

class InfoDic{
public:
    InfoDic(){
        account_id = ACCOUNT_ID;
        api_key_id = API_KEY_ID;
        secret_key = SECRET_KEY;
        symbol = SYMBOL;
        venue = VENUE;
        venues = VENUES;
        api_http = API_HTTP;
        host = HOST;
        md_ws = MD_WS;
        order_push_ws = ORDER_PUSH_WS;
        order_new_ws = ORDER_NEW_WS;
    }
    InfoDic(string account_id, string api_key_id, string secret_key, string symbol, string venue, string api_http, string host, string md_ws, string order_push_ws, string order_new_ws, vector venues): account_id(account_id), api_key_id(api_key_id), secret_key(secret_key), symbol(symbol), venue(venue), api_http(api_http), host(host), md_ws(md_ws), order_push_ws(order_push_ws), order_new_ws(order_new_ws){
        this -> venues = venues;
    }
        string GetAccountId()
        {
            return this -> account_id;
        }

        void SetAccountId(string account_id)
        {
            this -> account_id = account_id;
        }

        string GetApiKeyId()
        {
            return this -> api_key_id;
        }

        void SetApiKeyId(string api_key_id)
        {
            this -> api_key_id = api_key_id;
        }
        string GetSecretKey()
        {
            return this -> secret_key;
        }

        void SetSecretKey(string secret_key)
        {
            this -> secret_key = secret_key;
        }
        string GetSymbol()
        {
            return this -> symbol;
        }

        void SetSymbol(string symbol)
        {
            this -> symbol = symbol;
        }

        string GetVenue()
        {
            return this -> venue;
        }
        void SetVenue(string venue)
        {
            this -> venue = venue;
        }
        string GetApiHttp()
        {
            return this -> api_http;
        }
        void SetApiHttp(string api_http)
        {
            this -> api_http = api_http;
        }
        string GetHost()
        {
            return this -> host;
        }
        void SetHost(string host)
        {
            this -> host = host;
        }
        string GetMdWs()
        {
            return this -> md_ws;
        }
        void SetMdWs(string md_ws)
        {
            this -> md_ws = md_ws;
        }
        string GetOrderPushWs()
        {
            return this -> order_push_ws;
        }
        void SetOrderPushWs(string order_push_ws)
        {
            this -> order_push_ws = order_push_ws;
        }
        string GetOrderNewWs()
        {
            return this -> order_new_ws;
        }
        void SetOrderNewWs(string order_new_ws)
        {
            this -> order_new_ws = order_new_ws;
        }
        vector GetVenues()
        {
            return this -> venues;
        }
        void SetVenues(vector venues)
        {
            this -> venues = venues;
        }
private:
    string account_id;
    string api_key_id;
    string secret_key;
    string symbol;
    string venue;
    string api_http;
    string host;
    string md_ws;
    string order_push_ws;
    string order_new_ws;
    vector venues;
};

class ExchangeApi{
public:
    ExchangeApi(){
        dic = InfoDic();
        SetUpActionMap();
    }
    ExchangeApi(string account_id, string api_key_id, string secret_key, string symbol, string venue, string api_http, string host, string md_ws, string order_push_ws, string order_new_ws, vector venues): dic(account_id, api_key_id,  secret_key, symbol, venue, api_http, host, md_ws, order_push_ws, order_new_ws, venues){
        SetUpActionMap();
    }
    
    void WsRun();
    void HttpRequestsDemo();
    void AddWsAction(string action_name, json action);
    void EraseWsAction(string action_name);
    void printExchanges();
    void printSymbols();
    //void run_ws_action(string action_name, string base_url = "", bool encoded = false);
private:
    InfoDic dic;
    unordered_map mp;
    string GetToken(string params = "");
    string GetSign(string params = "");
    unordered_map connection_mp;
    vector exchanges;
    vector symbols;
    std::map<std::string, Action> action_mp;
    string HttpRequest(json j, Method method, string base_url, Data_Type type = Data_Type::HEADER);
    string HttpRequestNew(json j, Method method, string base_url, Data_Type type = Data_Type::HEADER);
    void SetUpActionMap();
};


#endif /* utilities_hpp */
