#include "reg_window.h"
#include "ui_reg_window.h"
#include "http_client.h"


reg_window::reg_window(QWidget *parent)
    : QDialog(parent), ui(new Ui::reg_window)
{
    ui->setupUi(this);
    this->setWindowTitle("Регистрация");


    ui->pushButton_create_account->setStyleSheet(
        "QPushButton {"
        "background-color: rgb(140, 192, 155); color: white;" "border-radius: 10px;"  // основной цвет
        "}"
        "QPushButton:hover {"
        "background-color: rgb(128, 177, 145); color: grey;" // цвет при наведении
        "}"
        "QPushButton:pressed {"
        "background-color: rgb(128, 177, 145); color: grey;" // цвет при нажатии
        "}"
        );

    ui->lineEdit_password->setEchoMode(QLineEdit::Password);
    ui->lineEdit_confirmation->setEchoMode(QLineEdit::Password);

    // Максимальная длина имени пользователя и пароля
    ui->lineEdit_login->setMaxLength(20);
    ui->lineEdit_password->setMaxLength(20);
    ui->lineEdit_confirmation->setMaxLength(20);
}


reg_window::~reg_window() { delete ui; }

void reg_window::err_message(const QString& message) {
    const int timeout_ms = 2500;

    QLabel* label = new QLabel(this);
    label->setFixedHeight(50);
    label->setText(message);
    label->setAlignment(Qt::AlignCenter);

    label->setStyleSheet(
        "background-color: rgba(216, 58, 47, 0.9);"
        "color: rgb(255, 255, 255);"
        "border-radius: 5px;"
        "padding: 10px;"
        "font-family: 'Gill Sans', sans-serif;"
        "font-size: 14px;"
        );

    // Чтобы сообщение было посередине окна
    int x = (this->width() - label->sizeHint().width()) / 2;
    int y = (this->height() - label->sizeHint().height()) / 2;

    label->move(x, y);
    label->show();

    QTimer::singleShot(timeout_ms, label, &QLabel::deleteLater);
}



void reg_window::on_lineEdit_login_textEdited(const QString &arg1)
{
    reg_window::user_newlogin = arg1;
}


void reg_window::on_lineEdit_password_textEdited(const QString &arg1)
{
    reg_window::user_newpassword = arg1;
}


void reg_window::on_lineEdit_confirmation_textEdited(const QString &arg1)
{
    reg_window::user_password_confirmation = arg1;
}


QString reg_window::get_nickname()
{
    return user_newlogin;
}

QString reg_window::get_password()
{
    return user_newpassword;
}

QString reg_window::get_confirmation()
{
    return user_password_confirmation;
}

bool reg_window::check_password_confirmation()
{
    return (get_new_password() == get_confirmation());
}


void reg_window::on_pushButton_create_account_clicked() {
    if (get_new_login().length() < 3) {
        err_message("Логин должен содержать минимум 3 символа");
        return;
    }
    if (get_new_password().length() < 6){
        err_message("Пароль должен содержать минимум 6 символов");
        return;
    }
    if (!check_password_confirmation()){
        err_message("Подтверждение пароля не совпадает с исходным");
        return;
    }

    const int status_code = registrate(get_nickname(), get_password());

    if (status_code != 0){
        err_message("Произошла ошибка");
        return;
    }

    this->hide();
}
