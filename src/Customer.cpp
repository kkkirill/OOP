#include "../include/Customer.h"

Customer::Customer(const Person* person, Bank *bank) : person(person), bank(bank), Person(*person){
}

Customer::~Customer() {
    bank = nullptr;
};

std::ostream &operator<<(std::ostream &os, const Customer &Customer) {
    os << static_cast<Person>(Customer) << std::endl;
    return os;
}

int Customer::withdraw_sum(int sum) const{
    return bank->withdraw_from_account(const_cast<Person*>(person), sum);
}

const Person *const Customer::get_person() {
    return person;
}
