#include "include/database/DatabaseManager.h"
#include <iostream>

DatabaseManager::DatabaseManager() : conn(nullptr) {}

DatabaseManager::~DatabaseManager() {
    disconnect();
}

bool DatabaseManager::connect() {
    try {
        conn = std::make_unique<pqxx::connection>(
            "dbname=" + std::string(DB_NAME) +
            " user=" + std::string(DB_USER) +
            " password=" + std::string(DB_PASSWORD) +
            " hostaddr=" + std::string(DB_HOST) +
            " port=" + std::string(DB_PORT)
        );
        return conn->is_open();
    } catch (const std::exception &e) {
        std::cerr << "Connection error: " << e.what() << std::endl;
        return false;
    }
}


bool DatabaseManager::disconnect() {
    if (conn) {
        conn.reset(); 
        return true;
    }
    return false;
}

bool DatabaseManager::createUser(const std::string& username, const std::string& password) {
    if (!conn || !conn->is_open()) {
        std::cerr << "Database connection is not open." << std::endl;
        return false;
    }

    try {
        pqxx::work txn(*conn);
        txn.exec_params("INSERT INTO users (username, password) VALUES ($1, $2)",
                        username, password);
        txn.commit();
        return true;
    } catch (const std::exception &e) {
        std::cerr << "Create user error: " << e.what() << std::endl;
        return false;
    }
}

bool DatabaseManager::authenticateUser(const std::string& username, const std::string& password) {
    if (!conn || !conn->is_open()) {
        std::cerr << "Database connection is not open." << std::endl;
        return false;
    }

    try {
        pqxx::work txn(*conn);
        pqxx::result r = txn.exec_params("SELECT id FROM users WHERE username = $1 AND password = $2",
                                         username, password);
        return !r.empty();
    } catch (const std::exception &e) {
        std::cerr << "Authentication error: " << e.what() << std::endl;
        return false;
    }
}

