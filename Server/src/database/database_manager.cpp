#include "database_manager.h"
#include <ctime>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <optional>

void Logger::log(LogLevel level, const std::string &message) {
    std::string levelStr;
    switch (level) {
        case LogLevel::DEBUG:   levelStr = "DEBUG"; break;
        case LogLevel::INFO:    levelStr = "INFO"; break;
        case LogLevel::WARNING: levelStr = "WARNING"; break;
        case LogLevel::ERROR:   levelStr = "ERROR"; break;
    }

    std::time_t now = std::time(nullptr);
    char buf[64];
    std::strftime(buf, sizeof(buf), "%Y-%m-%d %H:%M:%S", std::localtime(&now));
    std::string logMsg = std::string(buf) + " [" + levelStr + "] " + message + "\n";
    std::cout << logMsg;
    std::ofstream ofs("application.log", std::ios::app);
    if (ofs.is_open()) ofs << logMsg;
}

DatabaseManager::DatabaseManager() : conn(nullptr) {}
DatabaseManager::~DatabaseManager() { disconnect(); }

bool DatabaseManager::connect() {
    try {
        std::string connStr =
            "dbname="   + DB_NAME +
            " user="    + DB_USER +
            " password="+ DB_PASSWORD +
            " hostaddr="+ DB_HOST +
            " port="    + DB_PORT;
        conn = std::make_unique<pqxx::connection>(connStr);
        if (!conn->is_open()) {
            Logger::log(LogLevel::ERROR, "Failed to open DB connection.");
            return false;
        }
        Logger::log(LogLevel::INFO, "Connected to database.");

        pqxx::work txn(*conn);

        // Проверка/создание таблицы users
        #pragma GCC diagnostic push //игнорировать устаревший метод exec
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        auto r = txn.exec("SELECT to_regclass('public.users');");
        if (r[0][0].is_null()) {
            txn.exec(R"(
                CREATE TABLE users (
                    id SERIAL PRIMARY KEY,
                    username VARCHAR(255) UNIQUE NOT NULL,
                    password VARCHAR(255) NOT NULL
                );
            )");
            Logger::log(LogLevel::INFO, "Created table 'users'.");
        }
        #pragma GCC diagnostic pop

        // Проверка/создание таблицы financial_profile
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        auto r2 = txn.exec("SELECT to_regclass('public.financial_profile');");
        if (r2[0][0].is_null()) {
            txn.exec(R"(
                CREATE TABLE financial_profile (
                    id SERIAL PRIMARY KEY,
                    user_id INTEGER UNIQUE REFERENCES users(id),
                    balance INTEGER NOT NULL,
                    daily_minimum INTEGER NOT NULL,
                    savings INTEGER NOT NULL,
                    debt INTEGER NOT NULL
                );
            )");
            Logger::log(LogLevel::INFO, "Created table 'financial_profile'.");
        }
        #pragma GCC diagnostic pop

        txn.commit();
        return true;
    } catch (const std::exception &e) {
        Logger::log(LogLevel::ERROR, std::string("Connection error: ") + e.what());
        return false;
    }
}

bool DatabaseManager::disconnect() {
    if (conn) {
        conn.reset();
        Logger::log(LogLevel::INFO, "Disconnected from database.");
        return true;
    }
    return false;
}

bool DatabaseManager::createUser(const std::string &username, const std::string &password) {
    if (!conn || !conn->is_open()) {
        Logger::log(LogLevel::ERROR, "No open DB connection for createUser.");
        return false;
    }
    try {
        pqxx::work txn(*conn);
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        auto r = txn.exec_params(
            "INSERT INTO users (username, password) VALUES ($1, $2) "
            "ON CONFLICT (username) DO NOTHING RETURNING id;",
            username, password
        );
        #pragma GCC diagnostic pop

        txn.commit();
        if (r.empty()) {
            Logger::log(LogLevel::WARNING, "User already exists: " + username);
            return false;
        }
        Logger::log(LogLevel::INFO, "Created user: " + username);
        return true;
    } catch (const std::exception &e) {
        Logger::log(LogLevel::ERROR, std::string("createUser error: ") + e.what());
        return false;
    }
}

// новый метод для входа(получение пароля)

std::optional<std::string> DatabaseManager::getPasswordByUsername(const std::string& username) {
    if (!conn || !conn->is_open()) {
        Logger::log(LogLevel::ERROR, "No open DB connection for getPasswordByUsername.");
        return std::nullopt;
    }
    try {
        pqxx::work txn(*conn);
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        auto r = txn.exec_params("SELECT password FROM users WHERE username = $1;", username);
        #pragma GCC diagnostic pop
        txn.commit();

        if (r.empty()) {
            Logger::log(LogLevel::WARNING, "User not found: " + username);
            return std::nullopt;
        }
        return r[0][0].as<std::string>();
    } catch (const std::exception &e) {
        Logger::log(LogLevel::ERROR, std::string("getPasswordByUsername error: ") + e.what());
        return std::nullopt;
    }
}

