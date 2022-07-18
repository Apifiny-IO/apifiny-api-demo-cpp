//
//  actionList.h
//  apifiny_api_demo2
//
//  Created by Haobo Yuan on 7/4/22.
//

#ifndef actionList_h
#define actionList_h

#include <nlohmann/json.hpp>
#include <vector>
using json = nlohmann::json;
using string = std::string;
using vector = std::vector<std::string>;

inline const string ACCOUNT_ID = "STA-APIFINY_11111111";
inline const string API_KEY_ID = "583*********1dfa6b5";
inline const string SECRET_KEY = "01********************4C793";
inline const string SYMBOL = "BTCUSD";
inline const string VENUE = "GBBO";
inline const vector VENUES = {"GBBO"};
inline const string API_HTTP = "https://api.apifiny.com/ac/v2/GBBO";
inline const string HOST = "https://api.apifiny.com";
inline const string MD_WS = "wss://api.apifiny.com/md/ws/v1";
inline const string ORDER_NEW_WS = "wss://apicb.apifiny.com/ws/stream";

inline json j_empty;

inline json j = {
    {"action", "newOrder"},
    {"data", {
        {"orderId", ""},
        {"venue", "COINBASEPRO"},
        {"orderInfo", {
            {"symbol", "BTCUSDT"},
            {"orderType", "LIMIT"},
            {"quantity", "1.12"},
            {"limitPrice", "100"},
            {"orderSide", "BUY"},
            {"timeInForce", "1"},
            {"total", "0"}
        }},
    }}
};

inline json ws_orderbook_channel = {{"channel", "orderbook"}, {"symbol", "BTCUSDT"}, {"venues", json::array({"COINBASEPRO"})}, {"action", "sub"}};

inline json ws_orderbook_channel_pack = {{"channel", "orderbook"}, {"symbol", "BTCUSDT"}, {"venues", json::array({"BINANCE","BINANCEUS","COINBASEPRO","FTX","GBBO","HUOBI","KUCOIN","OKCOIN","OKX","BITBAY","BITHUMB","BITMAX","BITSO","BITSTAMP","BITTREX","BLOCKCHAIN","COINBASEPROUK","COINONE","CRYPTO","EXMO","GATEIO","GEMINI","INDEPENDENTRESERVE","INDODAX","ITBIT","KORBIT","KRAKEN","KRAKENUK","LIQUID","UPBIT"})}, {"action", "sub"}};

inline json ws_orderbook_channel_pack_unsub = {{"channel", "orderbook"}, {"symbol", "BTCUSDT"}, {"venues", json::array({"BINANCE","BINANCEUS","COINBASEPRO","FTX","GBBO","HUOBI","KUCOIN","OKCOIN","OKX","BITBAY","BITHUMB","BITMAX","BITSO","BITSTAMP","BITTREX","BLOCKCHAIN","COINBASEPROUK","COINONE","CRYPTO","EXMO","GATEIO","GEMINI","INDEPENDENTRESERVE","INDODAX","ITBIT","KORBIT","KRAKEN","KRAKENUK","LIQUID","UPBIT"})}, {"action", "unsub"}};

inline json ws_orderbook_payload = {
    {"venues", json::array({"VENUE1"})},
    {"channel", "orderbook"},
    {"symbol", "BTCUSDT"},
    {"orderbook", {
        {"symbol", "BTCUSDT"},
        {"updatedAt", "1621839607399"},
        {"asks", json::array({
            json::array({"36179.76000000", "0.01311800"})
            // [price, size]
            // ……
        })},
        {"bids", json::array({
            json::array({"36165.88000000", "0.01426800"}),
            json::array({"36153.40000000", "0.05641000"})
        })}
    }}
};



inline json ws_orderbook_channel_unsub = {{"channel", "orderbook"}, {"symbol", "BTCUSDT"}, {"venues", json::array({"BITMAX"})}, {"action", "unsub"}};

inline json ws_trades_channel = {{"channel", "trade"}, {"symbol", "BTCUSDT"}, {"venues", json::array({"COINBASEPRO"})}, {"action", "sub"}};

