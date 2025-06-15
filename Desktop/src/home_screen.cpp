#include "home_screen.h"
#include "ui_home_screen.h"
#include "http_client.h"
#include "loan.h"
#include <QToolButton>
#include <QLabel>
#include <QPropertyAnimation>
#include <QTimer>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QColor>

home_screen::home_screen(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::home_screen), http_client_home(new httpClient(this)) {
  ui->setupUi(this);
  this->setWindowTitle("Главная");

  connect(this, &home_screen::profile_requested, http_client_home, &httpClient::get_financial_profile);
  connect(http_client_home, &httpClient::financial_profile_received, this, &home_screen::show_financial_profile);
  connect(http_client_home, &httpClient::loan_info_received, this, &home_screen::loan_information);
  connect(&ui_loan, &loan::update_profile, this, &home_screen::update_financial_profile);
  connect(&ui_deposit, &deposit::update_profile, this, &home_screen::update_financial_profile);

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

  ui->ql_balance->setTextFormat(Qt::RichText);
  ui->ql_monthly_min->setTextFormat(Qt::RichText);
  ui->ql_debt->setTextFormat(Qt::RichText);
  ui->ql_month->setTextFormat(Qt::RichText);
  ui->ql_month->setAlignment(Qt::AlignLeft | Qt::AlignBottom);


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

  QString qlStyle_3 = "QLabel {"
                    "   color: black;"
                    "   border-radius: 10px;"
                    "   padding: 5px;"
                    "}";

  ui->ql_modules->setStyleSheet(qlStyle_3);
  ui->ql_savings->setStyleSheet(qlStyle_3);
  ui->ql_loans->setStyleSheet(qlStyle_3);

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

  ui->pb_my_loans->setStyleSheet(buttonStyle_2);
  ui->pb_my_savings->setStyleSheet(buttonStyle_2);

  ui->pb_make_loan->setStyleSheet(buttonStyle_1);
  ui->pb_make_deposit->setStyleSheet(buttonStyle_1);

  ui->pb_mod_loans->setStyleSheet(buttonStyle_2);
  ui->pb_mod_savings->setStyleSheet(buttonStyle_2);


  // Подписи под диаграммой

  QString qlStyle_2 = "QLabel {"
      "   background-color: rgb(245, 245, 245);"
      "   color: grey;"
      "   border-radius: 10px;"
      "   padding: 5px;"
      "}";

  ui->ql_chart_balance->setStyleSheet(qlStyle_2);

  ui->ql_chart_debt->setStyleSheet(qlStyle_2);

  ui->ql_chart_savings->setStyleSheet(qlStyle_2);


  ui->ql_chart_balance_value->setStyleSheet(
      "QLabel {"
      "   background-color: rgba(174, 208, 180, 0.6);"
      "   color: grey;"
      "   border-radius: 10px;"
      "   padding: 5px;"
      "}"
      );

  ui->ql_chart_debt_value->setStyleSheet(
      "QLabel {"
      "   background-color: rgba(217, 108, 103, 0.5);"
      "   color: grey;"
      "   border-radius: 10px;"
      "   padding: 5px;"
      "}"
      );

  ui->ql_chart_savings_value->setStyleSheet(
      "QLabel {"
      "   background-color: rgba(225, 211, 255, 0.6);"
      "   color: grey;"
      "   border-radius: 10px;"
      "   padding: 5px;"
      "}"
      );


  // Информация о текущем месяце игры

  QString buttonStyle_3 =
      "QPushButton {"
      "   background-color: rgba(174, 208, 180, 0.7);"
      "   border-top: none;"
      "   text-align: center;"
      "   color: white;"
      "   border-radius: 8px;"
      "   padding: 5px;"
      "}"
      "QPushButton:hover {"
      "   background-color: rgb(174, 208, 180)"
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
    http_client_home->next_month(username);
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


void home_screen::set_username(const QString &name)
{
    this->username = name;
    ui->ql_username->setText(username);
}

void home_screen::load_financial_profile()
{
    if (!username.isEmpty()) {
        emit profile_requested(username);
    }
}

void home_screen::update_financial_profile()
{
    if (!username.isEmpty()) {
        emit profile_requested(username);
    }
}

void home_screen::show_game_result(GameStatus status)
{
    const int timeout_ms = 5000;

    QLabel* label = new QLabel(this);
    label->setFixedHeight(90);
    label->setFixedWidth(420);
    label->setWordWrap(true);
    label->setMargin(5);
    label->setAlignment(Qt::AlignCenter);

    if (status == GameStatus::WIN){
        label->setStyleSheet(
            "background-color: rgb(97, 197, 84);"
            "color: rgb(255, 255, 255);"
            "border-radius: 5px;"
            "padding: 10px;"
            "font-family: 'Gill Sans', sans-serif;"
            "font-size: 14px;"
            );
        label->setText("Поздравляем с успешным завершением игры!");
    } else {
        label->setStyleSheet(
            "background-color: rgb(216, 58, 47);"
            "color: rgb(255, 255, 255);"
            "border-radius: 5px;"
            "padding: 10px;"
            "font-family: 'Gill Sans', sans-serif;"
            "font-size: 14px;"
            );
        label->setText("К сожалению, вы проиграли :( \n"
            "Сумма долга превысила ваш текущий баланс");
    }

    int x = (this->width() - label->sizeHint().width()) / 2;
    int y = (this->height() - label->sizeHint().height()) / 2;

    label->move(x, y);
    label->show();

    QTimer::singleShot(timeout_ms, label, &QLabel::deleteLater);
}


void home_screen::update_financial_chart(int balance, int debt, int savings)
{
    // очищение старой диаграммы
    QLayoutItem* item;
    while ((item = ui->chart_layout->takeAt(0))) {
        delete item->widget();
        delete item;
    }

    QPieSeries *series = new QPieSeries();

    series->append("", balance);
    series->append("", debt);
    series->append("", savings);

    if (balance > 0) {
        ui->ql_chart_balance->setVisible(true);
        ui->ql_chart_balance_value->setVisible(true);

        ui->ql_chart_balance_value->setText(QLocale().toString(balance));

    } else {
        ui->ql_chart_balance->setVisible(false);
        ui->ql_chart_balance_value->setVisible(false);
    }
    if (debt > 0) {
        ui->ql_chart_debt->setVisible(true);
        ui->ql_chart_debt_value->setVisible(true);

        ui->ql_chart_debt_value->setText(QLocale().toString(debt));
    } else {
        ui->ql_chart_debt->setVisible(false);
        ui->ql_chart_debt_value->setVisible(false);
    }
    if (savings > 0) {
        ui->ql_chart_savings->setVisible(true);
        ui->ql_chart_savings_value->setVisible(true);

        ui->ql_chart_savings_value->setText(QLocale().toString(savings));
    } else {
        ui->ql_chart_savings->setVisible(false);
        ui->ql_chart_savings_value->setVisible(false);
    }


    if (series->slices().size() > 0) { series->slices().at(0)->setColor(QColor(174, 208, 180, 180)); }
    if (series->slices().size() > 1) { series->slices().at(1)->setColor(QColor(217, 108, 103, 110)); }
    if (series->slices().size() > 2) { series->slices().at(2)->setColor(QColor(225, 211, 255, 180)); }

    for (auto slice : series->slices()) {
        slice->setLabelVisible(false);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setTitle("");
    chart->legend()->setVisible(false);

    chart->setBackgroundBrush(Qt::transparent);
    chart->setMargins(QMargins(0, 0, 0, 0));

    chart->setContentsMargins(-10, -10, -10, -10);
    series->setPieSize(0.7);

    QChartView *chartView = new QChartView(chart);
    chartView->setRenderHint(QPainter::Antialiasing);
    chartView->setStyleSheet("background: transparent");
    chartView->setFrameShape(QFrame::NoFrame);

    ui->chart_layout->addWidget(chartView);
}


void home_screen::show_financial_profile(int balance, int monthly_minimum, int total_loans,
                                        int interest_due, int salary, int current_month,
                                        const QString &status)
{
    if (status == "in_progress"){
        QString balance_str = "<div style='font-family: Gill Sans; font-size: 15pt; line-height: 1.5; margin: 0;'>"
            "Баланс<br>"
            "<br>"
            "</div>" + QLocale().toString(balance);

        QString motnthly_min_str = "<div style='font-family: Gill Sans; font-size: 15pt; line-height: 1.5; margin: 0;'>"
            "Месячный минимум<br>"
            "<br>"
            "</div>" + QLocale().toString(monthly_minimum);

        QString salary_str = "<div style='font-family: Gill Sans; font-size: 15pt; line-height: 1.5; margin: 0;'>"
            "Зарплата<br>"
            "<br>"
            "</div>" + QLocale().toString(salary);


        ui->ql_balance->setText(balance_str);
        ui->ql_monthly_min->setText(motnthly_min_str);
        ui->ql_debt->setText(salary_str);

        QString current_month_str = " Текущий месяц:  "+ QLocale().toString(current_month);

        ui->ql_month->setText(current_month_str);

        update_financial_chart(balance, total_loans, 0);

        user_balance = balance;

    } else if (status == "win"){
        show_game_result(GameStatus::WIN);
    } else {
        show_game_result(GameStatus::LOSE);
    }
}


void home_screen::loan_information(int min_loan_amount, int max_loan_amount, int interest_rate)
{
  ui_loan.set_loan_info(min_loan_amount, max_loan_amount, interest_rate, username);
}


void home_screen::on_pb_make_loan_clicked()
{
    http_client_home->get_loan_info(username);

    QTimer::singleShot(900, this, [this]{
        ui_loan.show();
    });
}

void home_screen::on_pb_my_loans_clicked()
{
    ui_loan_info.get_loan_data(username);

    QTimer::singleShot(900, this, [this]{
        ui_loan_info.show();
    });
}


void home_screen::on_pb_make_deposit_clicked()
{
    ui_deposit.set_info(username, user_balance);

    QTimer::singleShot(900, this, [this]{
        ui_deposit.show();
    });
}


void home_screen::on_pb_my_savings_clicked()
{
    ui_deposit_info.get_deposit_data(username);

    QTimer::singleShot(900, this, [this]{
        ui_deposit_info.show();
    });
}

