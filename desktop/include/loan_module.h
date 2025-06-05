#ifndef LOAN_MODULE_H
#define LOAN_MODULE_H

#include <QWidget>
#include <QGraphicsOpacityEffect>
#include <QPropertyAnimation>
#include <QStringList>

namespace Ui {
class loan_module;
}

class loan_module : public QWidget {
    Q_OBJECT

public:
    explicit loan_module(QWidget *parent = nullptr);
    ~loan_module();

private slots:
    void on_pb_next_clicked();
    void fade_out_text_finished();
    void loan_module_finished();

private:
    Ui::loan_module *ui;

    QGraphicsOpacityEffect *text_opacity_effect;
    QPropertyAnimation *fade_out;
    QPropertyAnimation *fade_in;
    QStringList texts;
    QStringList headings;
    int text_id = 0;
    int heading_id = 0;

    const int text_last_id = 4;
};

#endif  // LOAN_MODULE_H
