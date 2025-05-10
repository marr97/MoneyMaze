#include "http_client.h"
#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/StreamCopier.h>
#include <sstream>
#include <iostream>

void send_json_to_server(const nlohmann::json& data, const std::string& endpoint) {
    try {
        Poco::Net::HTTPClientSession session("89.169.154.118", 9090);
        Poco::Net::HTTPRequest request(Poco::Net::HTTPRequest::HTTP_POST, endpoint, Poco::Net::HTTPMessage::HTTP_1_1);
        std::string jsonStr = data.dump();

        request.setContentType("application/json");
        request.setContentLength(jsonStr.length());

        std::ostream& os = session.sendRequest(request);
        os << jsonStr;

        Poco::Net::HTTPResponse response;
        std::istream& is = session.receiveResponse(response);
        std::stringstream responseStream;
        Poco::StreamCopier::copyStream(is, responseStream);


    } catch (const std::exception& e) {
        std::cerr << "Error sending JSON: " << e.what() << "\n";
    }
}

void HttpClient::send_registration_data(const nlohmann::json& data) {
    send_json_to_server(data, "/register");
}

void HttpClient::send_auth_data(const nlohmann::json& data) {
    send_json_to_server(data, "/auth");
}