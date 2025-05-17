#include "http_client.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>

httpClient::httpClient(QObject *parent): QObject(parent) {
    manager = new QNetworkAccessManager(this);
}

httpClient::~httpClient(){
    delete manager;
}

void httpClient::handle_server_response(QNetworkReply* reply)
{
    if (reply->error() == QNetworkReply::NoError) {
        QString response = reply->readAll();
        qDebug() << "Ответ сервера: " << response;

        int status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
        emit registration_finished(status_code, response);
    }
    else {
        qDebug() << "Ошибка сети: " << reply->errorString();
        emit error_occurred(reply->errorString());
    }

    reply->deleteLater();
}


void httpClient::registrate(const QString &nickname, const QString &password)
{
    QNetworkRequest request;

    QUrl url("http://89.169.154.118:9090");
    url.setPath("/register");
    request.setUrl(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json_data;
    json_data["login"] = nickname;
    json_data["password"] = password;

    QJsonDocument json_doc(json_data);
    QByteArray registration_data = json_doc.toJson();


    qDebug() << "------------ отправка данных ------------";


    QNetworkReply *reply = manager->post(request, registration_data);


    connect(reply, &QNetworkReply::finished, this, [=](){
        handle_server_response(reply);
    });
}
