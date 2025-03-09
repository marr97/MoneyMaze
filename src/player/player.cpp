#include "player.h"
#include <iostream>

void Player::spend_money(double amount) {
    if (amount <= cash) {
        cash -= amount;
    } else {
        std::cout << "Недостаточно средств :(";
    }
}

void Player::take_credit(double amount) {
    cash += amount;
    debt += amount;
    std::cout << "Кредит взят: " << amount << "\n";
}

void Player::deposit_money(double amount) {
    if (amount <= cash) {
        cash -= amount;
        savings += amount;
    } else {
        std::cout << "Недостаточно средств для депозита!\n";
    }
}

void Player::withdraw_money(double amount) {
    if (amount <= savings) {
        cash += amount;
        savings -= amount;
    } else {
        std::cout << "Недостаточно средств на вкладе!\n";
    }
}

void Player::daily_expense() {
    if (daily_minimum <= cash) {
        cash -= daily_minimum;
    } else {
        std::cout << "Недостаточно средств для покрытия прожиточного минимума. Вы банкрот!\n";
    }
}
