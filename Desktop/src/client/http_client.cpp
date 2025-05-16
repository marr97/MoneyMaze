#include "http_client.h"


void handle_server_response(QNetworkReply* reply){
    if (reply->error() == QNetworkReply::NoError) {
        QString response = reply->readAll();
        qDebug() << "Ответ сервера: " << response;
    } else {
        qDebug() << "Ошибка: " << reply->errorString();
    }
    reply->deleteLater();
}


int registrate(QString &nickname, QString &password){

    QNetworkAccessManager *manager = new QNetworkAccessManager(this);
    QNetworkRequest request;
    request.setUrl(QUrl("http://89.169.154.118:9090"));


    QJsonObject json_data;
    json_data["nickname"] = nickname;
    json_data["password"] = password;

    QJsonDocument json_doc(json_data);
    QByteArray registration_data = json_doc.toJson();


    qDebug() << "------------ отправка данных ------------";


    QNetworkReply *reply = manager->post(request, registration_data);


    connect(reply, &QNetworkReply::finished, this, [=](){
        handle_server_response(reply);
    });

    connect(reply, &QNetworkReply::errorOccurred, this, [](QNetworkReply::NetworkError err) {
        qDebug() << "Ошибка сети: " << err;
    });

    int status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    return status_code;
}
