#ifndef PLAYER_H
#define PLAYER_H

#include <string>

class Player {
private:
    double cash;
    double debt;
    double savings;
    double daily_minimum;

public:
    Player(double startCash, double minDaily);

    double get_cash() const;
    double get_debt() const;
    double get_savings() const;
    double get_daily_minimum() const;

    void spend_money(double amount);
    void take_credit(double amount);
    void deposit_money(double amount); // cash -> savings
    void withdraw_money(double amount); // savings -> cash
    void daily_expense();
};

#endif // PLAYER_H