#ifndef LAB5_1_PRODUCT_H
#define LAB5_1_PRODUCT_H

#pragma once
#include <string>
#include <iostream>
#include <utility>
#include <iomanip>

typedef enum {
    Food, Technique, Household, Medicine
} Type;

class Product {
private:
    std::string name;
    Type type;
    int cost;
public:
    Product(std::string name, Type type, int cost);

    ~Product();

    friend std::ostream& operator<<(std::ostream& os, const Product& person);

    std::string get_name();

    Type get_type();

    int get_cost();

    void set_name(std::string name);

    void set_type(Type type);

    void set_cost(int cost);
};


#endif
