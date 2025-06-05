#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QDialog>

class httpClient: public QObject {
    Q_OBJECT

public:
    explicit httpClient(QObject *parent = nullptr);
    ~httpClient();

    enum Status {
        OK,
        ERROR,
        NETWORK_ERROR
    };
    Q_ENUM(Status)

    void registrate(const QString &nickname, const QString &password);
    void authorize(const QString &login, const QString &password);
    void show_result(const QString &message, Status status, QDialog *object);
    void get_financial_profile(const QString &username);

signals:
    void registration_finished(int status_code, const QString &error_msg);
    void authorization_finished(int status_code, const QString &error_msg);
    void error_occurred(const QString &error);
    void financial_profile_received(int balance, int monthly_minimum, int total_loans,
                                    int interest_due, int salary, int current_month,
                                    const QString &status);

private:
    QNetworkAccessManager *manager;
};

#endif // HTTP_CLIENT_H