inline json ws_trades_payload = {
    {"venues", json::array({"VENUE1"})},
    {"channel", "trade"},
    {"symbol", "BTCUSDT"},
    {"trade", {
        {"trades", json::array({{
            {"symbol", "BTCUSDT"},
            {"provider", "VENUE1"},
            {"price","36271.52000000"},
            {"qty","0.00034500"},
            {"side", "BUY"},
            {"tradeTime","1621839791084"},
            {"exchangeID", "5093303"},
            {"updateTime","1621839791086"}
        }, {
            {"symbol", "BTCUSDT"},
            {"provider", "VENUE1"},
            {"price","36289.07000000"},
            {"qty","0.00000700"},
            {"side", "SELL"},
            {"tradeTime","1621839787668"},
            {"exchangeID", "5093301"},
            {"updateTime","1621839787671"}
        }})
        }}}
};

inline json ws_trades_channel_unsub = {{"channel", "trade"}, {"symbol", "BTCUSDT"}, {"venues", json::array({"COINBASEPRO"})}, {"action", "unsub"}};

inline json ws_kline_channel = {{"channel", "kline_1m"}, {"symbol", "BTCUSDT"}, {"venues", json::array({"COINBASEPRO"})}, {"action", "sub"}}; //speed is somehow slow

inline json ws_kline_payload = {
    {"venues", json::array({"VENUE1"})},
    {"channel", "kline_1m"},
    {"symbol", "BTC/USD"},
    {"kline_1m", {
        {"currencyPair", "BTC/USD"},
        {"period", "1m"},
        {"open","36536.1900"},
        {"high","36536.1900"},
        {"low","36464.6200"},
        {"close","36464.6200"},
        {"vol","2.46849600"},
        {"count","65"},
        {"timestamp","1621841040000"},
        {"exchange", "VENUE1"}
    }}
};

inline json ws_kline_channel_unsub = {{"channel", "kline_1m"}, {"symbol", "BTCUSDT"}, {"venues", json::array({"COINBASEPRO"})}, {"action", "unsub"}};

inline json ws_ticker_channel = {{"channel", "ticker"}, {"symbol", "BTCUSDT"}, {"venues", json::array({"COINBASEPRO"})}, {"action", "sub"}};

inline json ws_ticker_payload = {
    {"venues", json::array({"VENUE1"})},
    {"channel", "ticker"},
    {"symbol", "BTCUSDT"},
    {"ticker", {
        {"symbol", "BTCUSDT"},
        {"open", "36631.84000000"},
        {"high", "36785.32000000"},
        {"low", "31109.00000000"},
        {"close", "36198.03000000"},
        {"vol", "2984.41975300"},
        {"amount", "101489083.47069713"},
        {"count", "0"},
        {"provider", "VENUE1"},
        {"tickerTime", "1621839608737"},
        {"updateAt", "1621839608835"}
    }
    }};

inline json ws_ticker_channel_unsub = {{"channel", "ticker"}, {"symbol", "BTCUSDT"}, {"venues", json::array({"COINBASEPRO"})}, {"action", "unsub"}};

inline json ws_cob_channel = {{"channel", "ticker"}, {"symbol", "BTCUSDT"}, {"action", "sub"}};

inline json ws_cob_payload = {
    {"asks", json::array({{
        {"price", "46840"},
        {"qty", "0.00004784"},
        {"source", "HUOBI"}
    },
// ……
    {
        {"price", "47040"},
        {"qty", "0.23653"},
        {"source", "BINANCE"}
    }})},
    {"bids", json::array({{
        {"price", "47039.99"},
        {"qty", "0.007"},
        {"source", "GATEIO"}
    },
// ……
    {
        {"price", "47038.62"},
        {"qty", "0.0161"},
        {"source", "KUCOIN"}
    }})},
    {"symbol", "BTCUSDT"},
    {"updateAt", "1640850556984"}
};
inline json ws_cob_channel_unsub = {{"channel", "ticker"}, {"symbol", "BTCUSDT"}, {"action", "unsub"}};


