#include "reg_window.h"
#include "ui_reg_window.h"
#include "http_client.h"

reg_window::reg_window(QWidget *parent)
    : QDialog(parent), ui(new Ui::reg_window), http_client(new httpClient(this))
{
    ui->setupUi(this);
    this->setWindowTitle("Регистрация");

    connect(http_client, &httpClient::registration_finished, this, &reg_window::handle_registration_result);
    connect(http_client, &httpClient::error_occurred, this, &reg_window::handle_network_error);


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


reg_window::~reg_window() {
    delete ui;
}

void reg_window::show_message(const QString &message, int message_type)
{
    const int timeout_ms = 2500;

    QLabel* label = new QLabel(this);
    label->setFixedHeight(50);
    label->setText(message);
    label->setAlignment(Qt::AlignCenter);

    if (message_type == ERROR){
        label->setStyleSheet(
            "background-color: rgba(216, 58, 47, 0.9);"
            "color: rgb(255, 255, 255);"
            "border-radius: 5px;"
            "padding: 10px;"
            "font-family: 'Gill Sans', sans-serif;"
            "font-size: 14px;"
            );
    } else if (message_type == SUCCESS){
        label->setStyleSheet(
            "background-color: rgba(97, 197, 84, 0.9);"
            "color: rgb(255, 255, 255);"
            "border-radius: 5px;"
            "padding: 10px;"
            "font-family: 'Gill Sans', sans-serif;"
            "font-size: 14px;"
            );
    } else {
        return;
    }

    // Чтобы сообщение было посередине окна
    int x = (this->width() - label->sizeHint().width()) / 2;
    int y = (this->height() - label->sizeHint().height()) / 2;

    label->move(x, y);
    label->show();

    QTimer::singleShot(timeout_ms, label, &QLabel::deleteLater);
}

void reg_window::handle_registration_result(int status_code){
    if (status_code == 200){
        show_message("Вы успешно зарегестрировались!", SUCCESS);

        QTimer::singleShot(2500 + 200, this, [this]{
            this->hide();
        });

    }
    else {
        show_message("Ошибка регистрации", ERROR);
    }
}


void reg_window::handle_network_error(const QString &error){
    show_message("Ошибка сети: " + error, ERROR);
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
    return (get_password() == get_confirmation());
}


void reg_window::on_pushButton_create_account_clicked() {
    if (get_nickname().length() < 3) {
        show_message("Логин должен содержать минимум 3 символа", ERROR);
        return;
    }
    if (get_password().length() < 6){
        show_message("Пароль должен содержать минимум 6 символов", ERROR);
        return;
    }
    if (!check_password_confirmation()){
        show_message("Подтверждение пароля не совпадает с исходным", ERROR);
        return;
    }


    http_client->registrate(get_nickname(), get_password());
}
