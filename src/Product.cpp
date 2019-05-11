#include <utility>

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
