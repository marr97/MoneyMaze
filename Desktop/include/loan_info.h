#ifndef LOAN_INFO_H
#define LOAN_INFO_H

#include <QWidget>
#include "http_client.h"

namespace Ui {
class loan_info;
}

class loan_info : public QWidget {
    Q_OBJECT

public:
    explicit loan_info(QWidget *parent = nullptr);
    void set_loan_data(int amount, int period, int rate, int passed_months);
    ~loan_info();

private:
    Ui::loan_info *ui;
    httpClient http_client_loan_info;
};

#endif  // LOAN_INFO_H
