#ifndef DEPOSIT_H
#define DEPOSIT_H

#include <QWidget>
#include <QString>
#include "http_client.h"

namespace Ui {
class deposit;
}

class deposit : public QWidget {
    Q_OBJECT

public:
    explicit deposit(QWidget *parent = nullptr);
    void set_info(const QString &name, int balance);
    ~deposit();

    enum MessageType {
        OK,
        ERROR
    };
    Q_ENUM(MessageType)


private slots:
    void on_rb_payment_1_clicked();
    void on_rb_payment_2_clicked();
    void on_pb_take_clicked();

    void show_message(MessageType msg_type, const QString &message);

private:
    Ui::deposit *ui;
    httpClient *http_client_deposit;

    QString username = "user";
    int interest_rate = 0;

    QString ButtonStyle;
    QString LineEditStyle;
    QString RadioButtonStyle;
    QString errorRadioButtonStyle;

    const int MIN_DEPOSIT = 10000;
    int user_balance = 0;
};

#endif  // DEPOSIT_H
