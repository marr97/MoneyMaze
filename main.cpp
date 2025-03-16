#include <QApplication>
#include <iostream>
#include "database/DatabaseManager.h"
#include "ui/profile_window.h"

int main(int argc, char *argv[]) {
    // Initialize Qt application first
    QApplication a(argc, argv);
    
    // Connect to database
    DatabaseManager dbManager;
    if (!dbManager.connect()) {
        std::cout << "Failed to connect to the database." << std::endl;
        return 1; // Exit with error code if database connection fails
    }
    
    std::cout << "Connected to the database successfully." << std::endl;
    
    // For testing purposes - in a real app, this would be handled by the login UI
    bool authenticated = false;
    QString username = "testuser";
    
    // Check if test user exists, create if not
    if (!dbManager.authenticateUser("testuser", "testpassword")) {
        std::cout << "Test user not found, creating..." << std::endl;
        if (dbManager.createUser("testuser", "testpassword")) {
            std::cout << "User created successfully." << std::endl;
            authenticated = true;
        } else {
            std::cout << "Failed to create user." << std::endl;
        }
    } else {
        std::cout << "User authenticated successfully." << std::endl;
        authenticated = true;
    }
    
    // Create and show profile window if authenticated
    if (authenticated) {
        profile_window w;
        w.setUsername(username);
        
        // Example financial data - in a real app, this would come from the database
        w.setDailyMinimum(1000.0);
        w.setFreeCash(5000.0);
        w.setLoanDebt(2000.0);
        
        w.show();
        
        // Run the application
        int result = a.exec();
        
        // Disconnect from database before exiting
        dbManager.disconnect();
        std::cout << "Disconnected from the database." << std::endl;
        
        return result;
    } else {
        // If not authenticated, show an error message and exit
        std::cout << "Authentication failed. Cannot show profile." << std::endl;
        dbManager.disconnect();
        return 1;
    }
}