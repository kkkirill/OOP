#ifndef LAB5_1_SHOP_H
#define LAB5_1_SHOP_H


#include <stack>
#include <vector>
#include <ctime>
#include <utility>
#include "Product.h"

typedef enum {
    Manager, Cashier, Cleaner, Director
} Position;

struct StaffPerson {
    std::string name;
    int age;
    Position position;
};

class Shop {
private:
    static std::vector<std::string> days;
    std::stack<std::pair<int, Product>> products;
    std::vector<std::pair<std::tm, std::tm>> schedule;
    std::vector<StaffPerson> staff;
public:
    Shop(std::initializer_list<std::pair<int, Product>> &products,
         const std::vector<std::pair<std::string, std::string>>& schedule,
         const std::vector<StaffPerson> &staff);

    virtual ~Shop();

    static const std::vector<std::string> &getDays();

    const std::stack<std::pair<int, Product>> &getProducts() const;

    const std::vector<std::pair<tm, tm>> &getSchedule() const;

    const std::vector<StaffPerson> &getStaff() const;

    static void setDays(const std::vector<std::string> &days);

    void setProducts(const std::stack<std::pair<int, Product>> &products);

    void setSchedule(const std::vector<std::pair<tm, tm>> &schedule);

    void setStaff(const std::vector<StaffPerson> &staff);

    Product buy_product();
};


#endif //LAB5_1_SHOP_H
