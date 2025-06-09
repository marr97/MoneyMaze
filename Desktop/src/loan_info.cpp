#include "loan_info.h"
#include "ui_loan_info.h"
#include "http_client.h"
#include <QString>

loan_info::loan_info(QWidget *parent) : QWidget(parent), ui(new Ui::loan_info), http_client_loan_info(new httpClient(this)) {
    ui->setupUi(this);
    this->setWindowTitle("Информация о кредитах");

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
}

loan_info::~loan_info() {
    delete ui;
}


void loan_info::set_loan_data(int amount, int period, int rate, int passed_months)
{
    ui->amount_value->setText(QLocale().toString(amount));
    ui->period_value->setText(QLocale().toString(period));
    ui->rate_value->setText(QLocale().toString(rate) + "%");
    ui->payed_months_value->setText(QLocale().toString(passed_months) + " мес");
}
