#pragma once

#include <string>
#include <Poco/Net/MailMessage.h>
#include <Poco/Net/SMTPClientSession.h>

class EmailSender {
public:
    EmailSender(const std::string& host, int port,
                const std::string& user, const std::string& password);

    bool sendRecoveryEmail(const std::string& to, const std::string& passwordPlain);

private:
    std::string smtp_host;
    int smtp_port;
    std::string smtp_user;
    std::string smtp_password;
};