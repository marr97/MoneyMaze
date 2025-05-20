#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <iostream>
#include <string>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include "database_manager.h" 

enum class RequestLogLevel { 
    INFO, 
    WARNING, 
    ERROR 
};

class RequestLogger {
public:
    void logRequest(RequestLogLevel level, const std::string &message);
};


class RequestHandler : public Poco::Net::HTTPRequestHandler {
public:
    RequestHandler(DatabaseManager& dbManager);
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override;

private:
    DatabaseManager& dbManager;
};

class RequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {
public:
    RequestHandlerFactory(DatabaseManager& dbManager);
    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request) override;

private:
    DatabaseManager& dbManager;
};

#endif // REQUEST_HANDLER_H
