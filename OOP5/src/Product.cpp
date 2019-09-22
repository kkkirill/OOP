#include "../include/Product.h"


Product::Product(std::string name, Type type, int cost) : name(std::move(name)), type(type), cost(cost){
}

Product::~Product() {
    name.clear();
}

std::string Product::get_name() {
    return name;
}

Type Product::get_type() {
    return type;
}

int Product::get_cost() {
    return cost;
}

void Product::set_name(std::string name) {
    this->name = std::move(name);
}

void Product::set_type(Type type) {
    this->type = type;
}

void Product::set_cost(int cost) {
    this->cost = cost;
}

inline std::string get_type(Type type) {
    std::string str_type;
    switch (type) {
        case 0:
            str_type = "Food";
            break;
        case 1:
            str_type = "Technique";
            break;
        case 2:
            str_type = "Household";
            break;
        case 3:
            str_type = "Medicine";
            break;
        default:
            str_type = "Something";
            break;
    }
    return str_type;
}

std::ostream &operator<<(std::ostream &os, const Product &person) {
    os << "Name: " << std::left << std::setw(15) << person.name
       << "\tType: " << std::left << std::setw(10) << get_type(person.type)
       << "\tCost: " << std::left << std::setw(5) << person.cost;
    return os;
}
