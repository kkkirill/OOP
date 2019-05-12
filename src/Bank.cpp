#include "include/Bank.h"

std::vector<std::string> Bank::days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

Bank::Bank(std::string name, std::deque<Person> &staff,
           std::initializer_list<std::pair<weekday, std::pair<std::string, std::string>>> work_schedule) :
        name(std::move(name)), staff(staff), list_account_number(0) {
    schedule = std::move(convert(work_schedule));
}

std::deque<Person> &Bank::get_staff() {
    return staff;
}

std::map<weekday, std::pair<std::tm, std::tm>> Bank::get_schedule() {
    return schedule;
}

void Bank::set_staff(std::deque<Person> &staff) {
    this->staff = staff;
}

void Bank::set_schedule(std::initializer_list<std::pair<weekday, std::pair<std::string, std::string>>> schedule) {
    this->schedule = std::move(convert(schedule));
}

void Bank::register_account(Person *client) {
    accounts.emplace_back(new BankAccount(&name, list_account_number++, client));
    std::cout << "Sucessfull" << std::endl;
    _getch();
}

bool Bank::close_account(Person *client) {
    auto person_accounts = find_accounts(client);
    int choice = choose_account(person_accounts, "Choose which account you want close:\n");
    if (choice == -22) {
        return false;
    }
    auto it = accounts.begin();
    std::advance(it, choice);
    accounts.erase(it);
    return true;
}

bool Bank::put_in_account(Person *client, int sum) {
    auto person_accounts = find_accounts(client);
    int choice = choose_account(person_accounts, "Choose to which account you want put money:\n");
    if (choice == -22) {
        return false;
    }
    auto it = person_accounts.begin();
    std::advance(it, choice);
    return (*it)->put_sum(sum);
}

int Bank::withdraw_from_account(Person *client, int sum) {
    auto person_accounts = find_accounts(client);
    int choice = choose_account(person_accounts, "Choose from which account you want withdraw money:\n");
    if (choice == -22) {
        return 0;
    }
    auto it = person_accounts.begin();
    std::advance(it, choice);
    return (*it)->withdraw_sum(sum);
}

bool Bank::transfer(Person *client, int sum) {
    auto person_accounts = find_accounts(client);
    int choice = choose_account(person_accounts, "Choose from what account you want transfer:\n");
    if (choice == -21)
        return false;
    auto it = person_accounts.begin();
    std::advance(it, choice);
    int sum_buffer = (*it)->withdraw_sum(sum);
    std::string inputBuffer = input_account_number();
    BankAccount *dst_account = find_account(std::atoi(inputBuffer.c_str()));
    if (sum_buffer == 0) {
        std::cout << "Not enough funds on the account\n";
        return false;
    }
    if (dst_account == nullptr) {
        do {
            std::cout << "No such account\n";
            inputBuffer = input_account_number();
            dst_account = find_account(std::atoi(inputBuffer.c_str()));
        } while (dst_account == nullptr);
    }
    dst_account->put_sum(sum_buffer);
    return true;
}

int Bank::choose_account(std::list<BankAccount *> accounts, std::string text) {
    int counter = 0;
    for (auto account : accounts) {
        std::cout << ++counter << " )\n" << *account << std::endl;
    }
    return input_choice(text, 1, static_cast<const int &>(accounts.size())) - 1;
}

BankAccount *Bank::find_account(int number) {
    auto pred_function = [&number](BankAccount *account) { return account->get_number() == number; };
    auto it = std::find_if(accounts.begin(), accounts.end(), pred_function);
    if (it == accounts.end() && (*it)->get_number() != accounts.back()->get_number())
        return nullptr;
    return *it;
}

std::list<BankAccount *> Bank::find_accounts(Person *client) {
    std::list<BankAccount *> person_accounts;
    for (auto &account : accounts) {
        if (account->get_owner() == client) {
            person_accounts.push_back(account);
        }
    }
    return person_accounts;
}

int Bank::input_choice(const std::string &text, const int &left, const int &right, bool isRequired) {
    int c;
    std::cout << text;
    do {
        c = _getch() - 48;
        fflush(stdin);
    } while ((c < left || c > right) && (isRequired ? true : c != -21));
    std::cout << c << std::endl;
    system("cls");
    return c;
}

