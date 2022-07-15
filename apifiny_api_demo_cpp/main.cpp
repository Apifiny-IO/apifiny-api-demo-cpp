#include "utilities.hpp"
 int main()
 {
     ExchangeApi exchange = ExchangeApi();
     exchange.HttpRequestsDemo();
     exchange.WsRun();
     
     return 0;
 }
