#include "loan.h"
#include "ui_loan.h"
#include "http_client.h"
#include <QIntValidator>
#include <QTimer>

loan::loan(QWidget *parent) : QWidget(parent), ui(new Ui::loan), http_client_loan(new httpClient(this)) {
    ui->setupUi(this);
    this->setWindowTitle("Оформление кредита");

    connect(http_client_loan, &httpClient::loan_taken, this, &loan::loan_taken_message);
    connect(http_client_loan, &httpClient::error_occurred, this, &loan::error_message);

    // кнопка взять кредит
    ButtonStyle = "QPushButton {"
        "   background-color: rgba(73, 179, 78, 0.7);"
        "   border-top: none;"
        "   text-align: center;"
        "   color: white;"
        "   border-radius: 8px;"
        "   padding: 5px;"
        "}"
        "QPushButton:hover {"
        "   background-color: rgba(73, 179, 78, 0.9)"
        "}";

    ui->pb_take->setStyleSheet(ButtonStyle);


    // ввод суммы кредита
    LineEditStyle = "QLineEdit {"
        "   border-radius: 10px;"
        "   padding: 5px;"
        "   font-size: 18px;"
        "   background-color: rgba(174, 208, 180, 0.2);"
        "}"
        "QLineEdit:hover {"
        "   border: 2px solid rgba(174, 208, 180, 0.3);"
        "}"
        "QLineEdit:focus {"
        "   border: 2px solid rgba(174, 208, 180, 0.3);"
        "}"
        "QLineEdit::placeholder {"
        "   font-size: 14px;"
        "   color: rgb(140, 140, 140);"
        "}";

    ui->loan_amount->setStyleSheet(LineEditStyle);

    // выбор количества месяцев
    RadioButtonStyle =
        "QRadioButton {"
        "    padding: 8px;"
        "    background: rgba(174, 208, 180, 0.2);"
        "    border-radius: 6px;"
        "    spacing: 8px;"
        "}"
        "QRadioButton::indicator {"
        "    width: 12px;"
        "    height: 12px;"
        "    border: 2px solid rgba(73, 179, 78, 0.3);"
        "    border-radius: 7px;"
        "    background: #b5e8b7;"
        "}"
        "QRadioButton::indicator:checked {"
        "    background: qradialgradient("
        "        cx:0.5, cy:0.5, radius:0.5,"
        "        fx:0.5, fy:0.5,"
        "        stop:0 rgba(73, 179, 78, 0.6),"
        "        stop:0.5 rgba(73, 179, 78, 0.6),"
        "        stop:0.6 white,"
        "        stop:1 white"
        "    );"
        "    border-color: rgba(73, 179, 78, 0.7);"
        "}";

    ui->rb_6months->setStyleSheet(RadioButtonStyle);
    ui->rb_9months->setStyleSheet(RadioButtonStyle);
    ui->rb_12months->setStyleSheet(RadioButtonStyle);

    errorRadioButtonStyle =
        "QRadioButton {"
        "    padding: 8px;"
        "    border: 1px solid red;"
        "    border-radius: 6px;"
        "    spacing: 8px;"
        "}"
        "QRadioButton::indicator {"
        "    width: 12px;"
        "    height: 12px;"
        "    border: 2px solid rgba(73, 179, 78, 0.3);"
        "    border-radius: 7px;"
        "    background: #b5e8b7;"
        "}"
        "QRadioButton::indicator:checked {"
        "    background: qradialgradient("
        "        cx:0.5, cy:0.5, radius:0.5,"
        "        fx:0.5, fy:0.5,"
        "        stop:0 rgba(73, 179, 78, 0.6),"
        "        stop:0.5 rgba(73, 179, 78, 0.6),"
        "        stop:0.6 white,"
        "        stop:1 white"
        "    );"
        "    border-color: rgba(73, 179, 78, 0.7);"
        "}";


    // ставка и сумма ежемесячного платежа
    QString qlStyle = "QLabel {"
        "   background-color: rgba(225, 211, 255, 0.3);"
        "   color: black;"
        "   border-radius: 10px;"
        "   padding: 5px;"
        "}";

    ui->ql_rate_value->setStyleSheet(qlStyle);
    ui->ql_payment_value->setStyleSheet(qlStyle);
}

loan::~loan() {
    delete ui;
}


void loan::set_loan_info(int min_amount, int max_amount, int rate, const QString &name)
{
    username = name;
    interest_rate = rate;

    ui->ql_rate_value->setText(QString::number(rate) + " %");

    QString min_value = QString::number(min_amount);
    QString max_value = QString::number(max_amount);

    QString message = "Введите сумму от " + min_value + " до " + max_value;

    ui->loan_amount->setPlaceholderText(message);

    QIntValidator *validator = new QIntValidator(min_amount, max_amount, this);
    ui->loan_amount->setValidator(validator);
}


