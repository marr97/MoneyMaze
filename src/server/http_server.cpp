#include "http_server.h"
#include "request_handler.h"
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Thread.h>
#include <Poco/Net/HTTPRequestHandlerFactory.h>
#include <Poco/Net/HTTPServer.h>

HttpServer::HttpServer(int port) : port(port), server(nullptr) {}

void HttpServer::start() {
    try {
        Poco::Net::ServerSocket serverSocket(port);

        Poco::Net::HTTPServerParams* params = new Poco::Net::HTTPServerParams;
        params->setMaxThreads(16);

        server = new Poco::Net::HTTPServer(new RequestHandlerFactory, serverSocket, params);
        server->start();
        std::cout << "Server started on port " << port << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Error starting server: " << e.what() << "\n";
    }
}

void HttpServer::stop() {
    if (server) {
        server->stop();
        std::cout << "Server stopped" << "\n";
    }
}
