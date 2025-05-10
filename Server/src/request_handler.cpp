#include "request_handler.h"
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>

void RequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request, Poco::Net::HTTPServerResponse& response) {
    response.setContentType("text/plain");
    response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
    
    std::ostream& ostr = response.send();
    ostr << "это прилетел ответ с сервера";
}

Poco::Net::HTTPRequestHandler* RequestHandlerFactory::createRequestHandler(const Poco::Net::HTTPServerRequest& request) {
    return new RequestHandler;
}
