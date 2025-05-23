#ifndef AUTH_WINDOW_H
#define AUTH_WINDOW_H

#include <QDialog>
#include "reg_window.h"
#include "home_screen.h"

class httpClient;

namespace Ui {
class auth_window;
}

class auth_window : public QDialog {
  Q_OBJECT

public:
  explicit auth_window(QWidget *parent = nullptr);
  ~auth_window();
  QString get_login();
  QString get_password();

private slots:
  void on_lineEdit_password_textEdited(const QString &arg1);
  void on_lineEdit_login_textEdited(const QString &arg1);
  void on_pushButton_register_clicked();
  void on_sign_in_pushButton_clicked();

  void handle_authorization_result(int status_code, const QString &error_msg);
  void handle_network_error(const QString &error);


private:
  Ui::auth_window *ui;
  reg_window ui_Reg;
  home_screen ui_Home;
  httpClient *http_client_auth;

  QString user_login;
  QString user_password;
};

#endif // AUTH_WINDOW_H
