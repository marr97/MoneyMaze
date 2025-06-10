#include "email_sender.h"

#include <Poco/Net/MailMessage.h>
#include <Poco/Net/MailRecipient.h>
#include <Poco/Net/SMTPClientSession.h>
#include <Poco/Net/SecureStreamSocket.h>
#include <Poco/Net/Context.h>
#include <Poco/Net/SocketAddress.h>
#include <Poco/Net/NetException.h>
#include <Poco/Net/SecureSMTPClientSession.h> // для SecureSMTPClientSession
#include <Poco/Net/AcceptCertificateHandler.h>
#include <Poco/Net/InvalidCertificateHandler.h>
#include <Poco/Net/SSLManager.h>
#include <Poco/Net/ConsoleCertificateHandler.h> // при необходимости альтернативный обработчик
#include <Poco/Net/HTTPSClientSession.h> // пример, не обязательно нужен
#include <Poco/Exception.h>
#include <iostream>

// Если SSL не инициализировано глобально, можно сделать инициализацию здесь.
// Но лучше вызывать один раз в main() приложения:
// Poco::Net::initializeSSL();
// А при завершении: Poco::Net::uninitializeSSL();

EmailSender::EmailSender(const std::string& host, int port,
                         const std::string& user, const std::string& password)
    : smtp_host(host), smtp_port(port),
      smtp_user(user), smtp_password(password)
{
    // Предполагаем, что SSLManager инициализируется вне конструктора,
    // либо можно здесь:
    // Poco::Net::initializeSSL();
    // Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> certHandler =
    //     new Poco::Net::AcceptCertificateHandler(false);
    // Poco::Net::Context::Ptr defaultContext = new Poco::Net::Context(
    //     Poco::Net::Context::CLIENT_USE, "", "", "",
    //     Poco::Net::Context::VERIFY_RELAXED, 9, false,
    //     "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH");
    // Poco::Net::SSLManager::instance().initializeClient(nullptr, certHandler, defaultContext);
}

bool EmailSender::sendRecoveryEmail(const std::string& to, const std::string& passwordPlain) {
    try {
        // 1. Формируем сообщение
        Poco::Net::MailMessage message;
        message.setSender(smtp_user);
        message.addRecipient(Poco::Net::MailRecipient(
            Poco::Net::MailRecipient::PRIMARY_RECIPIENT, to));

        // Кодировка темы
        std::string encodedSubject = Poco::Net::MailMessage::encodeWord("Восстановление пароля", "UTF-8");
        message.setSubject("=?UTF-8?B?" + encodedSubject + "?=");

        // Тело письма
        std::string body =
            "Здравствуйте,\n\n"
            "Ваш новый пароль: " + passwordPlain + "\n\n"
            "С уважением,\nКоманда поддержки";
        message.setContentType("text/plain; charset=UTF-8");
        message.setContent(body, Poco::Net::MailMessage::ENCODING_8BIT);

        // 2. Создаём свой SSL-контекст (если нужен специфичный)
        Poco::Net::Context::Ptr sslContext = new Poco::Net::Context(
            Poco::Net::Context::CLIENT_USE,
            "", "", "",
            Poco::Net::Context::VERIFY_RELAXED,
            9,    // минимум TLSv1.2
            false,
            "ALL:!ADH:!LOW:!EXP:!MD5:@STRENGTH"
        );

        // Инициализируем SSLManager, если ещё не инициализировано:
        // Замечание: делать только один раз за приложение.
        {
            static bool sslInitialized = false;
            if (!sslInitialized) {
                Poco::SharedPtr<Poco::Net::InvalidCertificateHandler> certHandler =
                    new Poco::Net::AcceptCertificateHandler(false);
                Poco::Net::SSLManager::instance().initializeClient(nullptr, certHandler, sslContext);
                sslInitialized = true;
            }
        }

        // 3. Выбор по порту: SMTPS или STARTTLS
        if (smtp_port == 465) {
            // SMTPS: SSL при установлении соединения
            Poco::Net::SocketAddress sa(smtp_host, smtp_port);
            Poco::Net::SecureStreamSocket secureSocket(sa, sslContext);
            Poco::Net::SecureSMTPClientSession session(secureSocket);
            session.login(Poco::Net::SMTPClientSession::AUTH_LOGIN, smtp_user, smtp_password);
            session.sendMessage(message);
            session.close();
        } else {
            // STARTTLS (порт 587). Проверяем наличие метода startTLS.
            Poco::Net::SMTPClientSession session(smtp_host, smtp_port);
            session.open();
#if POCO_VERSION_MAJOR >= 1 && POCO_VERSION_MINOR >= 9
            // В версиях Poco >= 1.9.0 метод startTLS(Context::Ptr) обычно присутствует.
            try {
                session.startTLS(sslContext);
            } catch (Poco::Exception& exc) {
                std::cerr << "Warning: STARTTLS failed or not supported: " << exc.displayText() << std::endl;
                // Можно продолжить по нешифрованному соединению или бросить исключение:
                // throw;
            }
#else
            // Если метода нет, вывести предупреждение.
            std::cerr << "Warning: Метод startTLS(Context::Ptr) отсутствует в текущей версии Poco. "
                         "Используется нешифрованное соединение.\n";
            // Либо требовать SMTPS: бросить исключение:
            // throw Poco::Exception("STARTTLS not supported in this Poco version");
#endif
            session.login(Poco::Net::SMTPClientSession::AUTH_LOGIN, smtp_user, smtp_password);
            session.sendMessage(message);
            session.close();
        }

        // Логгирование (раскомментировать при наличии Logger):
        // Logger::log(LogLevel::INFO, "Email sent to: " + to);

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