int loan::count_monthly_payment(int amount, int period, int rate)
{
    // дифференцированные платежи
    int x = amount / period;

    int k = amount * (rate / 100) * 30 / 365;

    return (x + k);
}


void loan::loan_taken_message()
{
    const int timeout_ms = 2500;

    QLabel* label = new QLabel(this);
    label->setFixedHeight(40);
    label->setFixedWidth(190);
    label->setAlignment(Qt::AlignCenter);

    label->setStyleSheet(
        "background-color: rgb(97, 197, 84);"
        "color: rgb(255, 255, 255);"
        "border-radius: 5px;"
        "padding: 10px;"
        "font-family: 'Gill Sans', sans-serif;"
        "font-size: 14px;"
        );
    label->setText("Кредит успешно оформлен!");

    int x = (this->width() - label->sizeHint().width()) / 2;
    int y = (this->height() - label->sizeHint().height()) / 20;

    label->move(x, y);
    label->show();

    emit update_profile();

    QTimer::singleShot(timeout_ms, label, &QLabel::deleteLater);
}


void loan::error_message(const QString &msg)
{
    const int timeout_ms = 2500;

    QLabel* label = new QLabel(this);

    label->setAlignment(Qt::AlignCenter);
    label->setText("Ошибка: " + msg);
    label->setStyleSheet(
        "background-color: rgb(155, 155, 155);"
        "color: rgb(255, 255, 255);"
        "border-radius: 5px;"
        "padding: 10px;"
        "font-family: 'Gill Sans', sans-serif;"
        "font-size: 14px;"
        );


    int x = (this->width() - label->sizeHint().width()) / 2;
    int y = (this->height() - label->sizeHint().height()) / 20;

    label->move(x, y);
    label->show();

    QTimer::singleShot(timeout_ms, label, &QLabel::deleteLater);
}

void loan::on_pb_take_clicked()
{
    int amount = ui->loan_amount->text().toInt();

    if (amount == 0 || ui->loan_amount->text().isEmpty()) {
        ui->loan_amount->setStyleSheet("border: 2px solid red;"
            "   border-radius: 10px;"
            "   padding: 5px;"
            "   font-size: 18px;"
            "   background-color: rgba(174, 208, 180, 0.2);");
        return;
    }

    int period = 0;
    if (ui->rb_6months->isChecked()) {
        period = 6;
    } else if (ui->rb_9months->isChecked()) {
        period = 9;
    } else if (ui->rb_12months->isChecked()) {
        period = 12;
    }

    if (period == 0) {
        ui->rb_6months->setStyleSheet(errorRadioButtonStyle);
        ui->rb_9months->setStyleSheet(errorRadioButtonStyle);
        ui->rb_12months->setStyleSheet(errorRadioButtonStyle);
        return;
    }

    http_client_loan->take_loan(amount, period, interest_rate, username);

    QTimer::singleShot(3500, this, [this]{
        ui->loan_amount->clear();
        ui->rb_6months->setChecked(false);
        ui->rb_9months->setChecked(false);
        ui->rb_12months->setChecked(false);
        ui->ql_payment_value->clear();

        ui->loan_amount->setStyleSheet(LineEditStyle);
        ui->rb_6months->setStyleSheet(RadioButtonStyle);
        ui->rb_9months->setStyleSheet(RadioButtonStyle);
        ui->rb_12months->setStyleSheet(RadioButtonStyle);

        this->hide();
    });
}


void loan::on_rb_6months_clicked()
{
    if (!ui->loan_amount->text().isEmpty()){
        int amount = ui->loan_amount->text().toInt();
        if (amount > 0) {
            int monthly_payment = count_monthly_payment(amount, 6, interest_rate);
            ui->ql_payment_value->setText(QString::number(monthly_payment));
        }
    }
}


void loan::on_rb_9months_clicked()
{
    if (!ui->loan_amount->text().isEmpty()){
        int amount = ui->loan_amount->text().toInt();
        if (amount > 0) {
            int monthly_payment = count_monthly_payment(amount, 9, interest_rate);
            ui->ql_payment_value->setText(QString::number(monthly_payment));
        }
    }
}


void loan::on_rb_12months_clicked()
{
    if (!ui->loan_amount->text().isEmpty()){
        int amount = ui->loan_amount->text().toInt();
        if (amount > 0) {
            int monthly_payment = count_monthly_payment(amount, 12, interest_rate);
            ui->ql_payment_value->setText(QString::number(monthly_payment));
        }
    }
}

