
#include <include/BankAccount.h>
#include <iomanip>

#include "include/BankAccount.h"

BankAccount::BankAccount() : BANK(nullptr), NUMBER(0), OPENING_DATE(0) {
}

BankAccount::BankAccount(const std::string *BANK, int NUMBER, const Person *owner) :
        BANK(BANK), NUMBER(NUMBER), owner(owner),
        OPENING_DATE(std::chrono::system_clock::to_time_t(std::chrono::system_clock::now())), sum(0) {
}

BankAccount::~BankAccount() {
    owner = nullptr;
    sum = 0;
}

const std::string BankAccount::get_bank() const {
    return *BANK;
}

const int BankAccount::get_number() const {
    return NUMBER;
}

const Person *BankAccount::get_owner() const {
    return owner;
}

int BankAccount::get_current_sum() const {
    return sum;
}

int BankAccount::withdraw_sum(int amount) {
    if (sum >= amount && amount > 0) {
        sum -= amount;
        return amount;
    }
    return 0;
}

const time_t &BankAccount::get_opening_date() {
    return OPENING_DATE;
}

bool BankAccount::put_sum(int contributed_amount) {
    sum += contributed_amount;
    return true;
}

void BankAccount::set_owner(Person *new_onwer) {
    owner = new_onwer;
}

std::ostream &operator<<(std::ostream &os, const BankAccount &account) {
    os << "Bank: " << *account.BANK << std::endl << "Opening date: "
       << std::put_time(&(*std::localtime(&account.OPENING_DATE)), "%H:%M:%S %d.%m.%Y") << std::endl
       << "Number: " << account.NUMBER << std::endl << "Current sum: " << account.sum << std::endl;
    return os;
}
