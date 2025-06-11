#include "http_client.h"
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QByteArray>
#include <QLabel>
#include <QDialog>
#include <QJsonArray>
#include <QVector>
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

    QNetworkReply *reply = manager->post(request, registration_data);


    connect(reply, &QNetworkReply::finished, this, [=](){
        int status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

        if (status_code == 200 || status_code >= 400) {
            QString response = reply->readAll();
            emit registration_finished(status_code, response);

        }
        else {
            emit error_occurred(reply->errorString());
        }

        reply->deleteLater();
    });
}


void httpClient::authorize(const QString &login, const QString &password)
{
    QNetworkRequest request;

    QUrl url("http://89.169.154.118:9090");
    url.setPath("/login");
    request.setUrl(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json_data;
    json_data["login"] = login;
    json_data["password"] = password;

    QJsonDocument json_doc(json_data);
    QByteArray auth_data = json_doc.toJson();

    QNetworkReply *reply = manager->post(request, auth_data);


    connect(reply, &QNetworkReply::finished, this, [=](){
        int status_code = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();

        if (status_code == 200 || status_code >= 400) {
            QString response = reply->readAll();
            emit authorization_finished(status_code, response);

        }
        else {
            emit error_occurred(reply->errorString());
        }

        reply->deleteLater();
    });
}


void httpClient::get_financial_profile(const QString &username)
{
    QNetworkRequest request;

    QUrl url("http://89.169.154.118:9090");
    url.setPath("/financial-profile");
    request.setUrl(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json_data;
    json_data["username"] = username;

    QJsonDocument json_doc(json_data);
    QByteArray data = json_doc.toJson();

    QNetworkReply* reply = manager->post(request, data);


    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response_data = reply->readAll();
            QJsonDocument json_response = QJsonDocument::fromJson(response_data);
            QJsonObject response_obj = json_response.object();

            int balance = response_obj["balance"].toInt();
            int monthly_minimum = response_obj["monthly_minimum"].toInt();
            int total_loans = response_obj["total_loans"].toInt();
            int interest_due = response_obj["interest_due"].toInt();
            int salary = response_obj["salary"].toInt();
            int current_month = response_obj["current_month"].toInt();
            QString status = response_obj["status"].toString();

            emit financial_profile_received(balance, monthly_minimum, total_loans,
                                          interest_due, salary, current_month, status);
        } else {
            qDebug() << "Error:" << reply->errorString();
            emit error_occurred(reply->errorString());
        }

        reply->deleteLater();
    });
}


void httpClient::next_month(const QString &username)
{
    QNetworkRequest request;

    QUrl url("http://89.169.154.118:9090");
    url.setPath("/next-month");
    request.setUrl(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json_data;
    json_data["username"] = username;

    QJsonDocument json_doc(json_data);
    QByteArray data = json_doc.toJson();

    QNetworkReply* reply = manager->post(request, data);


    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            get_financial_profile(username);
        } else {
            qDebug() << "Error:" << reply->errorString();
        }

        reply->deleteLater();
    });
}


void httpClient::get_loan_info(const QString &username)
{
    QNetworkRequest request;

    QUrl url("http://89.169.154.118:9090");
    url.setPath("/loan-info");
    request.setUrl(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json_data;
    json_data["username"] = username;

    QJsonDocument json_doc(json_data);
    QByteArray data = json_doc.toJson();

    QNetworkReply* reply = manager->post(request, data);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response_data = reply->readAll();
            QJsonDocument json_response = QJsonDocument::fromJson(response_data);
            QJsonObject response_obj = json_response.object();


            int min_loan_amount = response_obj["min_loan_amount"].toInt();
            int max_loan_amount = response_obj["max_loan_amount"].toInt();
            int interest_rate = response_obj["interest_rate"].toInt();

            emit loan_info_received(min_loan_amount, max_loan_amount, interest_rate);

        } else {
            QString error = reply->errorString();
            qDebug() << "Error:" << error;
        }

        reply->deleteLater();
    });
}


void httpClient::take_loan(int amount, int period, int rate, const QString &username)
{
    QNetworkRequest request;

    QUrl url("http://89.169.154.118:9090");
    url.setPath("/take-loan");
    request.setUrl(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json_data;
    json_data["username"] = username;
    json_data["amount"] = amount;
    json_data["period"] = period;
    json_data["rate"] = rate;

    QJsonDocument json_doc(json_data);
    QByteArray loan_data = json_doc.toJson();

    QNetworkReply* reply = manager->post(request, loan_data);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            emit loan_taken();
        } else {
            qDebug() << "Error:" << reply->errorString();
            emit error_occurred(reply->errorString());
        }

        reply->deleteLater();
    });

}


void httpClient::user_loans(const QString &username)
{
    QNetworkRequest request;

    QUrl url("http://89.169.154.118:9090");
    url.setPath("/user-loans");
    request.setUrl(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json_data;
    json_data["username"] = username;

    QJsonDocument json_doc(json_data);
    QByteArray data = json_doc.toJson();

    QNetworkReply* reply = manager->post(request, data);

    connect(reply, &QNetworkReply::finished, this, [=]() {
        if (reply->error() == QNetworkReply::NoError) {
            QByteArray response_data = reply->readAll();
            QJsonDocument json_response = QJsonDocument::fromJson(response_data);
            QJsonObject response_obj = json_response.object();

            QJsonArray loans = response_obj["loans"].toArray();
            QVector<QJsonObject> loans_list;

            for (const auto& loan: loans) {
                loans_list.append(loan.toObject());
            }

            emit loans_received(loans_list);

        } else {
            qDebug() << "Error:" << reply->errorString();
        }

        reply->deleteLater();
    });
}


void httpClient::make_deposit(int amount, int period, int rate, const QString &username)
{
    QNetworkRequest request;

    QUrl url("http://89.169.154.118:9090");
    url.setPath("/deposit");
    request.setUrl(url);

    request.setHeader(QNetworkRequest::ContentTypeHeader, "application/json");

    QJsonObject json_data;
    json_data["username"] = username;
    json_data["amount"] = amount;
    json_data["period"] = period;
    json_data["rate"] = rate;
}


