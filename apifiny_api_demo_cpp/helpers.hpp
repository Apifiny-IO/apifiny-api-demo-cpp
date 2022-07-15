//
//  helpers.hpp
//  apifiny_api_demo2
//
//  Created by Haobo Yuan on 7/2/22.
//

#ifndef helpers_hpp
#define helpers_hpp
#include <nlohmann/json.hpp>
#include <stdio.h>
#include <openssl/hmac.h>
#include <openssl/sha.h>
#include <openssl/evp.h>
#include <chrono>
#include <sys/time.h>
#include <ctime>
#include <cstdlib>
#include <signal.h>
#include <iostream>
#include <jwt/jwt.hpp>
#include <sstream>

using string = std::string;
using std::chrono::duration_cast;
using std::chrono::milliseconds;
using std::chrono::seconds;
using std::chrono::system_clock;



std::string Replace(std::string& s);
std::string String_to_hex(const std::string& input);
nlohmann::json CleanNoneValue(nlohmann::json params);
std::string PrepareParams(nlohmann::json params);
std::string EncodedString(nlohmann::json j);
std::string GetJwtToken(string secretKey, string accountId, string secretKeyId, std::string params = "");
void SignalCallbackHandler(int signum);
std::string B2aHex(const std::uint8_t *p, std::size_t n);
std::string Sha256Single(const std::string s);
std::string HmacSha256(const std::string key,  const std::string data);
std::string GetSignature(string secretKey, string accountId, string secretKeyId, std::string params);
#endif /* helpers_hpp */
