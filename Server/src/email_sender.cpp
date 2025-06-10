#include "email_sender.h"

#include <Poco/Net/MailMessage.h>
#include <Poco/Net/MailRecipient.h>
#include <Poco/Net/SMTPClientSession.h>
#include <Poco/Net/SecureStreamSocket.h>
#include <Poco/Net/Context.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/NetException.h>
#include <Poco/Net/SecureSMTPClientSession.h>
#include <Poco/Net/AcceptCertificateHandler.h>
#include <Poco/Net/InvalidCertificateHandler.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/Net/ConsoleCertificateHandler.h>
#include <Poco/Net/HTTPSClientSession.h>
#include <Poco/Exception.h>
#include <iostream>

EmailSender::EmailSender(const std::string& host, int port,
                         const std::string& user, const std::string& password)
    : smtp_host(host), smtp_port(port),
      smtp_user(user), smtp_password(password)
{}

bool EmailSender::sendRecoveryEmail(const std::string& to, const std::string& passwordPlain) {
    try {
        Poco::Net::MailMessage message;
        message.setSender(smtp_user);
        message.addRecipient(Poco::Net::MailRecipient(
            Poco::Net::MailRecipient::PRIMARY_RECIPIENT, to));

        std::string encodedSubject = Poco::Net::MailMessage::encodeWord("Восстановление пароля", "UTF-8");
        message.setSubject("=?UTF-8?B?" + encodedSubject + "?=");

        std::string body =
            "Здравствуйте,\n\n"
            "Ваш новый пароль: " + passwordPlain + "\n\n"
            "С уважением,\nКоманда поддержки";
        message.setContentType("text/plain; charset=UTF-8");
        message.setContent(body, Poco::Net::MailMessage::ENCODING_8BIT);

        Poco::Net::Context::Ptr sslContext = new Poco::Net::Context(
            Poco::Net::Context::CLIENT_USE,
            "", "", "",
            Poco::Net::Context::VERIFY_RELAXED,
            9,    
            false,
            "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH"
        );

        {
            static bool sslInitialized = false;
            if (!sslInitialized) {
                Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> certHandler =
                    new Poco::Net::AcceptCertificateHandler(false);
                Poco::Net::SSLManager::instance().initializeClient(nullptr, certHandler, sslContext);
                sslInitialized = true;
            }
        }

        if (smtp_port == 465) {
            Poco::Net::SocketAddress sa(smtp_host, smtp_port);
            Poco::Net::SecureStreamSocket secureSocket(sa, sslContext);
            Poco::Net::SecureSMTPClientSession session(secureSocket);
            session.login(Poco::Net::SMTPClientSession::AUTH_LOGIN, smtp_user, smtp_password);
            session.sendMessage(message);
            session.close();
        } else {
            Poco::Net::SMTPClientSession session(smtp_host, smtp_port);
            session.open();
#if POCO_VERSION_MAJOR >= 1 && POCO_VERSION_MINOR >= 9
            try {
                session.startTLS(sslContext);
            } catch (Poco::Exception& exc) {
                std::cerr << "Warning: STARTTLS failed or not supported: " << exc.displayText() << std::endl;

            }
#else
            std::cerr << "Warning: Метод startTLS(Context::Ptr) отсутствует в текущей версии Poco. "
                         "Используется нешифрованное соединение.\n";
            
#endif
            session.login(Poco::Net::SMTPClientSession::AUTH_LOGIN, smtp_user, smtp_password);
            session.sendMessage(message);
            session.close();
        }


        return true;
    }
    catch (const Poco::Net::SMTPException& e) {
        std::cerr << "SMTP Error: " << e.displayText() << std::endl;
        return false;
    }
    catch (const Poco::Net::NetException& e) {
        std::cerr << "Network Error: " << e.displayText() << std::endl;
        return false;
    }
    catch (const Poco::Exception& e) {
        std::cerr << "Poco Exception: " << e.displayText() << std::endl;
        return false;
    }
    catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        return false;
    }
}
