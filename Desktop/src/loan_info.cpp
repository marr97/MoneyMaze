#include "loan_info.h"
#include "ui_loan_info.h"
#include "http_client.h"
#include <QString>
#include <QStyle>
#include <QLabel>
#include <QApplication>

loan_info::loan_info(QWidget *parent) : QWidget(parent), ui(new Ui::loan_info), http_client_loan_info(new httpClient(this)) {
    ui->setupUi(this);
    this->setWindowTitle("Информация о кредитах");

    connect(http_client_loan_info, &httpClient::loans_received, this, &loan_info::set_loan_data);

    // виджеты с суммой кредита и следующим платежом

    QString WidgetStyle =  "QWidget {"
        "   background: rgba(174, 208, 180, 0.3);"
        "   border-radius: 10px;"
        "   border: 5px;"
        "   padding: 5px;"
        "}";

    ui->widget_amount->setStyleSheet(WidgetStyle);
    ui->widget_payment->setStyleSheet(WidgetStyle);

    QString qlStyle_1 = "QLabel {"
        "   background: transparent;"
        "   color: black;"
        "font-family: 'Gill Sans', sans-serif;"
        "font-size: 16px;"
        "}";

    ui->ql_amount->setStyleSheet(qlStyle_1);
    ui->ql_next_payment->setStyleSheet(qlStyle_1);

    ui->amount_value->setStyleSheet(qlStyle_1);
    ui->next_payment_value->setStyleSheet(qlStyle_1);


    // период и количество выплаченных месяцев, процентная ставка

    QString qlStyle_2 = "QLabel {"
        "   background-color: rgba(225, 211, 255, 0.3);"
        "   color: black;"
        "   border-radius: 10px;"
        "   padding: 5px;"
        "}";

    ui->period->setStyleSheet(qlStyle_2);
    ui->period_value->setStyleSheet(qlStyle_2);

    ui->payed_months->setStyleSheet(qlStyle_2);
    ui->payed_months_value->setStyleSheet(qlStyle_2);

    ui->rate->setStyleSheet(qlStyle_2);
    ui->rate_value->setStyleSheet(qlStyle_2);


    // стрелочки снизу и номер кредита

    QString qlStyle_3 = "QLabel {"
        "   background: transparent;"
        "   color: grey;"
        "font-family: 'Gill Sans', sans-serif;"
        "font-size: 13px;"
        "}";

    ui->ql_loan_id->setStyleSheet(qlStyle_3);

    QString arrowStyle = "QToolButton { border: none; "
        "padding: 5px; "
        "color: grey"
        "}";

    ui->tb_next->setArrowType(Qt::RightArrow);
    ui->tb_prev->setArrowType(Qt::LeftArrow);

    ui->tb_next->setStyleSheet(arrowStyle);
    ui->tb_prev->setStyleSheet(arrowStyle);
}

loan_info::~loan_info() {
    delete ui;
}

void loan_info::get_loan_data(const QString &username)
{
    http_client_loan_info->user_loans(username);
}


void loan_info::set_loan_data(const QVector<QJsonObject> &loans)
{
    if (loans.isEmpty()) {
        QLabel* label = new QLabel(this);
        label->setText("У вас нет кредитов");
        label->setFixedSize(430, 360);
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

    m_loans = loans;
    loan_id = 0;
    update_loan_display();
}


void loan_info::update_loan_display() {
    if (loan_id < 0 || loan_id >= m_loans.size())
        return;

    const QJsonObject& current = m_loans[loan_id];

    int amount = current["amount"].toInt();
    int rate = current["rate"].toInt();
    int period = current["period"].toInt();
    int passed_months = current["passed_months"].toInt();

    ui->amount_value->setText(QLocale().toString(amount));
    ui->period_value->setText(QLocale().toString(period) + " мес");
    ui->rate_value->setText(QLocale().toString(rate) + " %");
    ui->payed_months_value->setText(QLocale().toString(passed_months) + " мес");

    int next_payment = count_next_payment(amount, rate, period - passed_months);
    ui->next_payment_value->setText(QLocale().toString(next_payment));

    ui->ql_loan_id->setText("Номер кредита: " + QString::number(loan_id + 1));

}

void loan_info::on_tb_prev_clicked()
{
    if (loan_id > 0) {
        loan_id--;
        update_loan_display();
    }

}


void loan_info::on_tb_next_clicked()
{
    if (loan_id < m_loans.size() - 1) {
        loan_id++;
        update_loan_display();
    }
}


int loan_info::count_next_payment(int amount, int rate, int period)
{
    if (period <= 0 || amount <= 0) {
        return 0;
    }

    double principal_part = static_cast<double>(amount) / period;
    double interest_part = amount * (rate / 100.0 / 12.0);
    int next_payment = static_cast<int>(principal_part + interest_part + 0.5);

    return next_payment;
}
