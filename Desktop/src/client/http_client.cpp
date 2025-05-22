#include "http_client.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QLabel>
#include <QDialog>
#include <QTimer>

httpClient::httpClient(QObject *parent): QObject(parent) {
    manager = new QNetworkAccessManager(this);
}

httpClient::~httpClient(){
    delete manager;
}

void httpClient::show_result(const QString &message, Status status, QDialog *object)
{
    const int timeout_ms = 2500;

    QLabel* label = new QLabel(object);
    label->setFixedHeight(40);
    label->setText(message);
    label->setAlignment(Qt::AlignCenter);

    if (status == Status::ERROR){
        label->setStyleSheet(
            "background-color: rgb(216, 58, 47);"
            "color: rgb(255, 255, 255);"
            "border-radius: 5px;"
            "padding: 10px;"
            "font-family: 'Gill Sans', sans-serif;"
            "font-size: 14px;"
            );
    } else if (status == Status::OK){
        label->setStyleSheet(
            "background-color: rgb(97, 197, 84);"
            "color: rgb(255, 255, 255);"
            "border-radius: 5px;"
            "padding: 10px;"
            "font-family: 'Gill Sans', sans-serif;"
            "font-size: 14px;"
            );
    } else if (status == Status::NETWORK_ERROR){
        label->setStyleSheet(
            "background-color: rgb(155, 155, 155);"
            "color: rgb(255, 255, 255);"
            "border-radius: 5px;"
            "padding: 10px;"
            "font-family: 'Gill Sans', sans-serif;"
            "font-size: 14px;"
            );
    } else {
        return;
    }

    int x = (object->width() - label->sizeHint().width()) / 2;
    int y = (object->height() - label->sizeHint().height()) / 10;

    label->move(x, y);
    label->show();

    QTimer::singleShot(timeout_ms, label, &QLabel::deleteLater);
}



void httpClient::handle_server_response(QNetworkReply* reply)
{
    int status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    qDebug() << "reply status code=" << status_code << "\n";

    if (status_code == 200 || status_code >= 400) {
        QString response = reply->readAll();
        qDebug() << "Ответ сервера: " << response;

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


    qDebug() << "[ Отправка данных регистрации ]";


    QNetworkReply *reply = manager->post(request, registration_data);


    connect(reply, &QNetworkReply::finished, this, [=](){
        handle_server_response(reply);
    });
}

