#include "../include/urlDecode.h"

#include <sstream>
#include <iostream>

// Функция для декодирования URL
std::string urlDecode(const std::string& str) {
    std::stringstream decoded;
    char ch;
    int i = 0;
    while (i < str.length()) {
        if (str[i] == '%' && i + 2 < str.length()) {
            int hexValue;
            std::istringstream hexStream(str.substr(i + 1, 2));
            if (hexStream >> std::hex >> hexValue) {
                ch = static_cast<char>(hexValue);
                decoded << ch;
                i += 3;
                continue;
            }
        }
        if (str[i] == '+') {
            decoded << ' ';
        } else {
            decoded << str[i];
        }
        i++;
    }
    return decoded.str();
}