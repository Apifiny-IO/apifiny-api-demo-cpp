//
//  helpers.cpp
//  apifiny_api_demo2
//
//  Created by Haobo Yuan on 7/2/22.
//

#include "helpers.hpp"


std::string Replace(std::string& s){
    int sz = int(s.size());
    char c;
    std::string res;
    for (int i = 0; i < sz; i++){
        c = s[i];
        switch (c){
            case '{':
                break;
            case '}':
                break;
            case '\"':
                break;
            case ':':
                res.push_back('=');
                break;
            case ',':
                if (s[i - 1] == '"' && s[i + 1] == '"')
                res.push_back('&');
                else{
                    res.push_back(',');
                }
                break;
            default:
                res.push_back(c);
        }
    }
    return res;
}

std::string StringToHex(const std::string& input)
{
    static const char hex_digits[] = "0123456789ABCDEF";

    std::string output;
    output.reserve(input.length() * 2);
    for (unsigned char c : input)
    {
        output.push_back(hex_digits[c >> 4]);
        output.push_back(hex_digits[c & 15]);
    }
    return output;
}

nlohmann::json CleanNoneValue(nlohmann::json params){
    std::vector<std::string> vec;
    for(auto& el : params.items()){
        if (el.value() == NULL){
            vec.push_back(el.value());
        }
    }
    for (auto it : vec){
        params.erase(it);
    }
    return params;
}

std::string PrepareParams(nlohmann::json params){
    return EncodedString(CleanNoneValue(params));
}

std::string EncodedString(nlohmann::json j){
    std::string s = j.dump();
    s = Replace(s);
    return s;
}

using namespace jwt::params;
std::string GetJwtToken(string secretKey, string accountId, string secretKeyId, std::string params){
    std::string digest = "";
    if (params != ""){
        digest = Sha256Single(params);
        //std::cout << digest << std::endl;
    }
    auto millisec_since_epoch = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count() + 60000;
    jwt::jwt_object obj{algorithm("HS256"), headers({
        {"alg", "HS256"},
        {"typ", "JWT"}
    }), secret(secretKey), payload({{"accountId", accountId}})};
    obj.add_claim("secretKeyId", secretKeyId)
        .add_claim("exp", millisec_since_epoch);
    if (digest != ""){
        obj.add_claim("digest", digest);
    }
    auto enc_str = obj.signature();
    //std::cout << "token: " << enc_str << std::endl;
    return enc_str;
}
using json=nlohmann::json;
std::string GetSignature(string secretKey, string accountId, string secretKeyId, std::string params){
    return HmacSha256(secretKey, params);
}
std::string B2aHex(const std::uint8_t *p, std::size_t n) {
    static const char hex[] = "0123456789abcdef";
    std::string res;
    res.reserve(n * 2);

    for ( auto end = p + n; p != end; ++p ) {
        const std::uint8_t v = (*p);
        res += hex[(v >> 4) & 0x0F];
        res += hex[v & 0x0F];
    }

    return res;
}

std::string Sha256Single(const std::string str){
    unsigned char hash[SHA256_DIGEST_LENGTH];
    SHA256_CTX sha256;
    SHA256_Init(&sha256);
    SHA256_Update(&sha256, str.c_str(), str.size());
    SHA256_Final(hash, &sha256);
    std::stringstream ss;
    for(int i = 0; i < SHA256_DIGEST_LENGTH; i++)
    {
        ss << std::hex << std::setw(2) << std::setfill('0') << (int)hash[i];
    }
    //std::cout << ss.str() << std::endl;
    return ss.str();
}

std::string HmacSha256(const std::string key,  const std::string data) {
    std::uint8_t digest[EVP_MAX_MD_SIZE];
    std::uint32_t dilen{};
    char* k = const_cast<char*>(key.c_str());
    char* d = const_cast<char*>(data.c_str());
    std::size_t klen = key.length();
    std::size_t dlen = data.length();
    auto p = ::HMAC(
         ::EVP_sha256()
        ,k
        ,int(klen)
        ,(std::uint8_t *)d
        ,dlen
        ,digest
        ,&dilen
    );
    assert(p);

    return B2aHex(digest, dilen);
}

void SignalCallbackHandler(int signum) {
   std::cout << "Caught signal " << signum << std::endl;
   // Terminate program
   exit(signum);
}

