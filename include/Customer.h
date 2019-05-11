#ifndef LAB5_1_CUSTOMER_H
#define LAB5_1_CUSTOMER_H

#pragma once

#include <ostream>
#include <utility>

class Customer {
private:
    std::string name;
    std::string address;
    std::string phone_number;
    long credit_number;
public:
    Customer(std::string name, std::string address, std::string phone_number, long credit_number);

    ~Customer();

    friend std::ostream& operator<<(std::ostream& os, const Customer& Customer);

    std::string get_name() const;

    std::string get_address() const;

    std::string get_phone_number() const;

    long get_credit_number() const;

    void set_name(std::string name);

    void set_address(std::string address);

    void set_phone_number(std::string phone_number);

    void set_credit_number(long credit_number);
};

#endif //LAB5_1_CUSTOMER_H
