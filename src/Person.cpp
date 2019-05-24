#include "../include/Person.h"

Person::Person(std::string name, int date_of_birth, std::string address, Gender gender, std::string nationality) :
        name(std::move(name)), date_of_birth(date_of_birth), address(std::move(address)), gender(gender), nationality(
        std::move(nationality)) {
}

Person::~Person() {
    name.clear();
    address.clear();
    nationality.clear();
    date_of_birth = 0;
}

std::string Person::get_name() const {
    return name;
}

int Person::get_date_of_birth() const {
    return date_of_birth;
}

std::string Person::get_address() const {
    return address;
}

Gender Person::get_gender() const {
    return gender;
}

std::string Person::get_nationality() const {
    return nationality;
}

void Person::set_name(std::string name) {
    this->name = std::move(name);
}

void Person::set_date_of_birth(int date_of_birth) {
    this->date_of_birth = date_of_birth;
}

void Person::set_address(std::string address) {
    this->address = std::move(address);
}

void Person::set_gender(Gender gender) {
    this->gender = gender;
}

void Person::set_nationality(std::string nationality) {
    this->nationality = std::move(nationality);
}

std::ostream &operator<<(std::ostream &os, const Person &person) {
    os << "Name: " << std::left << std::setw(10) << person.name
    << "Year of Birth: " << std::left << std::setw(7) << person.date_of_birth
    << "Address: " << std::left << std::setw(35)<< person.address
    << "Gender: " << std::left << std::setw(10) << (person.gender ? "Female" : "Male")
    << "Nationality: " << std::left << std::setw(3) << person.nationality << std::endl;
    return os;
}
