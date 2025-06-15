#include "deposit_info.h"
#include "ui_deposit_info.h"
#include "http_client.h"
#include <QString>
#include <QStyle>
#include <QJsonObject>
#include <QVector>
#include <QLabel>
#include <QApplication>

deposit_info::deposit_info(QWidget *parent)
    : QWidget(parent), ui(new Ui::deposit_info), http_client_deposit_info(new httpClient(this)) {
    ui->setupUi(this);

    this->setWindowTitle("Информация о вкладах");

    connect(http_client_deposit_info, &httpClient::deposits_received, this, &deposit_info::set_deposit_data);

    // виджеты с суммой вклада

    QString WidgetStyle =  "QWidget {"
        "   background: rgba(174, 208, 180, 0.3);"
        "   border-radius: 10px;"
        "   border: 5px;"
        "   padding: 5px;"
        "}";

    ui->widget_deposit->setStyleSheet(WidgetStyle);

    QString qlStyle_1 = "QLabel {"
        "   background: transparent;"
        "   color: black;"
        "font-family: 'Gill Sans', sans-serif;"
        "font-size: 16px;"
        "}";

    ui->ql_deposit->setStyleSheet(qlStyle_1);
    ui->deposit_value->setStyleSheet(qlStyle_1);


    // период и процентная ставка

    QString qlStyle_2 = "QLabel {"
        "   background-color: rgba(225, 211, 255, 0.3);"
        "   color: black;"
        "   border-radius: 10px;"
        "   padding: 5px;"
        "}";

    ui->period->setStyleSheet(qlStyle_2);
    ui->period_value->setStyleSheet(qlStyle_2);

    ui->rate->setStyleSheet(qlStyle_2);
    ui->rate_value->setStyleSheet(qlStyle_2);


    // стрелочки снизу и номер кредита

    QString qlStyle_3 = "QLabel {"
        "   background: transparent;"
        "   color: grey;"
        "font-family: 'Gill Sans', sans-serif;"
        "font-size: 13px;"
        "}";

    ui->ql_deposit_id->setStyleSheet(qlStyle_3);

    QString arrowStyle = "QToolButton { border: none; "
        "padding: 5px; "
        "color: grey"
        "}";

    ui->tb_next->setArrowType(Qt::RightArrow);
    ui->tb_prev->setArrowType(Qt::LeftArrow);

    ui->tb_next->setStyleSheet(arrowStyle);
    ui->tb_prev->setStyleSheet(arrowStyle);
}

deposit_info::~deposit_info() {
    delete ui;
}


void deposit_info::get_deposit_data(const QString &username)
{
    http_client_deposit_info->user_deposits(username);
}


void deposit_info::set_deposit_data(const QVector<QJsonObject> &deposits)
{
    if (deposits.isEmpty()) {
        QLabel* label = new QLabel(this);
        label->setText("У вас нет вкладов");
        label->setFixedSize(400, 350);
        label->setAlignment(Qt::AlignCenter);


        label->setStyleSheet(
            "background-color: rgb(230, 230, 230);"
            "color: grey;"
            "border-radius: 5px;"
            "padding: 10px;"
            "font-family: 'Gill Sans', sans-serif;"
            "font-size: 16px;"
            );

        label->show();
        return;
    }

    m_deposits = deposits;
    deposit_id = 0;
    update_deposit_display();
}


void deposit_info::update_deposit_display() {
    if (deposit_id < 0 || deposit_id >= m_deposits.size())
        return;

    const QJsonObject& current = m_deposits[deposit_id];

    int deposit = current["current_amount"].toInt();
    int rate = current["rate"].toInt();
    int period = current["term_months"].toInt();

    ui->deposit_value->setText(QLocale().toString(deposit));
    ui->period_value->setText(QLocale().toString(period) + " мес");
    ui->rate_value->setText(QLocale().toString(rate) + " %");


    ui->ql_deposit_id->setText("Номер вклада: " + QString::number(deposit_id + 1));

}



void deposit_info::on_tb_prev_clicked()
{
    if (deposit_id > 0) {
        deposit_id--;
        update_deposit_display();
    }
}


void deposit_info::on_tb_next_clicked()
{
    if (deposit_id < m_deposits.size() - 1) {
        deposit_id++;
        update_deposit_display();
    }
}