inline json ws_trade_new_order = {
    {"action", "newOrder"},
    {"data", {
        {"orderId", ""},
        {"venue", "COINBASEPRO"},
        {"orderInfo", {
            {"symbol", "BTCUSDT"},
            {"orderType", "LIMIT"},
            {"quantity", "1.12"},
            {"limitPrice", "100"},
            {"orderSide", "BUY"},
            {"timeInForce", "1"},
            {"total", "0"}
        }},
    }}
};

inline json ws_trade_new_order_payload = {
    {"result", json::array({{
        {"accountId", "STA-VENUE1_00000001"},
        {"venue", "BINANCE"},
        {"orderId", "000000011584603011942221"},
        {"symbol", "BTCUSD"},
        {"orderType", "LIMIT"},
        {"orderSide", "BUY"},
        {"limitPrice", "100"},
        {"quantity", "1.12"},
        {"filledAveragePrice", "0"},
        {"filledCumulativeQuantity", "0"},
        {"timeInForce", "0"},
        {"openQuantity", "0"},
        {"orderStatus", "PENDING_SUBMIT"},
        {"total", "NULL"},
        {"stopType", "NULL"},
        {"triggerPrice", "NULL"},
        {"triggerTime", "NULL"},
        {"createdAt", "1584603012164"},
        {"updatedAt", "1584603012164"}
    }})},
    {"error", "NULL"}
};

inline json ws_trade_cancel_order = {
    {"action", "cancelOrder"},
    {"data", {
        {"orderId", "872804677639471104"},
        {"venue", "COINBASEPRO"}
    }}
};

inline json ws_trade_cancel_order_payload = {
    {"result", json::array({{
        {"accountId", "STA-VENUE1_00000001"},
        {"venue", "BINANCE"},
        {"orderId", "000000011584603011942221"},
        {"symbol", "BTCUSD"},
        {"orderType", "LIMIT"},
        {"orderSide", "BUY"},
        {"limitPrice", "100"},
        {"quantity", "1.12"},
        {"filledAveragePrice", "0"},
        {"filledCumulativeQuantity", "0"},
        {"timeInForce", "0"},
        {"openQuantity", "0"},
        {"orderStatus", "PENDING_SUBMIT"},
        {"total", "NULL"},
        {"stopType", "NULL"},
        {"triggerPrice", "NULL"},
        {"triggerTime", "NULL"},
        {"createdAt", "1584603012164"},
        {"updatedAt", "1584603012164"}
    }})},
    {"error", "NULL"}
};

inline json ws_trade_cancel_all_order = {
    {"action", "cancelAllOrder"},
    {"data", {
        {"venue", "COINBASEPRO"},
        {"symbol", "BTCUSDT"}
    }}
};

inline json ws_trade_cancel_all_order_payload = R"({
    "result": [
        "519e f355d9884e1f8e3d3ffc7caf13b5",
        "519e f355d9884e1f8e3d3ffc7caf13b3",
        "519e f355d9884e1f8e3d3ffc7caf14b5",
        "519e f355d9884e1f8e3d3ffc7caf13b6"
    ],
    "error": "NULL"
})"_json;

inline json http_ohlcv_params = {
    {"startTime", "1656937290932"},
    {"endTime", "1656850890932"}
};



inline json http_create_account = {{"accountId", ACCOUNT_ID},{"venue","COINBASEPRO"}};

inline json http_query_account = {{"accountId", ACCOUNT_ID}}; //,{"venue","COINBASEPRO"} optional

inline json http_query_balance = {{"accountId", ACCOUNT_ID}, {"venue","COINBASEPRO"}};

inline json http_query_address = {{"accountId", ACCOUNT_ID}, {"venue","APIFINY"}, {"coin", "USDT.ETH"}};

inline json http_create_withdraw_ticker = {{"accountId", ACCOUNT_ID}, {"venue","COINBASEPRO"}};

inline json http_withdraw_request = {
    {"accountId", ACCOUNT_ID},
    {"venue", "BINANCE"},
    {"coin", "USDT.ETH"},
    {"amount", "1000.0021"},
    {"memo", ""},
    {"address", "0x3Nwna****************fp8v"},
    {"ticket", "b2152827079******793d4bbe436f"}
};



