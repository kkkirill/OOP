#ifndef LAB4_1_BANK_H
#define LAB4_1_BANK_H
#pragma once

#include <deque>
#include <ctime>
#include <utility>
#include <algorithm>
#include <iostream>
#include <conio.h>
#include <regex>
#include <list>
#include <iomanip>
#include "BankAccount.h"

typedef enum {
    Monday, Tuesday, Wednesday, Thursday, Friday, Saturday, Sunday
} weekday;

class Bank {
private:
    int list_account_number;
    std::list<BankAccount*> accounts;
    std::string name;
    std::deque<Person> &staff;
    std::map<weekday, std::pair<std::tm, std::tm>> schedule;
public:
    static std::vector<std::string> days;
    Bank(std::string name, std::deque<Person> &staff,
         std::initializer_list<std::pair<weekday, std::pair<std::string, std::string>>> work_schedule);

    friend std::ostream &operator<<(std::ostream &os, const Bank &bank);

    std::deque<Person> &get_staff();

    std::map<weekday, std::pair<std::tm, std::tm>> get_schedule();

    void set_staff(std::deque<Person> &staff);

    void set_schedule(std::initializer_list<std::pair<weekday, std::pair<std::string, std::string>>> schedule);

    void perform_services(Person *client);

    inline void show_services();

    int choose_account(std::list<BankAccount *> accounts, std::string text = "");

    BankAccount *find_account(int number);

    std::list<BankAccount *> find_accounts(Person *client);

    int input_choice(const std::string &text, const int &left, const int &right, bool isRequired = false);

    std::string input_account_number();

    void show_account_status(Person *client);

    void register_account(Person *client);

    bool close_account(Person *client);

    bool put_in_account(Person *client, int sum);

    int withdraw_from_account(Person *client, int sum);

    void sort(Person *client, bool by_decendance, bool by_sum = false);

    bool transfer(Person *client, int sum);

    std::map<weekday, std::pair<std::tm, std::tm>>
    convert(std::initializer_list<std::pair<weekday, std::pair<std::string, std::string>>> work_schedule);
};

#endif //LAB4_1_BANK_H
