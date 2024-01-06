// Copyright 2023 SomeName
#include "lib.h"

using namespace std;

void Thirteen::reverse_array(unsigned char * arr, int size) {
    int start = 0;
    int end = size - 1;

    while (start < end) {
        unsigned char temp = arr[start];
        arr[start] = arr[end];
        arr[end] = temp;

        start++;
        end--;
    }
}

void Thirteen::check_constructor(unsigned char * arr) {
    for (int i = 0; i < _size; ++i) {
        if (arr[i] > 'C') {
            throw std::logic_error("It is not thirteen!");
        }
    }
}

int Thirteen::thirteen_to_int(unsigned char * number, size_t size) {
    reverse_array(number, size);

    if (number == nullptr) {
        return 0;
    }

    char * to_char = reinterpret_cast < char * > (number);
    int to_int = stoi(to_char, nullptr, 13);
    reverse_array(number, size);
    return to_int;
}

string Thirteen::convert_to_thirteen(int number) {
    string result = "";

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
    reverse(result.begin(), result.end());
    return result;
}

Thirteen::Thirteen(): _size(1), _array(0) {}

Thirteen::Thirteen(const size_t & size, unsigned char array) {
    _array = new unsigned char[size];

    for (size_t i = 0; i < size; ++i) {
        _array[i] = array;
    }

    _size = size;
}

Thirteen::Thirteen(const std::initializer_list<unsigned char> &in_list)
{
    _array = new unsigned char[in_list.size()-1];
    size_t i{0};
    for (unsigned char c : in_list){
        _array[i] = c;
        ++i;
    }
    _size = in_list.size();
}

Thirteen::Thirteen(const string & str) {
    if (str == "0") {
        _array = new unsigned char[0];
        _array[0] = '0';
        _size = 1;
        return;
    }

    _size = str.size();
    _array = new unsigned char[str.size()];
    size_t i = 0;

    for (; i < _size; ++i){
        _array[i] = str[i];
    }

    check_constructor(_array);
}

Thirteen::Thirteen(const Thirteen & thirteen) {
    _size = thirteen._size;
    _array = new unsigned char[_size];

    for (size_t i {0}; i < _size; ++i) {
        _array[i] = thirteen._array[i];
    }
    check_constructor(_array);
}

Thirteen::Thirteen(Thirteen && thirteen) noexcept {
    _size = thirteen._size;
    _array = thirteen._array;

    check_constructor(_array);

    thirteen._size = 0;
    thirteen._array = nullptr;
}

Thirteen Thirteen::operator + (const Thirteen & thirteen) {
    int first_num = thirteen_to_int(_array, _size);
    int second_num = thirteen_to_int(thirteen._array, thirteen._size);

    int sum = first_num + second_num;
    Thirteen result(convert_to_thirteen(sum));
    return result;
}

Thirteen Thirteen::operator - (const Thirteen & thirteen) {
    int first_num = thirteen_to_int(_array, _size);
    int second_num = thirteen_to_int(thirteen._array, thirteen._size);

    int diff = first_num - second_num;

    if (diff < 0) {
        throw std::logic_error("Can't be negative");
    }

    Thirteen result(convert_to_thirteen(diff));
    return result;
}

Thirteen Thirteen::operator * (const Thirteen & thirteen) {
    int first_num = thirteen_to_int(_array, _size);
    int second_num = thirteen_to_int(thirteen._array, thirteen._size);

    int res = first_num * second_num;
    Thirteen result(convert_to_thirteen(res));
    return result;
}

Thirteen Thirteen::operator / (const Thirteen & thirteen) {
    if (sizeof(thirteen._array) == 0 && _array[0] == 0) {
        throw std::logic_error("Сan't divide by zero");
    }

    int first_num = thirteen_to_int(_array, _size);
    int second_num = thirteen_to_int(thirteen._array, thirteen._size);

    int res = first_num * second_num;
    Thirteen result(convert_to_thirteen(res));
    return result;
}

Thirteen & Thirteen::operator += (const Thirteen & thirteen) {
    Thirteen new_thirteen = *this + thirteen;
    *this = new_thirteen;
    return *this;
}

Thirteen & Thirteen::operator -= (const Thirteen & thirteen) {
    Thirteen new_thirteen = *this - thirteen;
    *this = new_thirteen;
    return *this;
}

Thirteen & Thirteen::operator = (const Thirteen & thirteen) {
    _size = thirteen._size;
    _array = new unsigned char[_size];

    for (size_t i {0}; i < _size; ++i) {
        _array[i] = thirteen._array[i];
    }

    return * this;
}

bool Thirteen::operator < (const Thirteen & thirteen) {
    int first_num = thirteen_to_int(_array, _size);
    int second_num = thirteen_to_int(thirteen._array, thirteen._size);

    if (first_num < second_num) {
        return true;
    }
    return false;
}

bool Thirteen::operator > (const Thirteen & thirteen) {
    int first_num = thirteen_to_int(_array, _size);
    int second_num = thirteen_to_int(thirteen._array, thirteen._size);

    if (first_num > second_num) {
        return true;
    }
    return false;
}

bool Thirteen::operator == (const Thirteen & thirteen) {
    int first_num = thirteen_to_int(_array, _size);
    int second_num = thirteen_to_int(thirteen._array, thirteen._size);

    if (first_num == second_num) {
        return true;
    }
    return false;
}

Thirteen::~Thirteen() noexcept {
    if (_size > 0) {
        _size = 0;
        delete[] _array;
        _array = nullptr;
    }
}

unsigned char * Thirteen::get_array() {
    unsigned char * new_arr = new unsigned char[_size];
    if (_array == nullptr) {
        new_arr[0] = '0';
        return new_arr;
    }

    for (int i = 0; i < sizeof(_array) - 1; ++i) {
        new_arr[i] = _array[i];
    }

    return new_arr;
}

std::ostream & Thirteen::print(std::ostream & os) {
    if (_array == nullptr) {
        os << '0';
        return os;
    }
    for (size_t i = 0; i < _size; ++i)
        os << _array[i];
    os << "\n";
    return os;
}

std::istream & Thirteen::get_in(std::istream & os, size_t n) {
    _size = n;
    for (size_t i = 0; i < _size; ++i)
        os >> _array[i];
    return os;
}


size_t Thirteen::get_size() {
    return _size;
}