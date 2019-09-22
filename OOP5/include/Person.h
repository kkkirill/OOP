#ifndef LAB5_1_PERSON_H
#define LAB5_1_PERSON_H

#pragma once
#include <iostream>
#include <string>
#include <utility>
#include <deque>
#include <iomanip>

typedef enum {
    MALE, FEMALE
} Gender;

class Person {
protected:
    std::string name;
    int date_of_birth;
    std::string address;
    Gender gender;
    std::string nationality;
public:
    Person(std::string name, int date_of_birth, std::string address, Gender gender, std::string nationality);

    ~Person();

    friend std::ostream& operator<<(std::ostream& os, const Person& person);

    std::string get_name() const;

    int get_date_of_birth() const;

    std::string get_address() const;

    Gender get_gender() const;

    std::string get_nationality() const;

    void set_name(std::string name);

    void set_date_of_birth(int date_of_birth);

    void set_address(std::string address);

    void set_gender(Gender gender);

    void set_nationality(std::string nationality);
};


#endif //LAB5_1_PERSON_H
