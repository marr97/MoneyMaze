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
    char buf[101];
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
    std::string LogMessage;

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
                
                LogMessage = "User '" + login + "' successfully registered\n";
                RequestLogger::logRequest(RequestLogLevel::INFO, LogMessage);
            } else {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
                responseObj->set("success", false);
                responseObj->set("error", "User already exists");

                LogMessage = "Couldn't register user: '" + login + "'\n";
                RequestLogger::logRequest(RequestLogLevel::ERROR, LogMessage);
            }

        } else if (request.getURI() == "/login") {
            auto dbPass = dbManager.getPasswordByUsername(login);
            bool ok = dbPass.has_value() && dbPass.value() == password;
            
            std::string RequestInfo = "Endpoint: '/login' \n" + RequestBody;
            RequestLogger::logRequest(RequestLogLevel::INFO, RequestInfo);
            
            if (ok) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                responseObj->set("success", true);
                
                LogMessage = "User '" + login + "' successfully logged in\n";
                RequestLogger::logRequest(RequestLogLevel::INFO, LogMessage);

            } else {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
                responseObj->set("success", false);
                responseObj->set("error", "Invalid login or password");

                LogMessage = "Couldn't authorize user: '" + login + "'\n";
                RequestLogger::logRequest(RequestLogLevel::ERROR, LogMessage);
            }
        } else {
            responseObj->set("success", false);
            responseObj->set("error", "Unknown endpoint");

            LogMessage = "Unknown endpoint: " + request.getURI() + "\n";
            RequestLogger::logRequest(RequestLogLevel::WARNING, LogMessage);
        }

        Poco::JSON::Stringifier::stringify(responseObj, out);

    } catch (const std::exception& e) {
        Poco::JSON::Object::Ptr errorObj = new Poco::JSON::Object;
        errorObj->set("success", false);
        errorObj->set("error", std::string("Exception: ") + e.what());
        Poco::JSON::Stringifier::stringify(errorObj, out);

        LogMessage = "Catch exception: " + e.what() + "\n";
        RequestLogger::logRequest(RequestLogLevel::ERROR, LogMessage);
    }
}
