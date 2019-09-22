#ifndef LAB5_1_CUSTOMER_H
#define LAB5_1_CUSTOMER_H

#pragma once

#include <ostream>
#include <utility>
#include "Bank.h"

    class Customer : public Person {
    private:
        Bank *bank;
        const Person* const person;
    public:
        Customer(const Person* person, Bank* bank);
        ~Customer();

        friend std::ostream &operator<<(std::ostream &os, const Customer &Customer);

        int withdraw_sum(int sum) const;
        const Person* const get_person();
    };

#endif //LAB5_1_CUSTOMER_H
