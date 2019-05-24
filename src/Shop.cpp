#include "../include/Shop.h"


std::vector<std::string> Shop::days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};


Shop::Shop(std::initializer_list<std::pair<int, Product>> &products,
           std::initializer_list<std::pair<weekday, std::pair<std::string, std::string>>> schedule,
           const std::deque<Person> &staff, const std::string KEY_VALUE) :
        products(products), staff(staff), KEY_VALUE(KEY_VALUE) {
    this->schedule = std::move(Bank::convert(schedule));
}

Shop::~Shop() {
    products.clear();
    schedule.clear();
    while (!staff.empty()) {
        staff.pop();
    }
}

const std::vector<std::string> &Shop::getDays() {
    return days;
}

const std::deque<std::pair<int, Product>> &Shop::getProducts() const {
    return products;
}

const std::map<weekday, std::pair<tm, tm>> &Shop::getSchedule() const {
    return schedule;
}

const std::stack<Person> &Shop::getStaff() const {
    return staff;
}

void Shop::setDays(const std::vector<std::string> &days) {
    Shop::days = days;
}

void Shop::setProducts(const std::initializer_list<std::pair<int, Product>> &products) {
    for (auto &product : products) {
        Shop::products.emplace_back(product);
    }
}

void Shop::setSchedule(const std::map<weekday, std::pair<tm, tm>> &schedule) {
    Shop::schedule = schedule;
}

void Shop::setStaff(const std::initializer_list<Person> &staff) {
    for (auto &item : staff) {
        Shop::staff.push(item);
    }
}

std::deque<std::pair<int, Product>> Shop::buy_products(Customer *customer) {
    std::deque<std::pair<int, Product>> bin;
    std::deque<std::pair<int, int>> temp_amount_values;
    std::pair<int, int> choice = std::make_pair(-1, -1);
    auto total_sum_or_amount = [&bin](bool flag = true) -> int {
        int sum = 0;
        if (flag) {
            std::for_each(bin.begin(), bin.end(),
                          [&sum](auto &elem) { sum += elem.second.get_cost() * elem.first; });
        } else {
            std::for_each(bin.begin(), bin.end(),
                          [&sum](auto &elem) { sum += elem.first; });
        }
        return sum;
    };
    do {
        std::cout << "Total amount of products: " << std::setw(5) << total_sum_or_amount(false) << std::endl;
        std::cout << "Total sum: " << std::setw(5) << total_sum_or_amount() << std::endl;
        show_products(temp_amount_values);
        choice = choose_product();
        if (choice != std::make_pair(-1, -1)) {
            bin.emplace_back(std::make_pair(choice.second, products[choice.first].second));
            temp_amount_values.emplace_back(std::make_pair(choice.first, choice.second));
        }
    } while (choice.first != -1 && choice.second != -1);
    if (!bin.empty()) {
        choice.first = customer->withdraw_sum(total_sum_or_amount());
        if (choice.first > 0) {
            for (const auto &item : temp_amount_values) {
                products[item.first].first -= item.second;
            }
            std::cout << "Thank you for purchase!!!" << std::endl;
        } else if (choice.first == -1) {
            std::cout << "Come next time!" << std::endl;
        } else {
            bin.clear();
            std::cout << "Not enough money!" << std::endl;
        }
        _getch();
    } else {
        std::cout << "Come next time!" << std::endl;
        _getch();
    }
    return bin;
}

std::pair<int, int> Shop::choose_product() {
    int choice = Common::input_choice("Choose product: ", 1, static_cast<const int &>(products.size())) - 1;
    if (choice == -22)
        return std::make_pair(-1, -1);
    std::string inputBuffer;
    std::cout << "Input amount of products: ";
    std::cin >> inputBuffer;
    try {
        if (!(std::regex_match(inputBuffer, std::regex("^[\\d]{1,}$")) &&
              std::stoi(inputBuffer) <= products[choice].first)) {
            do {
                std::cout << "Incorrect input. Number of products (" << products[choice].first << ")\n";
                std::cin >> inputBuffer;
            } while (!(std::regex_match(inputBuffer, std::regex("^[\\d]{1,}$")) &&
                       std::stoi(inputBuffer) <= products[choice].first));
        }
        return std::make_pair(choice, std::stoi(inputBuffer));
    }
    catch (std::exception const &e) {
        return std::make_pair(-1, -1);
    }
}

