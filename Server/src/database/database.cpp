#include "database.h"
#include <iostream>

DatabaseManager::DatabaseManager() {
    connect();
}

DatabaseManager::~DatabaseManager() {
    disconnect();
}

bool DatabaseManager::connect() {
    try {
        conn = std::make_unique<pqxx::connection>("dbname=mydb user=myuser password=mypassword host=127.0.0.1");
        if (conn->is_open()) {
            std::cout << "Connected to the database successfully!\n";
            return true;
        } else {
            std::cerr << "Failed to open the database connection!\n";
            return false;
        }
    } catch (const std::exception &e) {
        std::cerr << "Database connection error: " << e.what() << "\n";
        return false;
    }
}

void DatabaseManager::disconnect() {
    if (conn && conn->is_open()) {
        conn.reset();
        std::cout << "Database connection closed.\n";
    }
}


bool DatabaseManager::isConnected() const {
    return conn && conn->is_open();
}