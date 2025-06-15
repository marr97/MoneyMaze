#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QObject>
#include <QDialog>
#include <QJsonObject>
#include <QVector>

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
    void next_month(const QString &username);
    void get_loan_info(const QString &username);
    void take_loan(int amount, int period, int rate, const QString &username);
    void user_loans(const QString &username);
    void make_deposit(int amount, int period, int rate, const QString &username);
    void user_deposits(const QString &username);

signals:
    void registration_finished(int status_code, const QString &error_msg);
    void authorization_finished(int status_code, const QString &error_msg);
    void error_occurred(const QString &error);
    void financial_profile_received(int balance, int monthly_minimum, int total_loans,
                                    int interest_due, int salary, int current_month,
                                    const QString &status);
    void loan_info_received(int min_loan_amount, int max_loan_amount, int interest_rate);
    void loans_received(const QVector<QJsonObject> &loans_list);
    void loan_taken();

    void deposits_received(const QVector<QJsonObject> &deposits_list);
    void deposit_taken();

private:
    QNetworkAccessManager *manager;
};

#endif // HTTP_CLIENT_H
