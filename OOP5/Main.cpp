#include "include/Shop.h"
#include <iostream>
#include <windows.h>

int main() {

    std::initializer_list <std::pair<weekday, std::pair<std::string, std::string>>> work_shedule{
            std::make_pair(weekday::Monday, std::make_pair("08:00", "22:00")),
            std::make_pair(weekday::Tuesday, std::make_pair("08:00", "22:00")),
            std::make_pair(weekday::Wednesday, std::make_pair("08:00", "21:00")),
            std::make_pair(weekday::Thursday, std::make_pair("08:00", "22:00")),
            std::make_pair(weekday::Friday, std::make_pair("09:00", "19:00")),
            std::make_pair(weekday::Saturday, std::make_pair("09:30", "19:00")),
            std::make_pair(weekday::Sunday, std::make_pair("11:00", "18:00")),
    };

    std::initializer_list<std::pair<int, Product>> products{
            std::make_pair(24, Product("Холодильник", Type::Technique, 200)),
            std::make_pair(10, Product("Oven", Type::Technique, 170)),
            std::make_pair(120, Product("Bread", Type::Food, 3)),
            std::make_pair(99, Product("Milk", Type::Food, 4)),
            std::make_pair(75, Product("Proposol", Type::Medicine, 10)),
            std::make_pair(25, Product("Bucket", Type::Household, 9)),
    };

    std::deque<Person> staff{
            Person("Kirill", 2000, "Minsk, Slobodskaya 157-128", Gender::MALE, "BY"),
            Person("Vitya", 1999, "Minsk, Dzyarzhinskogo 110-23", Gender::MALE, "BY"),
            Person("Olya", 1998, "Brest, Pushkina 24-2", Gender::FEMALE, "BY")
    };


    Bank alpha_bank("AplhaBank", staff, work_shedule);

    std::deque<Customer> clients{
            Customer(new Person("Egor", 2000, "Minsk, Kjsmonavtov 110-12", Gender::MALE, "BY"), &alpha_bank),
            Customer(new Person("Dasha", 1996, "Mogilev, Artileriyskaya 123-1", Gender::FEMALE, "BY"), &alpha_bank),
            Customer(new Person("Sergey", 1995, "Vitebskiy region, Orhsa, Stalina 23-2", Gender::MALE, "BY"), &alpha_bank),
            Customer(new Person("Natasha", 1990, "Minsk, Platonova 24-5", Gender::FEMALE, "BY"), &alpha_bank)
    };

    INPUT ip {
            ip.type = INPUT_KEYBOARD,
            ip.ki.wScan = 0,
            ip.ki.wVk = VK_RETURN,
            ip.ki.dwFlags = 0
    };
    ip.ki.time = 0;
    ip.ki.dwExtraInfo = 0;

    for (auto &client : clients) {
        SendInput(1, &ip, sizeof(INPUT));
        alpha_bank.register_account(const_cast<Person*>(client.get_person()));
        alpha_bank.put_in_account(const_cast<Person*>(client.get_person()), 2000);
    }
    system("cls");

    Shop shop(products, work_shedule, staff, "SUPER_SECRET_KEY");
    shop.buy_products(&clients[0]);
    alpha_bank.show_account_status(const_cast<Person*>(clients[0].get_person()));

    _getch();
    system("cls");
    shop.get_director_key_access("SUPER_SECRET_KEY");
    return 0;
}



