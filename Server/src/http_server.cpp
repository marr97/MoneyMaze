#include "http_server.h"
#include "request_handler.h"
#include <Poco/Net/ServerSocket.h>
#include <Poco/Net/HTTPServerParams.h>
#include <Poco/Net/HTTPServer.h>
#include <iostream>

HttpServer::HttpServer(int port)
    : port(port),
      server(nullptr),
      emailSender_(initEmailSenderFromEnv())
{}

EmailSender HttpServer::initEmailSenderFromEnv() {
    std::string smtpHost = "smtp.yandex.ru";
    int smtpPort = 465;
    std::string smtpUser = "m0neymaze.project@yandex.ru";
    std::string smtpPass = "hiuuerxjorpyrtzo";
    return EmailSender(smtpHost, smtpPort, smtpUser, smtpPass);
}

void HttpServer::start() {
    try {
        if (!dbManager.connect()) {
            std::cerr << "DB connection failed, server not started\n";
            return;
        }
        
        Poco::Net::ServerSocket serverSocket(port);

        Poco::Net::HTTPServerParams* params = new Poco::Net::HTTPServerParams;
        params->setMaxThreads(16);

        auto* factory = new RequestHandlerFactory(dbManager, emailSender_);
        server = new Poco::Net::HTTPServer(
            factory,
            serverSocket,
            params
        );
        server->start();
        std::cout << "Server started on port " << port << "\n";

    } catch (const std::exception& e) {
        std::cerr << "Error starting server: " << e.what() << "\n";
    }
}

void HttpServer::stop() {
    if (server) {
        server->stop();
        std::cout << "Server stopped\n";
    }
}
