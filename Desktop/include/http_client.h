#ifndef HTTP_CLIENT_H
#define HTTP_CLIENT_H

#include <QNetworkAccessManager>
#include <QNetworkRequest>
#include <QNetworkReply>
#include <QDebug>
#include <QString>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>


void handle_server_response(QNetworkReply* reply);
int registrate(QString &nickname, QString &password);

#endif // HTTP_CLIENT_H
