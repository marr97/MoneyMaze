#include "request_handler.h"
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Stringifier.h>
#include <Poco/Dynamic/Var.h>
#include <sstream>

RequestHandler::RequestHandler(DatabaseManager& dbManager)
    : dbManager(dbManager) {}

RequestHandlerFactory::RequestHandlerFactory(DatabaseManager& dbManager)
    : dbManager(dbManager) {}

Poco::Net::HTTPRequestHandler* RequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request) {
    return new RequestHandler(dbManager);
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

        if (request.getURI() == "/register") {
            bool ok = dbManager.createUser(login, password);
             if (ok) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                responseObj->set("success", true);
            } else {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_CONFLICT);
                responseObj->set("success", false);
                responseObj->set("error", "User already exists");
            }

        } else if (request.getURI() == "/login") {
            auto dbPass = dbManager.getPasswordByUsername(login);
            bool ok = dbPass.has_value() && dbPass.value() == password;
            response.setStatus(ok
                ? Poco::Net::HTTPResponse::HTTP_OK
                : Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED
            );
            responseObj->set("success", ok);
            if (!ok) responseObj->set("error", "Invalid login or password");
        } else {
            responseObj->set("success", false);
            responseObj->set("error", "Unknown endpoint");
        }

        Poco::JSON::Stringifier::stringify(responseObj, out);

    } catch (const std::exception& e) {
        Poco::JSON::Object::Ptr errorObj = new Poco::JSON::Object;
        errorObj->set("success", false);
        errorObj->set("error", std::string("Exception: ") + e.what());
        Poco::JSON::Stringifier::stringify(errorObj, out);
    }
}
