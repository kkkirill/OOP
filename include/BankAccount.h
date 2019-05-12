#ifndef LAB4_1_BANKACCOUNT_H
#define LAB4_1_BANKACCOUNT_H
#pragma once
#include <string>
#include <chrono>
#include <ctime>
#include "Person.h"

class BankAccount {
private:
    const std::string* const BANK;
    const int NUMBER;
    const Person *owner;
    time_t OPENING_DATE;
    int sum;
public:
    BankAccount();
    BankAccount(const std::string *BANK, int NUMBER, const Person *owner);
    ~BankAccount();

    friend std::ostream& operator<< (std::ostream& os, const BankAccount& account);

    const std::string get_bank() const;

    const int get_number() const;

    const Person *get_owner() const;

    int withdraw_sum(int amount);

    int get_current_sum() const;

    const time_t &get_opening_date();

    bool put_sum(int contributed_amount);

    void set_owner(Person *new_onwer);
};

#endif //LAB4_1_BANKACCOUNT_H
