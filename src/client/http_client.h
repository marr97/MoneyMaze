#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <nlohmann/json.hpp>

using json = nlohmann::json;

class HttpClient {
public:
    static void send_registration_data(const json& data);
    static void send_auth_data(const json& data);
};

#endif HTTP_CLIENT_H // HTTP_CLIENT_H