bool DatabaseManager::authenticateUser(const std::string &username, const std::string &password) {
    if (!conn || !conn->is_open()) {
        Logger::log(LogLevel::ERROR, "No open DB connection for authenticateUser.");
        return false;
    }
    try {
        pqxx::work txn(*conn);
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        auto r = txn.exec_params(
            "SELECT id FROM users WHERE username = $1 AND password = $2;",
            username, password
        );
        #pragma GCC diagnostic pop
        return !r.empty();
    } catch (const std::exception &e) {
        Logger::log(LogLevel::ERROR, std::string("authenticateUser error: ") + e.what());
        return false;
    }
}

bool DatabaseManager::createFinancialProfile(int user_id, int initial_balance,
                                             int daily_minimum, int savings,
                                             int debt) {
    if (!conn || !conn->is_open()) {
        Logger::log(LogLevel::ERROR, "No open DB connection for createFinancialProfile.");
        return false;
    }
    try {
        pqxx::work txn(*conn);
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        auto r = txn.exec_params(
            "INSERT INTO financial_profile (user_id, balance, daily_minimum, savings, debt) "
            "VALUES ($1, $2, $3, $4, $5) ON CONFLICT (user_id) DO NOTHING RETURNING id;",
            user_id, initial_balance, daily_minimum, savings, debt
        );
        #pragma GCC diagnostic pop
        txn.commit();
        if (r.empty()) {
            Logger::log(LogLevel::WARNING, "Profile exists for user_id: " + std::to_string(user_id));
            return false;
        }
        Logger::log(LogLevel::INFO, "Created financial profile for user_id: " + std::to_string(user_id));
        return true;
    } catch (const std::exception &e) {
        Logger::log(LogLevel::ERROR, std::string("createFinancialProfile error: ") + e.what());
        return false;
    }
}

bool DatabaseManager::update_financial_profile(const std::string &column_name, int user_id, int new_value) {
    if (!conn || !conn->is_open()) {
        Logger::log(LogLevel::ERROR, "No open DB connection for update_financial_profile.");
        return false;
    }
    try {
        FinancialProfile col = financial_profile_column(column_name);
        std::string field;
        switch (col) {
            case FinancialProfile::BALANCE:       field = "balance"; break;
            case FinancialProfile::DAILY_MINIMUM: field = "daily_minimum"; break;
            case FinancialProfile::SAVINGS:       field = "savings"; break;
            case FinancialProfile::DEBT:          field = "debt"; break;
            default:
                Logger::log(LogLevel::WARNING, "Unknown column: " + column_name);
                return false;
        }
        pqxx::work txn(*conn);
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        auto r = txn.exec_params(
            "UPDATE financial_profile SET " + field + " = $2 WHERE user_id = $1 RETURNING id;",
            user_id, new_value
        );
        #pragma GCC diagnostic pop
        txn.commit();
        if (r.empty()) {
            Logger::log(LogLevel::WARNING, "No profile for user_id: " + std::to_string(user_id));
            return false;
        }
        Logger::log(LogLevel::INFO, "Updated " + column_name + " for user_id: " + std::to_string(user_id));
        return true;
    } catch (const std::exception &e) {
        Logger::log(LogLevel::ERROR, std::string("update_financial_profile error: ") + e.what());
        return false;
    }
}

int DatabaseManager::get_value_from_financial_profile(const std::string &column_name, int user_id) {
    if (!conn || !conn->is_open()) {
        Logger::log(LogLevel::ERROR, "No open DB connection for get_value_from_financial_profile.");
        return 0;
    }
    try {
        FinancialProfile col = financial_profile_column(column_name);
        std::string field;
        switch (col) {
            case FinancialProfile::BALANCE:       field = "balance"; break;
            case FinancialProfile::DAILY_MINIMUM: field = "daily_minimum"; break;
            case FinancialProfile::SAVINGS:       field = "savings"; break;
            case FinancialProfile::DEBT:          field = "debt"; break;
            default:
                Logger::log(LogLevel::WARNING, "Unknown column: " + column_name);
                return 0;
        }
        pqxx::work txn(*conn);
        #pragma GCC diagnostic push
        #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
        auto r = txn.exec_params(
            "SELECT " + field + " FROM financial_profile WHERE user_id = $1;",
            user_id
        );
        #pragma GCC diagnostic pop
        txn.commit();
        if (r.empty()) {
            Logger::log(LogLevel::WARNING, "No profile for user_id: " + std::to_string(user_id));
            return 0;
        }
        return r[0][0].as<int>();
    } catch (const std::exception &e) {
        Logger::log(LogLevel::ERROR, std::string("get_value_from_financial_profile error: ") + e.what());
        return 0;
    }
}

FinancialProfile DatabaseManager::financial_profile_column(const std::string &column_name) {
    std::string col = column_name;
    std::transform(col.begin(), col.end(), col.begin(), ::tolower);
    if (col == "balance")        return FinancialProfile::BALANCE;
    if (col == "daily_minimum")  return FinancialProfile::DAILY_MINIMUM;
    if (col == "savings")        return FinancialProfile::SAVINGS;
    if (col == "debt")           return FinancialProfile::DEBT;
    return FinancialProfile::UNKNOWN_COLUMN;
}