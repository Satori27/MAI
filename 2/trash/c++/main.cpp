#include <iostream>
#include <string>
using namespace std;

unsigned char* string_to_unsigned_char(string str) {
    unsigned char* ucharArray = reinterpret_cast<unsigned char*>(&str[0]);
    return ucharArray;
}

unsigned char* convertToTridecimal(int number) {
    std::string result = "";

    if (number == 0) {
        result = "0";
    }

    while (number > 0) {
        int remainder = number % 13;
        char digit;

        if (remainder < 10) {
            digit = remainder + '0';
        } else {
            digit = remainder - 10 + 'A';
        }

        result = digit + result;
        number /= 13;
    }
    unsigned char* ucharArray = reinterpret_cast<unsigned char*>(&result[0]);
    return ucharArray;
}

int main() {
    int number;
    std::cout << "Enter an integer: ";
    std::cin >> number;

    std::string tridecimal = convertToTridecimal(number);
    std::cout << "Tridecimal representation: " << tridecimal << std::endl;

    return 0;
}
