#include "auth_window.h"
#include "ui_auth_window.h"
#include "ui_reg_window.h"
#include "reg_window.h"
#include "http_client.h"

auth_window::auth_window(QWidget *parent)
    : QDialog(parent), ui(new Ui::auth_window), http_client_auth(new httpClient(this))
{
  ui->setupUi(this);
  this->setWindowTitle("Вход");

  connect(http_client_auth, &httpClient::authorization_finished, this, &auth_window::handle_authorization_result);
  connect(http_client_auth, &httpClient::error_occurred, this, &auth_window::handle_network_error);


  ui->sign_in_pushButton->setStyleSheet(
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
  ui->pushButton_register->setStyleSheet(
      "QPushButton {"
      "background-color: rgb(236, 219, 252); color: grey;" "border-radius: 7px;"  // основной цвет
      "}"
      "QPushButton:hover {"
      "background-color: rgb(213, 197, 228); color: white;" // цвет при наведении
      "}"
      "QPushButton:pressed {"
      "background-color: rgb(213, 197, 228); color: white;" // цвет при нажатии
      "}"
      );
   ui->lineEdit_password->setEchoMode(QLineEdit::Password);
}

auth_window::~auth_window() { delete ui; }

void auth_window::on_lineEdit_login_textEdited(const QString &arg1)
{
  auth_window::user_login = arg1;
}

void auth_window::on_lineEdit_password_textEdited(const QString &arg1)
{
  auth_window::user_password = arg1;
}

QString auth_window::get_login()
{
  return auth_window::user_login;
}

QString auth_window::get_password()
{
  return auth_window::user_password;
}


void auth_window::handle_authorization_result(int status_code, const QString &error_msg)
{
    if (status_code == 200){
        http_client_auth->show_result("Вход в аккаунт выполнен успешно!", httpClient::Status::OK, this);

        QTimer::singleShot(2500 + 200, this, [this]{
            this->hide();
            ui_Home.set_username(get_login());
            ui_Home.load_financial_profile();
            ui_Home.show();
        });
    }
    else if (status_code >= 400){
        http_client_auth->show_result("Неверный логин или пароль", httpClient::Status::ERROR, this);
    } else {
        http_client_auth->show_result("Ошибка: " + error_msg, httpClient::Status::ERROR, this);
    }
}

void auth_window::handle_network_error(const QString &error){
    http_client_auth->show_result("Ошибка сети: " + error, httpClient::Status::NETWORK_ERROR, this);
}


void auth_window::on_sign_in_pushButton_clicked()
{
    http_client_auth->authorize(get_login(), get_password());
}


void auth_window::on_pushButton_register_clicked()
{
  this->hide();
  ui_Reg.show();
}

