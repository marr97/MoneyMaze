#include "auth_window.h"
#include "ui_auth_window.h"
#include "ui_reg_window.h"
#include "reg_window.h"

auth_window::auth_window(QWidget *parent)
    : QDialog(parent), ui(new Ui::auth_window)
{
  ui->setupUi(this);
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


void auth_window::on_sign_in_pushButton_clicked()
{
  this->hide();
}


void auth_window::on_pushButton_register_clicked()
{
  this->hide();
  ui_Reg.show();
}

