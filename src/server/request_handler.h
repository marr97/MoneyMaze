#ifndef REQUEST_HANDLER_H
#define REQUEST_HANDLER_H

#include <iostream>
#include <Poco/Net/HTTPRequestHandler.h>
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>

class RequestHandler : public Poco::Net::HTTPRequestHandler {
public:
    void handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) override;
};

class RequestHandlerFactory : public Poco::Net::HTTPRequestHandlerFactory {
public:
    Poco::Net::HTTPRequestHandler* createRequestHandler(const Poco::Net::HTTPServerRequest& request) override;
};

#endif // REQUEST_HANDLER_H
