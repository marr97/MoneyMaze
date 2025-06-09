#ifndef LOAN_H
#define LOAN_H

#include <QWidget>
#include <QString>
#include "http_client.h"

namespace Ui {
class loan;
}

class loan : public QWidget {
    Q_OBJECT

public:
    explicit loan(QWidget *parent = nullptr);
    void set_loan_info(int min_amount, int max_amount, int rate, const QString &name);
    ~loan();

private slots:
    void on_pb_take_clicked();
    int count_monthly_payment(int amount, int period, int rate);
    void loan_taken_message();
    void error_message(const QString &msg);

    void on_rb_6months_clicked();
    void on_rb_9months_clicked();
    void on_rb_12months_clicked();

signals:
    void update_profile();

private:
    Ui::loan *ui;
    httpClient *http_client_loan;

    QString username = "user";
    int interest_rate = 0;

    QString ButtonStyle;
    QString LineEditStyle;
    QString RadioButtonStyle;
    QString errorRadioButtonStyle;
};

#endif  // LOAN_H
