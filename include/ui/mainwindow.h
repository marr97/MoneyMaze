#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include "auth_window.h"
#include "reg_window.h"

QT_BEGIN_NAMESPACE
namespace Ui {
  class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
  Q_OBJECT

public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow();


private slots:
  void on_pushButton_start_clicked();

private:
  Ui::MainWindow *ui;
  auth_window ui_Auth;
  reg_window ui_Reg;

  QString user_login;
  QString user_password;

};
#endif // MAINWINDOW_H
