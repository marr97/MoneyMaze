#include "request_handler.h"
#include <Poco/Net/HTTPServerRequest.h>
#include <Poco/Net/HTTPServerResponse.h>
#include <Poco/JSON/Parser.h>
#include <Poco/JSON/Object.h>
#include <Poco/JSON/Stringifier.h>
#include <Poco/Dynamic/Var.h>
#include <sstream>
#include <fstream>
#include <cstdlib>
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
        case RequestLogLevel::REPLYINFO:    levelStr = "Reply Info"; break;
        case RequestLogLevel::WARNING: levelStr = "Warning"; break;
        case RequestLogLevel::ERROR:   levelStr = "Error"; break;
    }

    setenv("TZ", "Europe/Moscow", 1);
    tzset(); 

    std::time_t now = std::time(nullptr);
    char buf[101];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    std::string logMsg = std::string(buf) + " [" + levelStr + "] " + message + "\n";
    std::cout << logMsg;
    std::ofstream ofs("application.log", std::ios::app);
    if (ofs.is_open()) ofs << logMsg;
}


void RequestHandler::handleRequest(Poco::Net::HTTPServerRequest& request,
                                   Poco::Net::HTTPServerResponse& response) {
    response.setContentType("application/json");
    Poco::JSON::Object::Ptr responseObj = new Poco::JSON::Object;

    try {
        const std::string& uri = request.getURI();

        if (uri == "/register") {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(request.stream());
            Poco::JSON::Object::Ptr json = result.extract<Poco::JSON::Object::Ptr>();

            std::string login = json->getValue<std::string>("login");
            std::string password = json->getValue<std::string>("password");

            std::string RequestBody = "Body: { login: " + login + ", password: " + password + " }";
            std::string RequestInfo = "Endpoint: '/register' | " + RequestBody;
            RequestLogger::logRequest(RequestLogLevel::INFO, RequestInfo);

            bool ok = dbManager.createUser(login, password);
            if (ok) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                responseObj->set("success", true);

                RequestLogger::logRequest(RequestLogLevel::INFO, "User '" + login + "' successfully registered");
                RequestLogger::logRequest(RequestLogLevel::REPLYINFO, "OK | HTTP status code = " + std::to_string(Poco::Net::HTTPResponse::HTTP_OK));
            } else {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
                responseObj->set("success", false);
                responseObj->set("error", "User already exists");

                RequestLogger::logRequest(RequestLogLevel::ERROR, "Couldn't register user: '" + login + "'");
                RequestLogger::logRequest(RequestLogLevel::REPLYINFO, "'User already exists' | HTTP status code = " + std::to_string(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST));
            }
        }
        else if (uri == "/login") {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(request.stream());
            Poco::JSON::Object::Ptr json = result.extract<Poco::JSON::Object::Ptr>();

            std::string login = json->getValue<std::string>("login");
            std::string password = json->getValue<std::string>("password");

            std::string RequestBody = "Body: { login: " + login + ", password: " + password + " }";
            std::string RequestInfo = "Endpoint: '/login' | " + RequestBody;
            RequestLogger::logRequest(RequestLogLevel::INFO, RequestInfo);

            auto dbPass = dbManager.getPasswordByUsername(login);
            bool ok = dbPass.has_value() && dbPass.value() == password;

            if (ok) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                responseObj->set("success", true);

                RequestLogger::logRequest(RequestLogLevel::INFO, "User '" + login + "' successfully logged in");
                RequestLogger::logRequest(RequestLogLevel::REPLYINFO, "OK | HTTP status code = " + std::to_string(Poco::Net::HTTPResponse::HTTP_OK));
            } else {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
                responseObj->set("success", false);
                responseObj->set("error", "Invalid login or password");

                RequestLogger::logRequest(RequestLogLevel::ERROR, "Couldn't authorize user: '" + login + "'");
                RequestLogger::logRequest(RequestLogLevel::REPLYINFO, "'Invalid login or password' | HTTP status code = " + std::to_string(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED));
            }
        }
        else if (uri == "/financial-profile") {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(request.stream());
            Poco::JSON::Object::Ptr json = result.extract<Poco::JSON::Object::Ptr>();

            std::string username = json->getValue<std::string>("username");
            std::string RequestBody = "Body: { username: " + username + " }";
            std::string RequestInfo = "Endpoint: '/financial-profile' | " + RequestBody;
            RequestLogger::logRequest(RequestLogLevel::INFO, RequestInfo);

            auto user_id_opt = dbManager.getUserIdByUsername(username);
            if (!user_id_opt) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                responseObj->set("success", false);
                responseObj->set("error", "User not found");

                RequestLogger::logRequest(RequestLogLevel::ERROR, "User not found: '" + username + "'");
            } else {
                int user_id = user_id_opt.value();
                auto profile = dbManager.getFinancialProfile(user_id);

                if (profile) {
                    responseObj->set("balance", profile->balance);
                    responseObj->set("monthly_minimum", profile->monthly_minimum);
                    responseObj->set("total_loans", profile->debt);

                    double interest_due = profile->debt * 0.15 / 12;
                    responseObj->set("interest_due", interest_due);
                    responseObj->set("salary", profile->salary);
                    responseObj->set("current_month", profile->played_months);

                    if (profile->balance < 0) {
                        responseObj->set("status", "lose");
                        responseObj->set("score", profile->played_months);
                    } else if (profile->played_months >= 12) {
                        responseObj->set("status", "win");
                        responseObj->set("score", profile->balance + profile->savings - profile->debt);
                    } else {
                        responseObj->set("status", "in_progress");
                    }
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);

                    RequestLogger::logRequest(RequestLogLevel::INFO, "Financial profile '" + username + "' successfully sent");
                    RequestLogger::logRequest(RequestLogLevel::REPLYINFO, "OK | HTTP status code = " + std::to_string(Poco::Net::HTTPResponse::HTTP_OK));
                } else {
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                    responseObj->set("success", false);
                    responseObj->set("error", "Financial profile not found");

                    RequestLogger::logRequest(RequestLogLevel::ERROR, "Financial profile not found for user: '" + username + "'");
                }
            }
        }
        else if (uri == "/next-month") {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(request.stream());
            Poco::JSON::Object::Ptr json = result.extract<Poco::JSON::Object::Ptr>();

            std::string username = json->getValue<std::string>("username");
            auto user_id_opt = dbManager.getUserIdByUsername(username);
            if (!user_id_opt) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                responseObj->set("success", false);
                responseObj->set("error", "User not found");

                RequestLogger::logRequest(RequestLogLevel::ERROR, "User not found: '" + username + "'");
            } else {
                int user_id = user_id_opt.value();
                auto profile = dbManager.getFinancialProfile(user_id);

                if (profile) {
                    double interest_due = profile->debt * 0.15 / 12;
                    profile->balance = profile->balance - profile->monthly_minimum - interest_due + profile->salary;
                    profile->played_months++;

                    dbManager.updateFinancialProfile(user_id, *profile);
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                    responseObj->set("success", true);

                    RequestLogger::logRequest(RequestLogLevel::INFO, "Next month updated for user '" + username + "'");
                    RequestLogger::logRequest(RequestLogLevel::REPLYINFO, "OK | HTTP status code = " + std::to_string(Poco::Net::HTTPResponse::HTTP_OK));
                } else {
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                    responseObj->set("success", false);
                    responseObj->set("error", "Financial profile not found");

                    RequestLogger::logRequest(RequestLogLevel::ERROR, "Financial profile not found for user: '" + username + "'");
                }
            }
        }
        else if (uri == "/loan-info") {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(request.stream());
            Poco::JSON::Object::Ptr json = result.extract<Poco::JSON::Object::Ptr>();

            std::string username = json->getValue<std::string>("username");
            auto user_id_opt = dbManager.getUserIdByUsername(username);

            if (!user_id_opt) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                responseObj->set("success", false);
                responseObj->set("error", "User not found");

                RequestLogger::logRequest(RequestLogLevel::ERROR, "User not found: '" + username + "'");
            } else {
                int user_id = user_id_opt.value();
                auto profile = dbManager.getFinancialProfile(user_id);

                if (profile) {
                    double interest_due = profile->debt * 0.15 / 12;

                    responseObj->set("loan_amount", profile->debt);
                    responseObj->set("interest_due", interest_due);
                    responseObj->set("loan_term", 12);
                    responseObj->set("loan_repayment_status", profile->played_months);

                    response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);

                    RequestLogger::logRequest(RequestLogLevel::INFO, "Loan info sent for user '" + username + "'");
                    RequestLogger::logRequest(RequestLogLevel::REPLYINFO, "OK | HTTP status code = " + std::to_string(Poco::Net::HTTPResponse::HTTP_OK));
                } else {
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                    responseObj->set("success", false);
                    responseObj->set("error", "Financial profile not found");

                    RequestLogger::logRequest(RequestLogLevel::ERROR, "Financial profile not found for user: '" + username + "'");
                }
            }
        }
        else if (uri == "/deposit") {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(request.stream());
            Poco::JSON::Object::Ptr json = result.extract<Poco::JSON::Object::Ptr>();

            std::string username = json->getValue<std::string>("username");
            double amount = json->getValue<double>("amount");

            auto user_id_opt = dbManager.getUserIdByUsername(username);
            if (!user_id_opt) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                responseObj->set("success", false);
                responseObj->set("error", "User not found");

                RequestLogger::logRequest(RequestLogLevel::ERROR, "User not found: '" + username + "'");
            } else {
                int user_id = user_id_opt.value();
                auto profile = dbManager.getFinancialProfile(user_id);
                if (profile) {
                    profile->balance += amount;
                    dbManager.updateFinancialProfile(user_id, *profile);

                    response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                    responseObj->set("success", true);

                    RequestLogger::logRequest(RequestLogLevel::INFO, "Deposit successful for user '" + username + "'");
                    RequestLogger::logRequest(RequestLogLevel::REPLYINFO, "OK | HTTP status code = " + std::to_string(Poco::Net::HTTPResponse::HTTP_OK));
                } else {
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                    responseObj->set("success", false);
                    responseObj->set("error", "Financial profile not found");

                    RequestLogger::logRequest(RequestLogLevel::ERROR, "Financial profile not found for user: '" + username + "'");
                }
            }
        }
        else {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
            responseObj->set("success", false);
            responseObj->set("error", "Unknown endpoint");

            RequestLogger::logRequest(RequestLogLevel::WARNING, "Unknown endpoint requested: '" + uri + "'");
        }

        std::ostream& out = response.send();
        Poco::JSON::Stringifier::stringify(responseObj, out);

    } catch (const std::exception& e) {
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        Poco::JSON::Object::Ptr errorObj = new Poco::JSON::Object;
        errorObj->set("success", false);
        errorObj->set("error", e.what());

        std::ostream& out = response.send();
        Poco::JSON::Stringifier::stringify(errorObj, out);

        RequestLogger::logRequest(RequestLogLevel::ERROR, std::string("Exception caught: ") + e.what());
    }
}