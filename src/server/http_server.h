#ifndef HTTP_SERVER_H
#define HTTP_SERVER_H

#include <iostream>
#include <Poco/Net/HTTPServer.h>
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Thread.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>

class HttpServer {
public:
    HttpServer(int port);
    void start();
    void stop();

private:
    int port;
    Poco::Net::HTTPServer* server;
};

#endif // HTTP_SERVER_H
