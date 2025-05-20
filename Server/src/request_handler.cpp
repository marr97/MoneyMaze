#include "request_handler.h"
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Stringifier.h>
#include <Poco/Dynamic/Var.h>
#include <sstream>
#include <fstream>
#include <ctime>

RequestHandler::RequestHandler(DatabaseManager& dbManager)
    : dbManager(dbManager) {}

RequestHandlerFactory::RequestHandlerFactory(DatabaseManager& dbManager)
    : dbManager(dbManager) {}

Poco::Net::HTTPRequestHandler* RequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request) {
    return new RequestHandler(dbManager);
}

void RequestLogger::logRequest(RequestLogLevel level, const std::string &message){
    std::string levelStr;
    switch (level) {
        case RequestLogLevel::INFO:    levelStr = "Info"; break;
        case RequestLogLevel::WARNING: levelStr = "Warning"; break;
        case RequestLogLevel::ERROR:   levelStr = "Error"; break;
    }

    std::time_t now = std::time(nullptr);
    char buf[64];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    std::string logMsg = std::string(buf) + " " + levelStr + "| " + message + "\n";
    std::cout << logMsg;
    std::ofstream ofs("application.log", std::ios::app);
    if (ofs.is_open()) ofs << logMsg;
}


void RequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request,
                                   Poco::Net::HTTPServerResponse& response) {
    response.setContentType("application/json");
    response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
    std::ostream& out = response.send();

    try {
        Poco::JSON::Parser parser;
        Poco::Dynamic::Var result = parser.parse(request.stream());
        Poco::JSON::Object::Ptr json = result.extract<Poco::JSON::Object::Ptr>();

        std::string login = json->getValue<std::string>("login");
        std::string password = json->getValue<std::string>("password");

        Poco::JSON::Object::Ptr responseObj = new Poco::JSON::Object;
        
        std::string RequestBody = "login: " + login + " password: " + password + "\n";
        
        if (request.getURI() == "/register") {
            std::string RequestInfo = "Endpoint: '/register' \n" + RequestBody;
            RequestLogger::logRequest(RequestLogLevel::INFO, RequestInfo);

            bool ok = dbManager.createUser(login, password);
             if (ok) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                responseObj->set("success", true);
                
                RequestLogger::logRequest(RequestLogLevel::INFO,
                    "User '" + login + "' successfully registered\n");
            } else {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
                responseObj->set("success", false);
                responseObj->set("error", "User already exists");

                RequestLogger::logRequest(RequestLogLevel::ERROR,
                    "Couldn't register user: '" + login + "'\n");
            }

        } else if (request.getURI() == "/login") {
            auto dbPass = dbManager.getPasswordByUsername(login);
            bool ok = dbPass.has_value() && dbPass.value() == password;

            std::string RequestBody = "login: " + login + " password: " + password + "\n";
            
            std::string RequestInfo = "Endpoint: '/login' \n" + RequestBody;
            RequestLogger::logRequest(RequestLogLevel::INFO, RequestInfo);
            
            if (ok) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                responseObj->set("success", true);

                RequestLogger::logRequest(RequestLogLevel::INFO,
                    "User '" + login + "' successfully logged in\n");

            } else {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
                responseObj->set("success", false);
                responseObj->set("error", "Invalid login or password");

                RequestLogger::logRequest(RequestLogLevel::ERROR,
                    "Couldn't authorize user: '" + login + "'\n");
            }
        } else {
            responseObj->set("success", false);
            responseObj->set("error", "Unknown endpoint");

            RequestLogger::logRequest(RequestLogLevel::WARNING,
                    "Unknown endpoint: " + request.getURI() + "\n");
        }

        Poco::JSON::Stringifier::stringify(responseObj, out);

    } catch (const std::exception& e) {
        Poco::JSON::Object::Ptr errorObj = new Poco::JSON::Object;
        errorObj->set("success", false);
        errorObj->set("error", std::string("Exception: ") + e.what());
        Poco::JSON::Stringifier::stringify(errorObj, out);

        RequestLogger::logRequest(RequestLogLevel::ERROR,
                    "Catch exception: " + e.what() + "\n");
    }
}
