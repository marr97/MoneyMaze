#ifndef PROFILE_WINDOW_H
#define PROFILE_WINDOW_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>


namespace Ui {
class profile_window;
}

class profile_window : public QDialog {
    Q_OBJECT

public:
    explicit profile_window(QWidget *parent = nullptr);
    ~profile_window();
    
    // Setters for updating profile data
    void setUsername(const QString &username);
    void setDailyMinimum(double amount);
    void setFreeCash(double amount);
    void setLoanDebt(double amount);
    
    // Refresh profile data from server
    void refreshProfileData();

private slots:
    void on_takeLoan_pushButton_clicked();
    void on_payLoan_pushButton_clicked();
    void on_logout_pushButton_clicked();
    void on_refresh_pushButton_clicked();

private:
    Ui::profile_window *ui;
    
    // User data
    QString username;
    double dailyMinimum;
    double freeCash;
    double loanDebt;
    
    // Helper methods
    void updateFinancialDisplay();
    void sendProfileRequest();
};

#endif // PROFILE_WINDOW_H