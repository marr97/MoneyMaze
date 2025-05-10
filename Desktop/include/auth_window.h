#ifndef AUTH_WINDOW_H
#define AUTH_WINDOW_H

#include <QDialog>
#include "reg_window.h"
#include "http_client.h"
#include "json_parser.h"

namespace Ui {
class auth_window;
}

class auth_window : public QDialog {
  Q_OBJECT

public:
  explicit auth_window(QWidget *parent = nullptr);
  ~auth_window();
  QString get_login() const;
  QString get_password() const;

private slots:
  void on_lineEdit_password_textEdited(const QString &arg1);

  void on_lineEdit_login_textEdited(const QString &arg1);

  void on_pushButton_register_clicked();

  void on_sign_in_pushButton_clicked();

private:
  Ui::auth_window *ui;
  reg_window ui_Reg;


  QString user_login;
  QString user_password;
};

#endif // AUTH_WINDOW_H
