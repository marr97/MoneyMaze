#ifndef LOAN_INFO_H
#define LOAN_INFO_H

#include <QWidget>
#include <QVector>
#include <QJsonObject>
#include "http_client.h"

namespace Ui {
class loan_info;
}

class loan_info : public QWidget {
    Q_OBJECT

public:
    explicit loan_info(QWidget *parent = nullptr);
    void get_loan_data(const QString &username);
    void set_loan_data(const QVector<QJsonObject> &loans_list);
    ~loan_info();

private slots:
    void on_tb_prev_clicked();
    void on_tb_next_clicked();

    void update_loan_display();
    int count_next_payment(int amount, int rate, int period);

private:
    Ui::loan_info *ui;
    httpClient *http_client_loan_info;

    QVector<QJsonObject> m_loans;
    int loan_id = 0;
};

#endif  // LOAN_INFO_H
