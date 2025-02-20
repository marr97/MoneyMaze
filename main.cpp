#include <iostream>
#include "include/database/DatabaseManager.h"

int main() {
    DatabaseManager dbManager;

    if (dbManager.connect()) {
        std::cout << "Connected to the database successfully." << std::endl;

        // Тест создания пользователя
        if (dbManager.createUser("testuser", "testpassword")) {
            std::cout << "User created successfully." << std::endl;
        } else {
            std::cout << "Failed to create user." << std::endl;
        }

        // Тест аутентификации пользователя
        if (dbManager.authenticateUser("testuser", "testpassword")) {
            std::cout << "User authenticated successfully." << std::endl;
        } else {
            std::cout << "Authentication failed." << std::endl;
        }

        dbManager.disconnect();
        std::cout << "Disconnected from the database." << std::endl;
    } else {
        std::cout << "Failed to connect to the database." << std::endl;
    }

    return 0;
}