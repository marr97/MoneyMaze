#pragma once

#include <pqxx/pqxx>
#include "db_config.h"
#include <memory>
#include <string>
#include <optional> 

enum class LogLevel { DEBUG, INFO, WARNING, ERROR };

class Logger {
public:
    static void log(LogLevel level, const std::string &message);
};

struct FinancialProfile {
    int balance;
    int monthly_minimum;
    int savings;
    int debt;
    int salary;
    int played_months;
    int deposits;
};

struct LoanInfo {
    double interest_rate;
    int min_loan_month;
    int max_loan_month;
    int min_loan_amount;
    int max_loan_amount;
};

class DatabaseManager {
public:
    DatabaseManager();
    ~DatabaseManager();

    bool connect();
    bool disconnect();

    // Методы для работы с пользователями
    bool createUser(const std::string &username, const std::string &password);
    bool authenticateUser(const std::string &username, const std::string &password);

    // Методы для работы с финансовым профилем
    bool createFinancialProfile(int user_id);
    std::optional<std::string> getPasswordByUsername(const std::string& username);

    std::optional<FinancialProfile> getFinancialProfile(int user_id);
    bool updateFinancialProfile(int user_id, const FinancialProfile& profile);
    bool createLoan(int user_id, int amount, int period, double rate);
    LoanInfo getLoanInfo(int user_id);

    std::optional<int> getUserIdByUsername(const std::string& username);

private:
    std::unique_ptr<pqxx::connection> conn;
};


