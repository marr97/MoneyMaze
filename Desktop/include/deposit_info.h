#ifndef DEPOSIT_INFO_H
#define DEPOSIT_INFO_H

#include <QWidget>
#include <QString>
#include <QJsonObject>
#include <QVector>
#include "http_client.h"


namespace Ui {
class deposit_info;
}

class deposit_info : public QWidget {
    Q_OBJECT

public:
    explicit deposit_info(QWidget *parent = nullptr);
    void get_deposit_data(const QString &username);
    void set_deposit_data(const QVector<QJsonObject> &deposit_list);
    ~deposit_info();

private slots:
    void on_tb_prev_clicked();
    void on_tb_next_clicked();

    void update_deposit_display();

private:
    Ui::deposit_info *ui;
    httpClient *http_client_deposit_info;

    QVector<QJsonObject> m_deposits;
    int deposit_id = 0;
};

#endif  // DEPOSIT_INFO_H
