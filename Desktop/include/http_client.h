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

signals:
    void registration_finished(int status_code, const QString &error_msg);
    void authorization_finished(int status_code, const QString &error_msg);
    void error_occurred(const QString &error);

private:
    QNetworkAccessManager *manager;
};

#endif // HTTP_CLIENT_H
