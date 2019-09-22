#ifndef LAB5_1_SHOP_H
#define LAB5_1_SHOP_H

#include <stack>
#include <vector>
#include <ctime>
#include <utility>
#include "Product.h"
#include "Customer.h"

typedef enum {
    Manager, Cashier, Cleaner, Director
} Position;

class Shop {
private:
    static std::vector<std::string> days;
    std::deque<std::pair<int, Product>> products;
    std::map<weekday, std::pair<std::tm, std::tm>> schedule;
    std::stack<Person> staff;
    const std::string KEY_VALUE;

    void show_staff();

    bool add_staff();

    bool remove_staff();

    std::pair<int, int> choose_product();

public:
    Shop(std::initializer_list<std::pair<int, Product>> &products,
         std::initializer_list<std::pair<weekday, std::pair<std::string, std::string>>> schedule,
         const std::deque<Person> &staff, const std::string KEY_VALUE);

    virtual ~Shop();

    static const std::vector<std::string> &getDays();

    const std::deque<std::pair<int, Product>> &getProducts() const;

    const std::map<weekday, std::pair<tm, tm>> &getSchedule() const;

    const std::stack<Person> &getStaff() const;

    static void setDays(const std::vector<std::string> &days);

    void setProducts(const std::initializer_list<std::pair<int, Product>> &products);

    void setSchedule(const std::map<weekday, std::pair<tm, tm>> &schedule);

    void setStaff(const std::initializer_list<Person> &staff);

    std::deque<std::pair<int, Product>> buy_products(Customer *customer);

    void show_products(std::deque<std::pair<int, int>> &temp_amount_values);

    void get_director_key_access(std::string key_value);
};


#endif //LAB5_1_SHOP_H
