#include "database/DatabaseManager.h"
#include <ctime>
#include <fstream>
#include <iostream>

// Класс для логирования
class Logger {
public:
    static void log(LogLevel level, const std::string &message) {
        std::string levelStr;
        switch (level) {
            case LogLevel::DEBUG:
                levelStr = "DEBUG";
                break;
            case LogLevel::INFO:
                levelStr = "INFO";
                break;
            case LogLevel::WARNING:
                levelStr = "WARNING";
                break;
            case LogLevel::ERROR:
                levelStr = "ERROR";
                break;
        }

        std::time_t now = std::time(nullptr);
        char timestamp[100];
        std::strftime(
            timestamp, sizeof(timestamp), "%Y-%m-%d %H:%M:%S",
            std::localtime(&now)
        );

        std::string logMessage =
            std::string(timestamp) + " [" + levelStr + "] " + message + "\n";

        std::cout << logMessage;  // Вывод в консоль

        std::ofstream logFile("application.log", std::ios_base::app);
        if (logFile.is_open()) {
            logFile << logMessage;
            logFile.close();
        }
    }
};

DatabaseManager::DatabaseManager() : conn(nullptr) {
}

DatabaseManager::~DatabaseManager() {
    disconnect();
}

bool DatabaseManager::connect() {
    try {
        // Формируем строку подключения
        std::string connectionString =
            "dbname=" + DB_NAME + " user=" + DB_USER +
            " password=" + DB_PASSWORD + " hostaddr=" + DB_HOST +
            " port=" + DB_PORT;

        conn = std::make_unique<pqxx::connection>(connectionString);

        if (conn->is_open()) {
            Logger::log(
                LogLevel::INFO, "Successfully connected to the database."
            );

            // Проверяем, существует ли таблица users
            pqxx::work txn(*conn);
            pqxx::result r = txn.exec("SELECT to_regclass('public.users');");

            // Если таблица не существует, создаем её
            if (r[0][0].is_null()) {
                Logger::log(
                    LogLevel::INFO, "Table 'users' not found, creating it..."
                );
                txn.exec(R"(
                    CREATE TABLE IF NOT EXISTS users (
                        id SERIAL PRIMARY KEY,
                        username VARCHAR(255) UNIQUE NOT NULL,
                        password VARCHAR(255) NOT NULL
                    );
                )");
                txn.commit();
                Logger::log(
                    LogLevel::INFO, "Table 'users' created successfully."
                );
            } else {
                Logger::log(LogLevel::INFO, "Table 'users' already exists.");
            }

            return true;
        } else {
            Logger::log(LogLevel::ERROR, "Failed to open database connection.");
            return false;
        }
    } catch (const pqxx::sql_error &e) {
        Logger::log(
            LogLevel::ERROR, "SQL error during connection: " +
                                 std::string(e.what()) + ". Query: " + e.query()
        );
    } catch (const std::exception &e) {
        Logger::log(
            LogLevel::ERROR, "Connection error: " + std::string(e.what())
        );
    } catch (...) {
        Logger::log(
            LogLevel::ERROR,
            "Unknown error occurred during database connection."
        );
    }
    return false;
}

bool DatabaseManager::disconnect() {
    if (conn) {
        conn.reset();
        return true;
    }
    return false;
}

bool DatabaseManager::createUser(
    const std::string &username,
    const std::string &password
) {
    if (!conn || !conn->is_open()) {
        Logger::log(
            LogLevel::ERROR,
            "Attempted to create user without an open database connection."
        );
        return false;
    }

    try {
        pqxx::work txn(*conn);
        pqxx::result r = txn.exec_params(
            "INSERT INTO users (username, password) VALUES ($1, $2) ON "
            "CONFLICT (username) DO NOTHING RETURNING id",
            username, password
        );
        txn.commit();

        if (r.empty()) {
            Logger::log(
                LogLevel::WARNING, "User creation failed: username '" +
                                       username + "' already exists."
            );
            return false;
        }

        Logger::log(
            LogLevel::INFO, "User '" + username + "' created successfully."
        );
        return true;
    } catch (const pqxx::sql_error &e) {
        Logger::log(
            LogLevel::ERROR,
            "SQL error during user creation: " + std::string(e.what())
        );
        return false;
    } catch (const std::exception &e) {
        Logger::log(
            LogLevel::ERROR,
            "Unexpected error during user creation: " + std::string(e.what())
        );
        return false;
    }
}

bool DatabaseManager::authenticateUser(
    const std::string &username,
    const std::string &password
) {
    if (!conn || !conn->is_open()) {
        std::cerr << "Database connection is not open." << std::endl;
        return false;
    }

    try {
        pqxx::work txn(*conn);
        pqxx::result r = txn.exec_params(
            "SELECT id FROM users WHERE username = $1 AND password = $2",
            username, password
        );
        return !r.empty();
    } catch (const std::exception &e) {
        std::cerr << "Authentication error: " << e.what() << std::endl;
        return false;
    }
}
