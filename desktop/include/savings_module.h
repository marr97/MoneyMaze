#ifndef SAVINGS_MODULE_H
#define SAVINGS_MODULE_H

#include <QWidget>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QStringList>

namespace Ui {
class savings_module;
}

class savings_module : public QWidget {
    Q_OBJECT

public:
    explicit savings_module(QWidget *parent = nullptr);
    ~savings_module();

private slots:
    void on_pb_next_clicked();
    void fade_out_text_finished();
    void savings_module_finished();

private:
    Ui::savings_module *ui;

    QGraphicsOpacityEffect *text_opacity_effect;
    QPropertyAnimation *fade_out;
    QPropertyAnimation *fade_in;
    QStringList texts;
    QStringList headings;
    int text_id = 0;
    int heading_id = 0;

    const int text_last_id = 4;
};

#endif  // SAVINGS_MODULE_H
