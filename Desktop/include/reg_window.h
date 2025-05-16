#ifndef REG_WINDOW_H
#define REG_WINDOW_H

#include <QDialog>
#include <QLabel>
#include <QTimer>
#include <QString>
#include <QNetworkReply>

namespace Ui {
class reg_window;
}

class reg_window : public QDialog {
  Q_OBJECT

public:
  explicit reg_window(QWidget *parent = nullptr);
  ~reg_window();
  QString get_nickname();
  QString get_password();
  QString get_confirmation();
  bool check_password_confirmation();
  void err_message(const QString &message);
  void handle_server_response(QNetworkReply *reply);

private slots:
  void on_lineEdit_login_textEdited(const QString &arg1);

  void on_lineEdit_password_textEdited(const QString &arg1);

  void on_lineEdit_confirmation_textEdited(const QString &arg1);

  void on_pushButton_create_account_clicked();


private:
  Ui::reg_window *ui;

  QString user_newlogin;
  QString user_newpassword;
  QString user_password_confirmation;
};

#endif // REG_WINDOW_H