void Shop::show_products(std::deque<std::pair<int, int>> &temp_amount_values) {
    int i = 0;
    if (temp_amount_values.empty()) {
        for (const auto &product : products) {
            std::cout << ++i << ") " << product.second
                      << "\tAmount: " << std::left << std::setw(5) << product.first
                      << std::endl;
        }
    } else {
        auto func = [&temp_amount_values, this](int j) -> int {
            auto value_it = std::find_if(temp_amount_values.begin(), temp_amount_values.end(),
                                         [j](auto &pair) -> bool {
                                             return pair.first == j;
                                         });
            if (value_it == temp_amount_values.end() && value_it->first != temp_amount_values.back().first) {
                return this->products[j].first;
            } else {
                return products[j].first - value_it->second;
            }
        };
        for (int j = 0; j < products.size(); ++j) {
            std::cout << ++i << ") " << products[j].second
                      << "\tAmount: " << std::left << std::setw(5) << func(j)
                      << std::endl;
        }
    }
}

void Shop::show_staff() {
    if (staff.empty()) {
        std::cout << "No workers!" << std::endl;
        return;
    }
    int counter = 0;
    std::stack<Person> temp(staff);
    while (!temp.empty()) {
        std::cout << ++counter << ") " << temp.top();
        temp.pop();
    }
}

bool Shop::add_staff() {
    std::deque<std::pair<std::string, std::regex>> checks{
        std::make_pair("Input name (Format: Fffff): ", std::regex("^[A-Z][a-z]+$")),
        std::make_pair("Input year of birth (Format: ####): ", std::regex("^\\d{4}$")),
        std::make_pair("Input address (Format: City, str.|st. Street int-int): ",
                       std::regex("^[A-z0-9]+$")),
        std::make_pair("Input gender (Format: Male|Female): ", std::regex("^(Male|Female)$")),
        std::make_pair("Input nationality (Format: RU|ru|Ru): ", std::regex("^([A-z]{2,3})$"))
    };
    //
    std::deque<std::string> container;
    try {
        for (const auto &check : checks) {
            container.push_back(Common::check_input(check.first, check.second));
        }
        staff.push(Person(container[0],
                          std::stoi(container[1]),
                          container[2],
                          Gender(container[3] != "Male"),
                          container[4])
        );
        return true;
    }
    catch (...) {
        return false;
    }
}

bool Shop::remove_staff() {
    show_staff();
    int choice = Common::input_choice("Choose person to fire: ", 1, static_cast<const int &>(staff.size())) - 1;
    if (choice == -22) {
        return false;
    }
    std::stack<Person> temp;
    for (int i = 0; i < choice; ++i) {
        temp.push(staff.top());
        staff.pop();
    }
    if (!staff.empty()) staff.pop();
    while (!temp.empty()) {
        staff.push(temp.top());
        temp.pop();
    }
    return true;
}

void Shop::get_director_key_access(std::string key_value) {
    if (key_value != KEY_VALUE) return;
    int choice = 0;
    while (choice != -22) {
        choice = Common::input_choice("Staff manage menu\n\n1) Show staff\n2) Add worker\n3) Fire worker\n", 1, 3) - 1;
        if (choice == 2) {
            std::cout << (remove_staff() ? "Success" : "");
        } else if (choice == 1) {
            std::cout << (add_staff() ? "Success" : "");
        } else if (choice == 0){
            show_staff();
        }
        _getch();
        system("cls");
    }
}







