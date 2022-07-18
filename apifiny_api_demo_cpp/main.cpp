#include "utilities.hpp"
#include <iostream>
 int main()
 {
     ExchangeApi exchange = ExchangeApi();
     exchange.HttpRequestsDemo();
     exchange.WsRun();
     return 0;
 }
