#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "auth_window.h"
#include "reg_window.h"
#include "ui_reg_window.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow)
{
  ui->setupUi(this);
  this->setWindowTitle(" ");

  ui->pushButton_start->setStyleSheet(
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
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::on_pushButton_start_clicked()
{
  ui_Auth.show();
}

