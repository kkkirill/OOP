#include "../include/Common.h"

std::vector<std::string> Common::days = {"Monday", "Tuesday", "Wednesday", "Thursday", "Friday", "Saturday", "Sunday"};

int Common::input_choice(const std::string &text, const int &left, const int &right, bool isRequired) {
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

std::string Common::check_input(std::string massage, std::regex condition) {
    std::string inputBuffer;
    inputBuffer.reserve(70);
    std::cout << massage;
    do {
        inputBuffer.clear();
        std::cin >> inputBuffer;
        std::cout << inputBuffer << "\t" << bool(std::regex_match(inputBuffer, condition)) << std::endl;
    } while(!std::regex_match(inputBuffer, condition));
    return inputBuffer;
}
