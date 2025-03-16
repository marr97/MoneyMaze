#include "ui/profile_window.h"
#include "ui_profile_window.h"
#include <QMessageBox>

profile_window::profile_window(QWidget *parent)
    : QDialog(parent), ui(new Ui::profile_window),
      dailyMinimum(0.0), freeCash(0.0), loanDebt(0.0)
{
    ui->setupUi(this);
    
    this->setMinimumSize(600, 600);
    updateFinancialDisplay();
}

profile_window::~profile_window()
{
    delete ui;
}

void profile_window::setUsername(const QString &username)
{
    this->username = username;
    ui->label_username->setText("Имя пользователя: " + username);
}

void profile_window::setDailyMinimum(double amount)
{
    this->dailyMinimum = amount;
    updateFinancialDisplay();
}

void profile_window::setFreeCash(double amount)
{
    this->freeCash = amount;
    updateFinancialDisplay();
}

void profile_window::setLoanDebt(double amount)
{
    this->loanDebt = amount;
    updateFinancialDisplay();
}

void profile_window::updateFinancialDisplay()
{
    // Обновление отображения финансовой информации
    ui->value_daily->setText(QString::number(dailyMinimum, 'f', 2) + " ₽");
    ui->value_cash->setText(QString::number(freeCash, 'f', 2) + " ₽");
    ui->value_loan->setText(QString::number(loanDebt, 'f', 2) + " ₽");
    
    // Изменение цвета долга в зависимости от суммы
    if (loanDebt > 0) {
        ui->value_loan->setStyleSheet("color: red;");
    } else {
        ui->value_loan->setStyleSheet("color: green;");
    }
}

void profile_window::refreshProfileData()
{
    // Здесь будет вызов сервера для получения обновленных данных профиля
    QMessageBox::information(this, "Обновление профиля", 
                            "Запрос на обновление профиля отправлен.");
}

void profile_window::on_takeLoan_pushButton_clicked()
{
    QMessageBox::information(this, "Кредит", 
                            "Открытие модуля для получения кредита...");
}

void profile_window::on_payLoan_pushButton_clicked()
{
    if (loanDebt <= 0) {
        QMessageBox::information(this, "Погашение кредита", 
                                "У вас нет задолженности по кредиту.");
        return;
    }
    
    if (freeCash < loanDebt) {
        QMessageBox::warning(this, "Погашение кредита", 
                            "У вас недостаточно средств для погашения кредита.");
        return;
    }
    
    QMessageBox::information(this, "Погашение кредита", 
                            "Запрос на погашение кредита отправлен.");
}

void profile_window::on_refresh_pushButton_clicked()
{
    refreshProfileData();
}

void profile_window::on_logout_pushButton_clicked()
{
    QMessageBox::information(this, "Выход", "Выход из аккаунта...");
    this->close();
}