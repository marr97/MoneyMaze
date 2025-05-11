#pragma once

#include <pqxx/pqxx>
#include "db_config.h"
#include <memory>
#include <string>

enum class LogLevel { DEBUG, INFO, WARNING, ERROR };
enum class FinancialProfile { BALANCE, DAILY_MINIMUM, SAVINGS, DEBT, UNKNOWN_COLUMN };

class Logger {
public:
    static void log(LogLevel level, const std::string &message);
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
    bool createFinancialProfile(
        int user_id,
        int initial_balance,
        int daily_minimum,
        int savings,
        int debt
    );
    bool update_financial_profile(const std::string &column_name, int user_id, int new_value);
    int  get_value_from_financial_profile(const std::string &column_name, int user_id);

private:
    std::unique_ptr<pqxx::connection> conn;
    FinancialProfile financial_profile_column(const std::string &column_name);
};
