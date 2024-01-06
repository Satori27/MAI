#include <iostream>
#include <boost/multiprecision/cpp_int.hpp>

// Функция для возведения числа в степень
std::string power(const std::string& base, int exponent) {
    namespace mp = boost::multiprecision;

    // Конвертирование исходной строки в тип cpp_int
    mp::cpp_int num(base);

    // Возведение числа в степень
    mp::cpp_int result = mp::pow(num, exponent);

    // Конвертирование результата обратно в строку
    std::string resultStr = result.str();

    return resultStr;
}

int main() {
    // Входные значения
    std::string base = "4";
    int exponent;
    std::cin>>exponent;

    // Возведение числа в степень
    std::string result = power(base, exponent);

    // Вывод результата
    std::cout << result << "\n";

    return 0;
}
