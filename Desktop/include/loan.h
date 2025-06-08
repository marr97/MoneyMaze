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


private:
    Ui::loan *ui;
    httpClient *http_client_loan;

    QString username = "user";

    QString ButtonStyle;
    QString LineEditStyle;
    QString RadioButtonStyle;
    QString errorRadioButtonStyle;
};

#endif  // LOAN_H
