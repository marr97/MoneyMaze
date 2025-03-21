#ifndef DATABASE_H
#define DATABASE_H

#include <pqxx/pqxx>
#include <string>

class DatabaseManager {
private:
    std::unique_ptr<pqxx::connection> conn;

public:
    DatabaseManager();
    ~DatabaseManager();

    bool connect();
    void disconnect();
    bool isConnected() const;
};

#endif // DATABASE_H