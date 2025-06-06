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
    std::string LogMessage;

    try {
        Poco::JSON::Object::Ptr responseObj = new Poco::JSON::Object;
        std::string ReplyBody;

        if (request.getURI() == "/register") {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(request.stream());
            Poco::JSON::Object::Ptr json = result.extract<Poco::JSON::Object::Ptr>();
            
            std::string login = json->getValue<std::string>("login");
            std::string password = json->getValue<std::string>("password");

            std::string RequestBody = "Body: { login: " + login + ",  password: " + password + " }";
            
            std::string RequestInfo = "Endpoint: '/register' | " + RequestBody;
            RequestLogger::logRequest(RequestLogLevel::INFO, RequestInfo);

            bool ok = dbManager.createUser(login, password);
             if (ok) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                responseObj->set("success", true);

                LogMessage = "User '" + login + "' successfully registered";
                RequestLogger::logRequest(RequestLogLevel::INFO, LogMessage);

                ReplyBody = " OK | HTTP status code = " + std::to_string(Poco::Net::HTTPResponse::HTTP_OK);
                RequestLogger::logRequest(RequestLogLevel::REPLYINFO, ReplyBody);
            } else {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
                responseObj->set("success", false);
                responseObj->set("error", "User already exists");

                LogMessage = "Couldn't register user: '" + login + "'";
                RequestLogger::logRequest(RequestLogLevel::ERROR, LogMessage);

                ReplyBody = "'User already exists' | HTTP status code = " + std::to_string(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
                RequestLogger::logRequest(RequestLogLevel::REPLYINFO, ReplyBody);
            }

        } else if (request.getURI() == "/login") {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(request.stream());
            Poco::JSON::Object::Ptr json = result.extract<Poco::JSON::Object::Ptr>();
            
            std::string login = json->getValue<std::string>("login");
            std::string password = json->getValue<std::string>("password");

            std::string RequestBody = "Body: { login: " + login + ",  password: " + password + " }";
            
            auto dbPass = dbManager.getPasswordByUsername(login);
            bool ok = dbPass.has_value() && dbPass.value() == password;
            
            std::string RequestInfo = "Endpoint: '/login' | " + RequestBody;
            RequestLogger::logRequest(RequestLogLevel::INFO, RequestInfo);
            
            if (ok) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                responseObj->set("success", true);
                
                LogMessage = "User '" + login + "' successfully logged in";
                RequestLogger::logRequest(RequestLogLevel::INFO, LogMessage);

                ReplyBody = " OK | HTTP status code = " + std::to_string(Poco::Net::HTTPResponse::HTTP_OK);
                RequestLogger::logRequest(RequestLogLevel::REPLYINFO, ReplyBody);

            } else {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
                responseObj->set("success", false);
                responseObj->set("error", "Invalid login or password");

                LogMessage = "Couldn't authorize user: '" + login + "'";
                RequestLogger::logRequest(RequestLogLevel::ERROR, LogMessage);

                ReplyBody = " 'Invalid login or password' | HTTP status code = " + std::to_string(Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
                RequestLogger::logRequest(RequestLogLevel::REPLYINFO, ReplyBody);
            }
        } else if (request.getURI() == "/financial-profile") {
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
                response.send() << "User not found";
                return;
            }
            int user_id = user_id_opt.value();
            
            if (auto profile = dbManager.getFinancialProfile(user_id)) {
                Poco::JSON::Object::Ptr responseObj = new Poco::JSON::Object;
                responseObj->set("balance", profile->balance);
                responseObj->set("monthly_minimum", profile->monthly_minimum);
                responseObj->set("total_loans", profile->debt);
                
                // Рассчет процентов (примерная логика)
                double interest_due = profile->debt * 0.15 / 12;
                responseObj->set("interest_due", interest_due);
                responseObj->set("salary", profile->salary);
                responseObj->set("current_month", profile->played_months);
                
                // Проверка условий игры
                if (profile->balance < 0) {
                    responseObj->set("status", "lose");
                    responseObj->set("score", profile->played_months);
                } else if (profile->played_months >= 12) { // 12 месяцев - условие победы
                    responseObj->set("status", "win");
                    responseObj->set("score", profile->balance + profile->savings - profile->debt);
                } else {
                    responseObj->set("status", "in_progress");
                }
                
                response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                std::ostream& out = response.send();
                Poco::JSON::Stringifier::stringify(responseObj, out);
                
                LogMessage = "Financial profile '" + username + "' successfully send";
                RequestLogger::logRequest(RequestLogLevel::INFO, LogMessage);

                ReplyBody = " OK | HTTP status code = " + std::to_string(Poco::Net::HTTPResponse::HTTP_OK);
                RequestLogger::logRequest(RequestLogLevel::REPLYINFO, ReplyBody);
                
            } else {
                // Обработка ошибки
            }
        } else if (request.getURI() == "/next-month") {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(request.stream());
            Poco::JSON::Object::Ptr json = result.extract<Poco::JSON::Object::Ptr>();
            
            std::string username = json->getValue<std::string>("username");
            auto user_id_opt = dbManager.getUserIdByUsername(username);
            if (!user_id_opt) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                response.send() << "User not found";
                return;
            }
            int user_id = user_id_opt.value();
            
            if (auto profile = dbManager.getFinancialProfile(user_id)) {
                // Рассчет процентов
                double interest_due = profile->debt * 0.15 / 12;
                
                // Обновление баланса
                profile->balance = profile->balance - profile->monthly_minimum - interest_due + profile->salary;
                profile->played_months++;
                
                dbManager.updateFinancialProfile(user_id, *profile);
                response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            } else {
                // Обработка ошибки
            }
        } else if (request.getURI() == "/loan-info") {
            auto loanInfo = dbManager.getLoanInfo();
            
            Poco::JSON::Object::Ptr responseObj = new Poco::JSON::Object;
            responseObj->set("interest_rate", loanInfo.interest_rate);
            responseObj->set("min_loan_month", loanInfo.min_loan_month);
            responseObj->set("max_loan_month", loanInfo.max_loan_month);
            responseObj->set("min_loan_amount", loanInfo.min_loan_amount);
            responseObj->set("max_loan_amount", loanInfo.max_loan_amount);
            
            response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            std::ostream& out = response.send();
            Poco::JSON::Stringifier::stringify(responseObj, out);
        } else if (request.getURI() == "/take-loan") {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(request.stream());
            Poco::JSON::Object::Ptr json = result.extract<Poco::JSON::Object::Ptr>();
            
            std::string username = json->getValue<std::string>("username");
            int period = json->getValue<int>("loan_period");
            int amount = json->getValue<int>("loan_amount");
            auto user_id_opt = dbManager.getUserIdByUsername(username);
            if (!user_id_opt) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                response.send() << "User not found";
                return;
            }
            int user_id = user_id_opt.value();
            
            auto loanInfo = dbManager.getLoanInfo();
            if (amount < loanInfo.min_loan_amount || amount > loanInfo.max_loan_amount ||
                period < loanInfo.min_loan_month || period > loanInfo.max_loan_month) {
                // Обработка невалидных параметров
                response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            } else {
                dbManager.createLoan(user_id, amount, period, loanInfo.interest_rate);
                response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            }
        } else {
            responseObj->set("success", false);
            responseObj->set("error", "Unknown endpoint");

            LogMessage = "Unknown endpoint: " + request.getURI();
            RequestLogger::logRequest(RequestLogLevel::WARNING, LogMessage);
        }
        
        std::ostream& out = response.send();
        Poco::JSON::Stringifier::stringify(responseObj, out);

    } catch (const std::exception& e) {
        Poco::JSON::Object::Ptr errorObj = new Poco::JSON::Object;
        errorObj->set("success", false);
        errorObj->set("error", std::string("Exception: ") + e.what());
        
        std::ostream& out = response.send();
        Poco::JSON::Stringifier::stringify(errorObj, out);

        std::ostringstream ExceptionInfo;
        ExceptionInfo << "Catch exception: " << e.what();
        RequestLogger::logRequest(RequestLogLevel::ERROR, ExceptionInfo.str());
    }
}
