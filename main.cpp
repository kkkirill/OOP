#include "include/Bank.h"

int main() {
    std::deque<Person> clients{
        Person("Egor", 2000, "Minsk, Kjsmonavtov 110-12", Gender::MALE, "BY"),
        Person("Dasha", 1996, "Mogilev, Artileriyskaya 123-1", Gender::FEMALE, "BY"),
        Person("Sergey", 1995, "Vitebskiy region, Orhsa, Stalina 23-2", Gender::MALE, "BY"),
        Person("Natasha", 1990, "Minsk, Platonova 24-5", Gender::FEMALE, "BY")
    };
    std::deque<std::deque<Person>> staff{
            std::deque<Person>{
                Person("Kirill", 2000, "Minsk, Slobodskaya 157-128", Gender::MALE, "BY"),
                Person("Vitya", 1999, "Minsk, Dzyarzhinskogo 110-23", Gender::MALE, "BY"),
                Person("Olya", 1998, "Brest, Pushkina 24-2", Gender::FEMALE, "BY")
            },
            std::deque<Person>{
                Person("Vanya", 1997, "Vitebsk, Yakuba Kolasa 112-51", Gender::MALE, "BY"),
                Person("Tanya", 1999, "Minsk region, Stolbtsy, Pervomayskaya 10-75", Gender::FEMALE, "BY"),
                Person("Petya", 1995, "Grodno, M. Tanka 91-13", Gender::MALE, "BY")
            }
    };
    std::initializer_list <std::pair<weekday, std::pair<std::string, std::string>>> work_shedule{
        std::make_pair(weekday::Monday, std::make_pair("08:00", "22:00")),
        std::make_pair(weekday::Tuesday, std::make_pair("08:00", "22:00")),
        std::make_pair(weekday::Wednesday, std::make_pair("08:00", "21:00")),
        std::make_pair(weekday::Thursday, std::make_pair("08:00", "22:00")),
        std::make_pair(weekday::Friday, std::make_pair("09:00", "19:00")),
        std::make_pair(weekday::Saturday, std::make_pair("09:30", "19:00")),
        std::make_pair(weekday::Sunday, std::make_pair("11:00", "18:00")),
    };

    Bank alpha_bank("AplhaBank", staff[0], work_shedule);
    //Bank belarus_bank("BelarusBank", staff[1], work_shedule);

    alpha_bank.perform_services(&clients[0]);

    return 0;
}
