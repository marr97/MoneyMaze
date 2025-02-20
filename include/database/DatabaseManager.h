#pragma once
#include <pqxx/pqxx>
#include "db_config.h"

class DatabaseManager {
public:
    DatabaseManager();
    ~DatabaseManager();

    bool connect();
    bool disconnect();

    // Методы для работы с пользователями
    bool createUser(const std::string& username, const std::string& password);
    bool authenticateUser(const std::string& username, const std::string& password);

    // Методы для работы с финансовым профилем
    bool createFinancialProfile(int userId, double initialBalance, double dailyMinimum);
    bool updateBalance(int userId, double newBalance);
    double getBalance(int userId);

private:
    std::unique_ptr<pqxx::connection> conn;
};