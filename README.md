# apifiny_api_demo_cpp
[![GitHub issues](https://img.shields.io/github/issues/Apifiny-IO/apifiny-api-demo-cpp)](https://github.com/Apifiny-IO/apifiny-api-demo-cpp/issues)
[![GitHub forks](https://img.shields.io/github/forks/Apifiny-IO/apifiny-api-demo-cpp)](https://github.com/Apifiny-IO/apifiny-api-demo-cpp/network)
[![GitHub stars](https://img.shields.io/github/stars/Apifiny-IO/apifiny-api-demo-cpp)](https://github.com/Apifiny-IO/apifiny-api-demo-cpp/stargazers)
[![GitHub license](https://img.shields.io/github/license/Apifiny-IO/apifiny-api-demo-cpp)](https://github.com/Apifiny-IO/apifiny-api-demo-cpp/blob/main/LICENSE)
[![contributors](https://img.shields.io/github/contributors/Apifiny-IO/apifiny-api-demo-cpp)](https://github.com/Apifiny-IO/apifiny-api-demo-cpp/graphs/contributors)

A c++ project for demonstrating APIFINY OPEN API.  
* Supported APIs:
    * REST trading/market API
    * WebSocket trading/market API

## Design Goals
apifiny_api_demo aims to provide a handy demonstration of Apifiny's apis(http requests and wesocket) under c++, including rest apis and websocket apis for retreiving market data, interact and inspect accounts, and make trading operations.

```
#include "utilities.hpp"
 int main()
 {
     exchange_api exchange = exchange_api();
     
     exchange.http_requests_demo();
     exchange.ws_run();
     
     return 0;
 }
```

## OPEN API Documentation  
https://doc.apifiny.com/connect/#introduction

## Installation
### Dependencies
* nlohmann/json 
* libcpr/cpr
* openssl
* cpp-jwt (by arun11299)
* websocketpp (by zaphoyd)


## Usage
### Build
Suggested build process:  
1. Make sure all of the dependencies are pre-installed
2. Create a project and import just the apifiny_api_demo2 folder
3. Run the demo
### Potential build issue when dealing with xcode:
If you have installed the dependencies already, but have errors like 
* don't know where the header file is or 
* underfined symbols,  

for first one, try to include the path to the dependencies' include folder in search path(build setting)  
for second one, try to include the path to the dependencies' dylib files in other linker flags(build setting -> link -> other linker flags), and add the path to the library folder to library search path




## Preset
Before running the demo, make sure you have put your account related info in actionList.h for correct connection.  
In actionList.h:
```
inline const string ACCOUNT_ID = "STA-APIFINY_0000001";
inline const string API_KEY_ID = "3360************9f14";
inline const string SECRET_KEY = "35AE************************3617";
...
```

## RESTful APIs
### Usage examples:
run all apis:
```
exchange_api exchange = exchange_api();
exchange.http_requests_demo();
```
Customization:  
In actionList.h, you can find all of json objects containing the specific info required for requests:  
```
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
```
Change the info in string format to customize your actions.

## WebSocket APIs
### Usage examples:
The websocket apis are designed to be an interactive program showing after all off rest api calls:
```
Enter Command(input help for more info):
```
Type "help" and you can see the menu for operations:
```
Enter Command(input help for more info):help

Command List:
connect <ws url(no url input then default connect two urls together)>
list <connection list and connection url>
show <coonection_id>
actions <list all available actinos>
inspect <action name(get the info of each action)>
send <id action_name>
urls <list available ws urls>
close <connection_id> (<close code> <close reason>)
help: Display this help text
quit: Exit the program
```
#### connect command: 
connect to the websocket urls; when nothing following "connect", the program will automatically connect both of the websockets urls:
```
Enter Command(input help for more info):connect
18870 "wss://apicb.apifiny.com/ws/trading"
18869 "wss://api.apifiny.com/md/ws/v1"
eyJh***K3UU
```

#### list command:
list the currently conncted urls and their corresponding ids:
```
Enter Command(input help for more info):list
18870 "wss://apicb.apifiny.com/ws/trading"
18869 "wss://api.apifiny.com/md/ws/v1"
```

#### show command: 
show the connection info for particular connection id in a snap shot fashion:
```
Enter Command(input help for more info):show 18869
> URI: wss://api.apifiny.com/md/ws/v1
> Status: Open
> Remote Server: nginx/1.14.0 (Ubuntu)
> Error/close reason: N/A
> Messages Processed: (4)
<<{"ping":1657294317062}
<<{"ping":1657294317062}
<<{"ping":1657294317062}
<<{"ping":1657294317062}
```

#### actions command:
list all of available ws action names:
```
Enter Command(input help for more info):actions
ws_cob_channel 
ws_cob_channel_unsub 
ws_kline_channel 
ws_kline_channel_unsub 
ws_orderbook_channel 
ws_orderbook_channel_unsub 
ws_ticker_channel 
ws_ticker_channel_unsub 
ws_trade_cancel_all_order 
ws_trade_cancel_order 
ws_trade_new_order 
ws_trades_channel 
ws_trades_channel_unsub 
```
use these names for message sending

#### inspect command
inspect particular aciton:
```
Enter Command(input help for more info):inspect ws_ticker_channel
Data content: {
  "action": "sub",
  "channel": "ticker",
  "symbol": "BTCUSDT",
  "venues": [
    "COINBASEPRO"
  ]
}
URL: wss://api.apifiny.com/md/ws/v1
Is Encoded Required: false
Response Format: {
  "channel": "ticker",
  "symbol": "BTCUSDT",
  "ticker": {
    "amount": "101489083.47069713",
    "close": "36198.03000000",
    "count": "0",
    "high": "36785.32000000",
    "low": "31109.00000000",
    "open": "36631.84000000",
    "provider": "VENUE1",
    "symbol": "BTCUSDT",
    "tickerTime": "1621839608737",
    "updateAt": "1621839608835",
    "vol": "2984.41975300"
  },
  "venues": [
    "VENUE1"
  ]
}
```

#### send command:
send the message to the ws url associated with particular id:
```
send 18869 ws_cob_channel
```
If you are subscribing a channel stream, then the program will loop for 30 seconds stream data and then go back to Enter input line. To check back the snap shot data of the channel, use show command. For other actions, the program will go back to Enter input line immediately.

#### urls command:
show all of available urls you can use to connect:
```
Enter Command(input help for more info):urls
wss://api.apifiny.com/md/ws/v1
wss://apicb.apifiny.com/ws/trading
```

#### close command:
close a connection:
```
Enter Command(input help for more info):close 18901
Enter Command(input help for more info):
```

#### help: 
Display this help text
#### quit: 
Exit the program

## Contributing
Contributions are welcome.
If you've found a bug within this project, please open an issue to discuss what you would like to change.

## License
[MIT](https://choosealicense.com/licenses/mit/)
