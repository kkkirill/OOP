#include "../include/Customer.h"

Customer::Customer(std::string name, std::string address, std::string phone_number, long credit_number) :
        name(std::move(name)), address(std::move(address)), phone_number(std::move(phone_number)),
        credit_number(credit_number) {

}

Customer::~Customer() {
    name.clear();
    address.clear();
    phone_number.clear();
    credit_number = 0;
}

std::string Customer::get_name() const {
    return name;
}

std::string Customer::get_address() const {
    return address;
}

std::string Customer::get_phone_number() const {
    return phone_number;
}

long Customer::get_credit_number() const {
    return credit_number;
}

void Customer::set_name(std::string name) {
    this->name = std::move(name);
}

void Customer::set_address(std::string address) {
    this->address = std::move(address);
}

void Customer::set_phone_number(std::string phone_number) {
    this->phone_number = std::move(phone_number);
}

void Customer::set_credit_number(long credit_number) {
    this->credit_number = credit_number;
}

std::ostream &operator<<(std::ostream &os, const Customer &Customer) {
    os << "Name: " << Customer.name << "Address: " << Customer.address << "Phone number:" << Customer.phone_number
       << "Credit number: " << Customer.credit_number << std::endl;
    return os;
}
