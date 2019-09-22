#ifndef LAB5_1_COMMON_H
#define LAB5_1_COMMON_H
#pragma once
#include <string>
#include <vector>
#include <conio.h>
#include <iostream>
#include <regex>

class Common {
public:
    static int input_choice(const std::string &text, const int &left, const int &right, bool isRequired = false);
    static std::vector<std::string> days;
    static std::string check_input(std::string massage, std::regex condition);
};


#endif //LAB5_1_COMMON_H
