#include "../include/Shop.h"

std::vector<std::string> Shop::days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};


Shop::Shop(std::initializer_list<std::pair<int, Product>> &products,
           const std::vector<std::pair<std::string, std::string>> &schedule,
           const std::vector<StaffPerson> &staff) {
}

Shop::~Shop() {
    for (int i = 0; i < products.size(); ++i) {
        products.pop();
    }
}

const std::vector<std::string> &Shop::getDays() {
    return days;
}

const std::stack<std::pair<int, Product>> &Shop::getProducts() const {
    return products;
}

const std::vector<std::pair<tm, tm>> &Shop::getSchedule() const {
    return schedule;
}

const std::vector<StaffPerson> &Shop::getStaff() const {
    return staff;
}

void Shop::setDays(const std::vector<std::string> &days) {
    Shop::days = days;
}

void Shop::setProducts(const std::stack<std::pair<int, Product>> &products) {
    Shop::products = products;
}

void Shop::setSchedule(const std::vector<std::pair<tm, tm>> &schedule) {
    Shop::schedule = schedule;
}

void Shop::setStaff(const std::vector<StaffPerson> &staff) {
    Shop::staff = staff;
}

Product Shop::buy_product() {

//    return Product(, Type::, 0);
}

