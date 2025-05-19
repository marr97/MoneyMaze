#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <QNetworkAccessManager>
#include <QNetworkReply>
#include <QDialog>
#include <QObject>

class httpClient: public QObject {
    Q_OBJECT

public:
    explicit httpClient(QObject *parent = nullptr);
    ~httpClient();
    void registrate(const QString &nickname, const QString &password);

private slots:
    void handle_server_response(QNetworkReply* reply);

signals:
    void registration_finished(int status_code, const QString &error_msg);
    void error_occurred(const QString &error);  // для ошибок сети

private:
    QNetworkAccessManager *manager;
};

#endif // HTTP_CLIENT_H
