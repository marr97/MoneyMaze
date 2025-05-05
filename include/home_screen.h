#ifndef HOME_SCREEN_H
#define HOME_SCREEN_H

#include <QMainWindow>
#include <QPropertyAnimation>
#include <QString>
#include <QWidget>

namespace Ui {
class home_screen;
}

class home_screen : public QMainWindow {
  Q_OBJECT

public:
  explicit home_screen(QWidget *parent = nullptr);
  ~home_screen();


private slots:
  void tb_modules_down();
  void tb_savings_down();
  void tb_loans_down();

private:
  Ui::home_screen *ui;

  QPropertyAnimation *animation_modules;
  QPropertyAnimation *animation_savings;
  QPropertyAnimation *animation_loans;

  bool is_modules_visible = false;
  bool is_savings_visible = false;
  bool is_loans_visible = false;

  const int HEIGHT = 120;  // высота виджетов
};

#endif // HOME_SCREEN_H