inline json http_transfer_funds = {{"accountId", ACCOUNT_ID},{"venue", "BINANCE"}, {"currency", "BTC"}, {"amount", "10.0"}, {"targetVenue", "COINBASEPRO"}};
//{"result":null,"error":{"code":327834,"message":"Order create failed, timestamp error"}}

inline json http_transfer_funds_history = {
    {"accountId", ACCOUNT_ID},
    {"startTimeDate", "1656937290932"},
    {"endTimeDate", "1656850890932"},
    {"limit", "10"},
    {"page", "1"}
  };

inline json http_transaction_fee = {
    {"type", "deposit"},
    {"from", ""},
    {"to", ""},
    {"currency", "BTC"},
    {"coin", "BTC"}
};

inline json http_trading_fee_rate = {
    {"accountId", ACCOUNT_ID},
    {"venue","BINANCE"},
    {"symbol", "BTCUSDT"}
};

inline json http_query_inst_quota = {
    {"accountId", ACCOUNT_ID},
    {"venue","BINANCE"},
    {"currency", "BTC"}
};

inline json http_create_conversion = {
    {"accountId", ACCOUNT_ID},
    {"venue","COINBASEPRO"},
    {"currency", "USD"},
    {"amount", "10000"},
    {"targetCurrency", "USDC"}
};

inline json http_new_order = {{"accountId", ACCOUNT_ID},{"venue","BINANCE"},{"orderInfo", {{"symbol", "BTCUSDT"},{"orderType", "LIMIT"},{"timeInForce", "1"},{"orderSide", "BUY"},{"limitPrice", "100"},{"quantity", "1.12"}}}};

inline json http_cancel_order = {{"accountId", ACCOUNT_ID},{"venue","BINANCE"},{"orderId", "00000001152221"}};

inline json http_cancel_all_order = {{"accountId", ACCOUNT_ID},{"venue", "BINANCE"},{"symbol", "BTCUSD"}};

inline json http_query_order_info = {{"accountId", ACCOUNT_ID}, {"venue", "BINANCE"},{"orderId","000000011584603011942221"}};

inline json http_query_muti_order = {{"accountId", ACCOUNT_ID},{"orderIdList","000000121574697605570321,000000121574697754664817"}};

inline json http_query_all_open_orders = {{"accountId", ACCOUNT_ID}, {"venue", "BINANCE"}};

inline json http_query_all_compl_orders = {{"accountId", ACCOUNT_ID}, {"venue", "COINBASEPRO"}, {"startTime", "1537857271784"}, {"endTime", "1537857271784"}, {"limit", "100"}};

inline json http_query_list_fills = {{"accountId", ACCOUNT_ID}, {"venue", "COINBASEPRO"}, {"symbol", "BTCUSDT"}, {"startTime", "1537857271784"}, {"endTime", "1537857271784"}, {"limit", "600"}};

inline json http_create_sor_order = {
    {"accountId", ACCOUNT_ID},
//    {"orderId", "APIFINY_000000011584603011942221"},
    {"venue", "BINANCE,KUCOIN,HUOBI,OKX,COINBASEPRO"},
    {"orderInfo", {
      {"symbol", "BTCUSDT"},
      {"orderType", "SOR"},
      {"orderSide", "BUY"},
      {"limitPrice", "30000"},
      {"quantity", "1"}
    }}
  };

inline json http_cancel_sor_order = {
    {"accountId", ACCOUNT_ID},
    {"orderId", ""}
};

inline json http_get_sor_order = {
    {"accountId", ACCOUNT_ID},
    {"orderId", "APIFINY_000000011584603011942221"}
};

inline json http_query_open_orders = {{"accountId", ACCOUNT_ID}};

inline json http_query_orders_history = {{"accountId", ACCOUNT_ID}, {"startTime", "1650532374000"}, {"endTime","1650532462000"}, {"limit", "5"}}; //other options please refer to documents

inline json http_query_order_detail = {{"accountId", ACCOUNT_ID}, {"orderId", "APIFINY_000000011584603011942221"}};

#endif /* actionList_h */