std::string Bank::input_account_number() {
    std::string inputBuffer;
    std::cout << "Input destination account number(5 numbers): ";
    std::cin >> inputBuffer;
    if (!std::regex_match(inputBuffer, std::regex("^[\\d]{5}$"))) {
        do {
            std::cout << "Incorrect input. Account number consist of 5 numbers\n";
            std::cin >> inputBuffer;
        } while (std::regex_match(inputBuffer, std::regex("^[\\d]{5}$")));
    }
    return inputBuffer;
}

void Bank::perform_services(Person *client) {
    int choice, temp;
    auto person_accounts = find_accounts(client);
    if (person_accounts.empty()) {
        if (input_choice("You don't have account. Do you want to create it? (1/0)\n", 0, 1, true)) {
            register_account(client);
        } else {
            return;
        }
    }
    do {
        system("cls");
        show_services();
        choice = input_choice("Choose service:\n", 1, 7) - 1;
        if (choice == 0) {
            show_account_status(client);
            _getch();
        } else if (choice == 1) {
            register_account(client);
        } else if (choice >= 2 && choice <= 4) {
            std::cout << "Input sum: ";
            do {
                std::cin.clear();
                std::cin.ignore(std::cin.rdbuf()->in_avail());
                std::cin >> temp;
            } while (!std::cin);
            if (choice == 3) {
                std::cout << "Withdrawn sum: " << withdraw_from_account(client, temp) << std::endl;
            } else if (choice == 2) {
                std::cout << (put_in_account(client, temp) ? "Done" : "Failed") << std::endl;
            } else {
                std::cout << (transfer(client, temp) ? "Done" : "Failed") << std::endl;
            }
            _getch();
        } else if (choice == 5) {
            close_account(client);
        } else if (choice == 6) {
            sort(client,
                 static_cast<bool>(input_choice("By decendance (1/0)\n", 0, 1, true)), static_cast<bool>(input_choice(
                         "By sum/By number (1/0)\n", 0, 1, true)));
            std::cout << "Sorted\n";
        }
    } while (choice != -22);
}

inline void Bank::show_services() {
    std::cout << "Services: " << std::endl
              << "1) Show accounts status" << std::endl
              << "2) Open account" << std::endl
              << "3) Put money in account" << std::endl
              << "4) Withdraw money from account" << std::endl
              << "5) Transfer money to another account" << std::endl
              << "6) Close account" << std::endl
              << "7) Sort accounts" << std::endl;
}

std::ostream &operator<<(std::ostream &os, const Bank &bank) {
    os << bank.name << std::endl;
    for (auto &item : bank.schedule) {
        os << Bank::days[item.first] << ": " << std::put_time(&item.second.first, "%H:%M") << ", "
           << std::put_time(&item.second.second, "%H:%M") << std::endl;
    }
    os << "Staff: " << std::endl;
    for (auto &item : bank.staff) {
        os << item;
    }
    return os;
}

void Bank::show_account_status(Person *client) {
    auto person_accounts = find_accounts(client);
    int counter = 0;
    for (auto &account : person_accounts) {
        std::cout << ++counter << " )\n" << *account;
    }
}

void Bank::sort(Person *client, bool by_decendance, bool by_sum) {
    for (auto j = 1U; j < accounts.size(); ++j) {
        auto itr = accounts.begin();
        std::advance(itr, j);
        const auto key = *itr;
        for (auto i = j; i > 0U; --i) {
            std::advance(itr, -1);
            if (by_decendance ?
            (by_sum ? key->get_current_sum() > (*itr)->get_current_sum() : key->get_number() > (*itr)->get_number()) :
            (by_sum ? key->get_current_sum() < (*itr)->get_current_sum() : key->get_number() < (*itr)->get_number())
                ) {
                const auto temp = *itr;
                *itr = key;
                *std::next(itr) = temp;
            } else {
                break;
            }
        }
    }
}

std::map<weekday, std::pair<std::tm, std::tm>>
Bank::convert(std::initializer_list<std::pair<weekday, std::pair<std::string, std::string>>> work_schedule) {
    std::tm t = {0}, t1 = {0};
    std::map<weekday, std::pair<std::tm, std::tm>> temp;
    for (auto &elem : work_schedule) {
        std::istringstream ss(elem.second.first + elem.second.second);
        ss >> std::get_time(&t, "%H:%M") >> std::get_time(&t1, "%H:%M");
        temp.emplace(elem.first, std::make_pair(t, t1));
    }
    return temp;
}

