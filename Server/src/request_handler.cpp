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
            auto json = result.extract<Poco::JSON::Object::Ptr>();

            std::string login = json->getValue<std::string>("login");
            std::string password = json->getValue<std::string>("password");
            RequestLogger::logRequest(RequestLogLevel::INFO,
                "Endpoint: '/register' | Body: { login: " + login + ", password: " + password + " }");

            bool ok = dbManager.createUser(login, password);
            response.setStatus(ok ? Poco::Net::HTTPResponse::HTTP_OK
                                  : Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
            responseObj->set("success", ok);
            if (!ok) responseObj->set("error", "User already exists");

        } else if (uri == "/login") {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(request.stream());
            auto json = result.extract<Poco::JSON::Object::Ptr>();

            std::string login = json->getValue<std::string>("login");
            std::string password = json->getValue<std::string>("password");
            RequestLogger::logRequest(RequestLogLevel::INFO,
                "Endpoint: '/login' | Body: { login: " + login + " }");

            auto dbPass = dbManager.getPasswordByUsername(login);
            bool ok = dbPass.has_value() && dbPass.value() == password;
            response.setStatus(ok ? Poco::Net::HTTPResponse::HTTP_OK
                                  : Poco::Net::HTTPResponse::HTTP_UNAUTHORIZED);
            responseObj->set("success", ok);
            if (!ok) responseObj->set("error", "Invalid login or password");

        } else if (uri == "/financial-profile") {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(request.stream());
            auto json = result.extract<Poco::JSON::Object::Ptr>();

            std::string username = json->getValue<std::string>("username");
            RequestLogger::logRequest(RequestLogLevel::INFO,
                "Endpoint: '/financial-profile' | Body: { username: " + username + " }");

            auto uid = dbManager.getUserIdByUsername(username);
            if (!uid) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                responseObj->set("success", false);
                responseObj->set("error", "User not found");
            } else {
                auto optProfile = dbManager.getFinancialProfile(*uid);
                if (!optProfile) {
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                    responseObj->set("success", false);
                    responseObj->set("error", "Financial profile not found");
                } else {
                    const auto& p = *optProfile;

                    auto depositSum = dbManager.getUserDepositSum(*uid);
                    int totalDeposit = depositSum.value_or(0);

                    responseObj->set("deposits", p.deposits);
                    responseObj->set("balance", p.balance);
                    responseObj->set("monthly_minimum", p.monthly_minimum);
                    responseObj->set("total_loans", p.debt);
                    responseObj->set("total_deposit", totalDeposit);

                    double interest_due = p.debt * 0.15 / 12;
                    responseObj->set("interest_due", interest_due);
                    responseObj->set("salary", p.salary);
                    responseObj->set("current_month", p.played_months);

                    if (p.balance < 0) {
                        responseObj->set("status", "lose");
                        responseObj->set("score", p.played_months);
                    } else if (p.played_months >= 24) {
                        responseObj->set("status", "win");
                        responseObj->set("score", p.balance + p.savings - p.debt);
                    } else {
                        responseObj->set("status", "in_progress");
                    }
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                }
            }

        } else if (uri == "/next-month") {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(request.stream());
            auto json = result.extract<Poco::JSON::Object::Ptr>();

            std::string username = json->getValue<std::string>("username");
            RequestLogger::logRequest(RequestLogLevel::INFO,
                "Endpoint: '/next-month' | Body: { username: " + username + " }");

            auto uid = dbManager.getUserIdByUsername(username);
            if (!uid) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                responseObj->set("success", false);
                responseObj->set("error", "User not found");
            } else {
                auto optProfile = dbManager.getFinancialProfile(*uid);
                if (!optProfile) {
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                    responseObj->set("success", false);
                    responseObj->set("error", "Financial profile not found");
                } else {
                    auto p = *optProfile;
                    if (p.played_months >= 24) {
                        response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
                        responseObj->set("success", false);
                        responseObj->set("error", "Game already finished");
                        std::ostream& out = response.send();
                        Poco::JSON::Stringifier::stringify(responseObj, out);
                        return;
                    }

                    p.balance = p.balance - p.monthly_minimum + p.salary;
                    p.played_months += 1;

                    auto userLoans = dbManager.getUserLoans(*uid);
                    Poco::JSON::Array::Ptr paymentsArr = new Poco::JSON::Array;
                    double totalInterest = 0.0;
                    int totalPrincipal = 0;

                    for (auto& loan : userLoans) {
                        if (loan.passed_months < loan.period) {
                            double monthlyInterest = loan.amount * (loan.rate / 100 / 12);
                            totalInterest += monthlyInterest;

                            int monthsLeft = loan.period - loan.passed_months;
                            double principalPayment = loan.amount / monthsLeft;
                            totalPrincipal += static_cast<int>(principalPayment);

                            loan.amount -= principalPayment;
                            if (loan.amount < 0) loan.amount = 0;
                            loan.passed_months += 1;

                            Poco::JSON::Object::Ptr payment = new Poco::JSON::Object;
                            payment->set("loan_id", loan.id);
                            payment->set("principal", static_cast<int>(principalPayment));
                            payment->set("interest", monthlyInterest);
                            paymentsArr->add(payment);

                            dbManager.updateLoan(loan);
                        }
                    }

                    int totalPayment = static_cast<int>(totalInterest) + totalPrincipal;
                    p.balance -= totalPayment;

                    int newDebt = 0;
                    for (const auto& loan : userLoans) {
                        newDebt += static_cast<int>(loan.amount);
                    }
                    p.debt = newDebt;
                    dbManager.updateFinancialProfile(*uid, p);

                    auto deposits = dbManager.getUserDeposits(*uid);
                    double totalDepositInterest = 0.0;
                    long long newTotalDeposit = 0;

                    for (auto& deposit : deposits) {
                        if (deposit.passed_months < deposit.term_months) {
                            double monthlyInterest = deposit.principal * (deposit.rate / 100 / 12);
                            totalDepositInterest += monthlyInterest;
                            deposit.passed_months += 1;
                            
                            deposit.current_amount = static_cast<long long>(
                                deposit.principal * pow(1 + deposit.rate/100/12, deposit.passed_months)
                            );
                            
                            bool depositUpdated = dbManager.createDeposit(
                                *uid, 
                                deposit.current_amount, 
                                deposit.term_months - deposit.passed_months, 
                                deposit.rate
                            );
                                    
                            if (!depositUpdated) {
                                Logger::log(LogLevel::ERROR, "Failed to update deposit for user " + std::to_string(*uid));
                            }
                        }
                        newTotalDeposit += deposit.current_amount;
                    }

                    p.balance += static_cast<int>(totalDepositInterest);
                    p.total_deposit = newTotalDeposit;

                    p.debt = std::accumulate(userLoans.begin(), userLoans.end(), 0,
                        [](int sum, const LoanRecord& loan) {
                            return sum + static_cast<int>(loan.amount);
                        });

                    dbManager.updateFinancialProfile(*uid, p);

                    responseObj->set("payments", paymentsArr);
                    responseObj->set("total_interest", totalInterest);
                    responseObj->set("total_principal", totalPrincipal);
                    responseObj->set("deposit_interest", totalDepositInterest);
                    responseObj->set("new_balance", p.balance);
                    responseObj->set("new_debt", p.debt);
                    responseObj->set("new_total_deposit", p.total_deposit);
                    responseObj->set("success", true);
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                }
            }
        } else if (uri == "/loan-info") {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(request.stream());
            auto json = result.extract<Poco::JSON::Object::Ptr>();

            std::string username = json->getValue<std::string>("username");
            RequestLogger::logRequest(RequestLogLevel::INFO,
                "Endpoint: '/loan-info' | Body: { username: " + username + " }");

            auto uid = dbManager.getUserIdByUsername(username);
            if (!uid) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                responseObj->set("success", false);
                responseObj->set("error", "User not found");
            } else {
                LoanInfo info = dbManager.getLoanInfo(*uid);
                responseObj->set("min_loan_amount",    info.min_loan_amount);
                responseObj->set("max_loan_amount",    info.max_loan_amount);
                responseObj->set("interest_rate",      info.interest_rate);
                responseObj->set("min_loan_month",     info.min_loan_month);
                responseObj->set("max_loan_month",     info.max_loan_month);
                response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            }
        } else if (uri == "/deposit") {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(request.stream());
            auto json = result.extract<Poco::JSON::Object::Ptr>();

            std::string username = json->getValue<std::string>("username");
            double amount = json->getValue<double>("amount");
            double rate = json->getValue<double>("rate");
            int period = json->getValue<int>("period");
            
            RequestLogger::logRequest(RequestLogLevel::INFO,
                "Endpoint: '/deposit' | Body: { username: " + username +
                ", amount: " + std::to_string(amount) +
                ", rate: " + std::to_string(rate) +
                ", period: " + std::to_string(period) + " }");

            auto uid = dbManager.getUserIdByUsername(username);
            if (!uid) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                responseObj->set("success", false);
                responseObj->set("error", "User not found");
            } else {
                bool depositCreated = dbManager.createDeposit(*uid, static_cast<long long>(amount), period, rate);
                
                if (!depositCreated) {
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
                    responseObj->set("success", false);
                    responseObj->set("error", "Failed to create deposit");
                } else {
                    auto optProfile = dbManager.getFinancialProfile(*uid);
                    if (!optProfile) {
                        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
                        responseObj->set("success", false);
                        responseObj->set("error", "Failed to get updated profile");
                    } else {
                        const auto& p = *optProfile;
                        responseObj->set("deposits", p.deposits);
                        responseObj->set("balance", p.balance);
                        responseObj->set("total_deposit", p.total_deposit);
                        responseObj->set("success", true);
                        response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                    }
                }
            }
        } else if (uri == "/user-deposit") {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(request.stream());
            auto json = result.extract<Poco::JSON::Object::Ptr>();

            std::string username = json->getValue<std::string>("username");
            RequestLogger::logRequest(RequestLogLevel::INFO,
                "Endpoint: '/user-deposit' | Body: { username: " + username + " }");

            auto uid = dbManager.getUserIdByUsername(username);
            if (!uid) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                responseObj->set("success", false);
                responseObj->set("error", "User not found");
            } else {
                auto deposits = dbManager.getUserDeposits(*uid);
                if (deposits.empty()) {
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                    responseObj->set("success", false);
                    responseObj->set("error", "No active deposits found");
                } else {
                    Poco::JSON::Array::Ptr depositsArr = new Poco::JSON::Array;
                    for (const auto& deposit : deposits) {
                        Poco::JSON::Object::Ptr depositObj = new Poco::JSON::Object;
                        depositObj->set("id", deposit.id);
                        depositObj->set("principal", deposit.principal);
                        depositObj->set("current_amount", deposit.current_amount);
                        depositObj->set("rate", deposit.rate);
                        depositObj->set("term_months", deposit.term_months);
                        depositObj->set("passed_months", deposit.passed_months);
                        depositObj->set("start_date", deposit.start_date);
                        depositsArr->add(depositObj);
                    }
                    
                    responseObj->set("deposits", depositsArr);
                    responseObj->set("success", true);
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
                }
            }
        } else if (uri == "/take-loan") {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(request.stream());
            auto json = result.extract<Poco::JSON::Object::Ptr>();

            std::string username = json->getValue<std::string>("username");
            int amount  = json->getValue<int>("amount");
            int period  = json->getValue<int>("period");
            double rate = json->getValue<double>("rate");

            RequestLogger::logRequest(RequestLogLevel::INFO,
                "Endpoint: '/take-loan' | Body: { username: " + username +
                ", amount: " + std::to_string(amount) +
                ", period: " + std::to_string(period) +
                ", rate: " + std::to_string(rate) + " }");

            auto uid = dbManager.getUserIdByUsername(username);
            if (!uid) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                responseObj->set("success", false);
                responseObj->set("error", "User not found");
            } else {
                auto optProfile = dbManager.getFinancialProfile(*uid);
                if (!optProfile) {
                    response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                    responseObj->set("success", false);
                    responseObj->set("error", "Financial profile not found");
                } else {
                    auto p = *optProfile;
                    int remaining_months = 24 - p.played_months;
                    if (period > remaining_months) {
                        response.setStatus(Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
                        responseObj->set("success", false);
                        responseObj->set("error", "Loan period exceeds remaining game time");
                    } else {
                        bool ok = dbManager.createLoan(*uid, amount, period, rate);
                        response.setStatus(ok ? Poco::Net::HTTPResponse::HTTP_OK
                                            : Poco::Net::HTTPResponse::HTTP_BAD_REQUEST);
                        responseObj->set("success", ok);
                        if (!ok) responseObj->set("error", "Loan could not be created");
                    }
                }
            }
        } else if (uri == "/user-loans") {
            Poco::JSON::Parser parser;
            Poco::Dynamic::Var result = parser.parse(request.stream());
            auto json = result.extract<Poco::JSON::Object::Ptr>();

            std::string username = json->getValue<std::string>("username");
            RequestLogger::logRequest(RequestLogLevel::INFO,
                "Endpoint: '/user-loans' | Body: { username: " + username + " }");

            auto uid = dbManager.getUserIdByUsername(username);
            if (!uid) {
                response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
                responseObj->set("success", false);
                responseObj->set("error", "User not found");
            } else {
                auto loans = dbManager.getUserLoans(*uid);
                Poco::JSON::Array::Ptr arr = new Poco::JSON::Array;
                for (auto &ln : loans) {
                    Poco::JSON::Object::Ptr obj = new Poco::JSON::Object;
                    obj->set("id",            ln.id);
                    obj->set("amount",        ln.amount);
                    obj->set("period",        ln.period);
                    obj->set("rate",          ln.rate);
                    obj->set("passed_months", ln.passed_months);
                    arr->add(obj);
                }
                responseObj->set("success", true);
                responseObj->set("loans", arr);
                response.setStatus(Poco::Net::HTTPResponse::HTTP_OK);
            }
        } else {
            response.setStatus(Poco::Net::HTTPResponse::HTTP_NOT_FOUND);
            responseObj->set("success", false);
            responseObj->set("error", "Unknown endpoint");
        }

        std::ostream& out = response.send();
        Poco::JSON::Stringifier::stringify(responseObj, out);

    } catch (const std::exception& e) {
        response.setStatus(Poco::Net::HTTPResponse::HTTP_INTERNAL_SERVER_ERROR);
        Poco::JSON::Object::Ptr errorObj = new Poco::JSON::Object;
        errorObj->set("success", false);
        errorObj->set("error",   e.what());
        RequestLogger::logRequest(RequestLogLevel::ERROR,
            std::string("Exception caught: ") + e.what());

        std::ostream& out = response.send();
        Poco::JSON::Stringifier::stringify(errorObj, out);
    }
}
