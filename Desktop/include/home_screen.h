#ifndef HOME_SCREEN_H
#define HOME_SCREEN_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QString>
#include <QWidget>
#include "loan_module.h"
#include "savings_module.h"

class httpClient;

namespace Ui {
class home_screen;
}

class home_screen : public QMainWindow {
  Q_OBJECT

public:
  explicit home_screen(QWidget *parent = nullptr);
  void set_username(const QString &name);
  void load_financial_profile();
  ~home_screen();

  enum GameStatus {
      WIN,
      LOSE
  };
  Q_ENUM(GameStatus)

private slots:
  void tb_modules_down();
  void tb_savings_down();
  void tb_loans_down();
  void on_pb_next_month_clicked();
  void on_pb_mod_loans_clicked();
  void on_pb_mod_savings_clicked();

  void show_game_result(GameStatus status);

  void show_financial_profile(int balance, int monthly_minimum, int total_loans,
                                    int interest_due, int salary, int current_month,
                                    const QString &status);

signals:
  void profile_requested(const QString &username);


  private:
  Ui::home_screen *ui;
  loan_module ui_loan_module;
  savings_module ui_savings_module;
  httpClient *http_client_home;

  QPropertyAnimation *animation_modules;
  QPropertyAnimation *animation_savings;
  QPropertyAnimation *animation_loans;

  bool is_modules_visible = false;
  bool is_savings_visible = false;
  bool is_loans_visible = false;

  QString username = "user";
  const int HEIGHT = 120;  // высота виджетов
};

#endif // HOME_SCREEN_H
