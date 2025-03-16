#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <QString>

// Placeholder for HTTP client functionality
// This will be implemented later

// If we need JSON functionality
class json {
public:
    // Add minimal functionality needed for now
    static json parse(const QString& jsonStr) { return json(); }
    // Add other methods as needed
};

json create_auth_json(const class auth_window& window);
void send_auth_data(const json& data);

#endif // HTTP_CLIENT_H