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
    int total_deposit;
};

struct LoanInfo {
    double interest_rate;
    int min_loan_month;
    int max_loan_month;
    int min_loan_amount;
    int max_loan_amount;
};

struct LoanRecord {
    int    id;
    int    amount;
    int    period;
    double rate;
    int    passed_months;
};

struct DepositInfo {
    int current_amount;
    double rate;
    int term_months;
};

class DatabaseManager {
public:
    DatabaseManager();
    ~DatabaseManager();

    bool connect();
    bool disconnect();

    bool createUser(const std::string &username, const std::string &password);
    bool authenticateUser(const std::string &username, const std::string &password);

    bool createFinancialProfile(int user_id);
    std::optional<std::string> getPasswordByUsername(const std::string& username);

    std::optional<FinancialProfile> getFinancialProfile(int user_id);
    bool updateFinancialProfile(int user_id, const FinancialProfile& profile);

    bool createLoan(int user_id, int amount, int period, double rate);
    LoanInfo getLoanInfo(int user_id);
    std::vector<LoanRecord> getUserLoans(int user_id);
    bool updateLoan(const LoanRecord& loan);

    std::optional<DepositInfo> getUserDeposit(int user_id);
    std::optional<int> getUserDepositSum(int user_id);
    bool createDeposit(int user_id, long long principal, int term_months, double rate);

    std::optional<int> getUserIdByUsername(const std::string& username);

private:
    std::unique_ptr<pqxx::connection> conn;
};


