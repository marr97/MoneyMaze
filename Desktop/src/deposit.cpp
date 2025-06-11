#include "deposit.h"
#include "ui_deposit.h"
#include "http_client.h"
#include <QIntValidator>
#include <QTimer>

deposit::deposit(QWidget *parent) : QWidget(parent), ui(new Ui::deposit), http_client_deposit(new httpClient(this)) {
    ui->setupUi(this);
    this->setWindowTitle("Оформление вклада");

    // кнопка оформить вклад
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


    // ввод суммы вклада
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

    ui->deposit_amount->setStyleSheet(LineEditStyle);
    ui->deposit_amount->setPlaceholderText("Введите сумму от " + QLocale().toString(MIN_DEPOSIT));

    // выбор количества месяцев и условий выплат
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

    ui->rb_payment_1->setStyleSheet(RadioButtonStyle);
    ui->rb_payment_2->setStyleSheet(RadioButtonStyle);

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


    // ставка
    QString qlStyle = "QLabel {"
        "   background-color: rgba(225, 211, 255, 0.3);"
        "   color: black;"
        "   border-radius: 10px;"
        "   padding: 5px;"
        "}";

    ui->ql_rate_value->setStyleSheet(qlStyle);
}

deposit::~deposit() {
    delete ui;
}


void deposit::set_info(const QString &name, int balance)
{
    username = name;
    user_balance = balance;

    int max_deposit = user_balance;
    if (max_deposit < MIN_DEPOSIT){
        max_deposit = MIN_DEPOSIT;
    }

    QIntValidator *validator = new QIntValidator(MIN_DEPOSIT, max_deposit, this);
    ui->deposit_amount->setValidator(validator);
}


// выплата в конце срока
void deposit::on_rb_payment_1_clicked()
{
    interest_rate = 18;
    ui->ql_rate_value->setText(QString::number(interest_rate) + " %");
}


// выплата каждый месяц
void deposit::on_rb_payment_2_clicked()
{
    interest_rate = 15;
    ui->ql_rate_value->setText(QString::number(interest_rate) + " %");
}


void deposit::show_message(MessageType msg_type, const QString &message)
{
    const int timeout_ms = 2500;

    QLabel* label = new QLabel(this);
    label->setFixedHeight(45);
    label->setFixedWidth(400);
    label->setText(message);
    label->setAlignment(Qt::AlignCenter);

    if (msg_type == MessageType::ERROR){
        label->setStyleSheet(
            "background-color: rgb(216, 58, 47);"
            "color: rgb(255, 255, 255);"
            "border-radius: 5px;"
            "padding: 10px;"
            "font-family: 'Gill Sans', sans-serif;"
            "font-size: 14px;"
            );
    } else if (msg_type == MessageType::OK){
        label->setStyleSheet(
            "background-color: rgb(97, 197, 84);"
            "color: rgb(255, 255, 255);"
            "border-radius: 5px;"
            "padding: 10px;"
            "font-family: 'Gill Sans', sans-serif;"
            "font-size: 14px;"
            );
    } else {
        return;
    }

    int x = (this->width() - label->sizeHint().width()) / 2;
    int y = (this->height() - label->sizeHint().height()) / 23;

    label->move(x, y);
    label->show();

    QTimer::singleShot(timeout_ms, label, &QLabel::deleteLater);
}



void deposit::on_pb_take_clicked()
{
    int amount = ui->deposit_amount->text().toInt();

    if (amount == 0 || ui->deposit_amount->text().isEmpty()) {
        ui->deposit_amount->setStyleSheet("border: 2px solid red;"
            "   border-radius: 10px;"
            "   padding: 5px;"
            "   font-size: 18px;"
            "   background-color: rgba(174, 208, 180, 0.2);");
        return;
    }

    if (amount > user_balance){
        show_message(ERROR, "Сумма вклада не может превышать ваш текущий баланс");
        return;
    }
    if (amount < MIN_DEPOSIT){
        show_message(ERROR, "Сумма вклада не может быть меньше " + QLocale().toString(MIN_DEPOSIT));
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

    http_client_deposit->make_deposit(amount, period, interest_rate, username);

    QTimer::singleShot(3500, this, [this]{
        ui->deposit_amount->clear();
        ui->rb_6months->setChecked(false);
        ui->rb_9months->setChecked(false);
        ui->rb_12months->setChecked(false);
        ui->rb_payment_1->setChecked(false);
        ui->rb_payment_2->setChecked(false);

        ui->deposit_amount->setStyleSheet(LineEditStyle);
        ui->rb_6months->setStyleSheet(RadioButtonStyle);
        ui->rb_9months->setStyleSheet(RadioButtonStyle);
        ui->rb_12months->setStyleSheet(RadioButtonStyle);
        ui->rb_payment_1->setStyleSheet(RadioButtonStyle);
        ui->rb_payment_2->setStyleSheet(RadioButtonStyle);

        this->hide();
    });
}

