#ifndef REG_WINDOW_H
#define REG_WINDOW_H

#include <QDialog>
#include <QLabel>
#include <QTimer>
#include <QString>
#include <QNetworkReply>

class httpClient;

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
  void show_message(const QString &message, int message_type);
  void handle_registration_result(int status_code, const QString &error_msg);
  void handle_network_error(const QString &error);

private slots:
  void on_lineEdit_login_textEdited(const QString &arg1);

  void on_lineEdit_password_textEdited(const QString &arg1);

  void on_lineEdit_confirmation_textEdited(const QString &arg1);

  void on_pushButton_create_account_clicked();


private:
  Ui::reg_window *ui;
  httpClient *http_client;

  QString user_newlogin;
  QString user_newpassword;
  QString user_password_confirmation;
  const int SUCCESS = 0;
  const int ERROR = 1;
  const int NETWORK_ERROR = 2;
};

#endif // REG_WINDOW_H
