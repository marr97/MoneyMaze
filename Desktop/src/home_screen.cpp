#include "home_screen.h"
#include "ui_home_screen.h"
#include <QToolButton>
#include <QPropertyAnimation>
#include <QTimer>

home_screen::home_screen(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::home_screen) {
  ui->setupUi(this);
  this->setWindowTitle("Главная");

  // Имя пользователя

  ui->ql_username->setStyleSheet(
      "QLabel {"
      "   background-color: rgb(202, 219, 252);"
      "   color: black;"
      "   border-radius: 10px;"
      "   padding: 5px;"
      "}"
      );

  // Финансовые данные пользователя

  QString qlStyle_1 = "QLabel {"
                      "   background-color: rgb(245, 245, 245);"
                      "   color: black;"
                      "   border-radius: 10px;"
                      "   padding: 5px;"
                      "}";

  ui->ql_balance->setStyleSheet(qlStyle_1);
  ui->ql_monthly_min->setStyleSheet(qlStyle_1);
  ui->ql_debt->setStyleSheet(qlStyle_1);

  // Стрелочки

  QString arrowStyle = "QToolButton { border: none; "
                       "padding: 5px; }";

  ui->tb_modules->setArrowType(Qt::DownArrow);
  ui->tb_savings->setArrowType(Qt::DownArrow);
  ui->tb_loans->setArrowType(Qt::DownArrow);

  ui->tb_modules->setStyleSheet(arrowStyle);
  ui->tb_savings->setStyleSheet(arrowStyle);
  ui->tb_loans->setStyleSheet(arrowStyle);

  connect(ui->tb_savings, &QToolButton::clicked, this, &home_screen::tb_savings_down);
  connect(ui->tb_loans, &QToolButton::clicked, this, &home_screen::tb_loans_down);
  connect(ui->tb_modules, &QToolButton::clicked, this, &home_screen::tb_modules_down);

  // Лейблы

  QString qlStyle_2 = "QLabel {"
                    "   color: black;"
                    "   border-radius: 10px;"
                    "   padding: 5px;"
                    "}";

  ui->ql_modules->setStyleSheet(qlStyle_2);
  ui->ql_savings->setStyleSheet(qlStyle_2);
  ui->ql_loans->setStyleSheet(qlStyle_2);

  // Кнопки под лейблами

  QString buttonStyle_1 =
      "QPushButton {"
      "   background-color: rgb(245, 245, 245);"
      "   border-top: none;"
      "   text-align: center;"
      "   color: rgb(73, 179, 78);"
      "   border-radius: 8px;"
      "   padding: 5px;"
      "}"
      "QPushButton:hover {"
      "   background-color: rgb(225, 211, 255)"
      "}";

  QString buttonStyle_2 =
      "QPushButton {"
      "   background-color: rgb(245, 245, 245);"
      "   border-top: none;"
      "   text-align: center;"
      "   color: rgb(46, 47, 48);"
      "   border-radius: 8px;"
      "   padding: 5px;"
      "}"
      "QPushButton:hover {"
      "   background-color: rgb(225, 211, 255)"
      "}";



  ui->pb_make_loan->setStyleSheet(buttonStyle_1);
  ui->pb_make_deposit->setStyleSheet(buttonStyle_1);

  ui->pb_mod_loans->setStyleSheet(buttonStyle_2);
  ui->pb_mod_savings->setStyleSheet(buttonStyle_2);

  // Информация о текущем месяце игры

  QString buttonStyle_3 =
      "QPushButton {"
      "   background-color: rgba(174, 208, 180, 0.6);"
      "   border-top: none;"
      "   text-align: center;"
      "   color: grey;"
      "   border-radius: 8px;"
      "   padding: 5px;"
      "}"
      "QPushButton:hover {"
      "   background-color: rgb(151, 207, 169)"
      "}";

  ui->pb_next_month->setStyleSheet(buttonStyle_3);

  ui->ql_month->setStyleSheet(
      "QLabel {"
      "   color: grey;"
      "   padding: 5px;"
      "}"
      );




  // Виджеты с кнопками

  QString widgetStyle =  "QWidget {"
                        "   background: rgba(225, 211, 255, 0.3);"
                        "   border-radius: 10px;"
                        "   border: 5px;"
                        "   padding: 10px;"
                        "}";

  ui->widget_savings->setStyleSheet(widgetStyle);
  ui->widget_loans->setStyleSheet(widgetStyle);
  ui->widget_modules->setStyleSheet(widgetStyle);

  ui->widget_savings->setMaximumHeight(0);
  ui->widget_savings->setMinimumHeight(0);

  ui->widget_loans->setMaximumHeight(0);
  ui->widget_loans->setMinimumHeight(0);

  ui->widget_modules->setMaximumHeight(0);
  ui->widget_modules->setMinimumHeight(0);


  animation_savings = new QPropertyAnimation(ui->widget_savings, "maximumHeight");
  animation_savings->setDuration(250);

  animation_loans = new QPropertyAnimation(ui->widget_loans, "maximumHeight");
  animation_loans->setDuration(250);

  animation_modules = new QPropertyAnimation(ui->widget_modules, "maximumHeight");
  animation_modules->setDuration(250);

}


home_screen::~home_screen()
{
  delete ui;
  delete animation_modules;
  delete animation_savings;
  delete animation_loans;
}


void home_screen::tb_savings_down()
{
  if (is_savings_visible) {
    animation_savings->setStartValue(HEIGHT);
    animation_savings->setEndValue(0);
    animation_savings->start();

    ui->tb_savings->setArrowType(Qt::DownArrow);
  }
  else {
    animation_savings->setStartValue(0);
    animation_savings->setEndValue(HEIGHT);
    animation_savings->start();

    ui->tb_savings->setArrowType(Qt::UpArrow);
  }

  is_savings_visible = !is_savings_visible;
}

void home_screen::tb_loans_down()
{
  if (is_loans_visible) {
    animation_loans->setStartValue(HEIGHT);
    animation_loans->setEndValue(0);
    animation_loans->start();

    ui->tb_loans->setArrowType(Qt::DownArrow);
  }
  else {
    animation_loans->setStartValue(0);
    animation_loans->setEndValue(HEIGHT);
    animation_loans->start();

    ui->tb_loans->setArrowType(Qt::UpArrow);
  }

  is_loans_visible = !is_loans_visible;
}

void home_screen::tb_modules_down()
{
  if (is_modules_visible) {
    animation_modules->setStartValue(HEIGHT);
    animation_modules->setEndValue(0);
    animation_modules->start();

    ui->tb_modules->setArrowType(Qt::DownArrow);
  }
  else {
    animation_modules->setStartValue(0);
    animation_modules->setEndValue(HEIGHT);
    animation_modules->start();

    ui->tb_modules->setArrowType(Qt::UpArrow);
  }

  is_modules_visible = !is_modules_visible;
}

void home_screen::on_pb_next_month_clicked()
{
}


void home_screen::on_pb_mod_loans_clicked()
{
    QTimer::singleShot(200, this, [this]{
        ui_loan_module.show();
    });
}


void home_screen::on_pb_mod_savings_clicked()
{
    QTimer::singleShot(200, this, [this]{
        ui_savings_module.show();
    });
}

