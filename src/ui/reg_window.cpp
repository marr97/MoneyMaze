#include "reg_window.h"
#include "ui_reg_window.h"

reg_window::reg_window(QWidget *parent)
    : QDialog(parent), ui(new Ui::reg_window)
{
  ui->setupUi(this);
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
}

reg_window::~reg_window() { delete ui; }

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


QString reg_window::get_new_login()
{
  return user_newlogin;
}

QString reg_window::get_new_password()
{
  return user_newpassword;
}

QString reg_window::get_confirmation()
{
  return user_password_confirmation;
}

bool reg_window::check_password_confirmation()
{
  return (user_newpassword == user_password_confirmation);
}

void reg_window::on_pushButton_create_account_clicked() {
    
  json regData = create_registration_json(*this);
  send_registration_data(regData);
  this->hide();
}

