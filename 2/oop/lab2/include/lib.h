#pragma once
#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

class Thirteen {
public:
  Thirteen();
  Thirteen(const size_t &size, unsigned char array);
  Thirteen(const std::initializer_list<unsigned char> &t);
  Thirteen(const string &str);
  Thirteen(const Thirteen &thirteen);
  Thirteen(Thirteen &&thirteen) noexcept;

  Thirteen operator+(const Thirteen &thirteen);
  Thirteen operator-(const Thirteen &thirteen);
  Thirteen operator*(const Thirteen &thirteen);
  Thirteen operator/(const Thirteen &thirteen);
  Thirteen &operator+=(const Thirteen &thirteen);
  Thirteen &operator-=(const Thirteen &thirteen);
  Thirteen &operator=(const Thirteen &thirteen);

  bool operator<(const Thirteen &thirteen);
  bool operator>(const Thirteen &thirteen);
  bool operator==(const Thirteen &thirteen);

  unsigned char *get_array();
  size_t get_size();

  ~Thirteen() noexcept;
  std::ostream & print(std::ostream &os);
  std::istream & get_in(std::istream &os, size_t n);


private:
  size_t _size;
  unsigned char *_array;
  void reverse_array(unsigned char* arr, int size);
  int thirteen_to_int(unsigned char *number, size_t n);
  string convert_to_thirteen(int number);
  void check_constructor(unsigned char* arr);
};