#include "lib.h"
#include <string>
#include <gtest/gtest.h>
using namespace std;

string convert_to_string(unsigned char* arr, size_t size){
  string str;
  for(size_t i=0; i<size; i++){
    if(arr[i]=='\0') break;
    str+= arr[i];
  }

  return str;
}


TEST(Thirteen1, BasicAssertions) {
  // arrange
  Thirteen thirteen;

  // act
  unsigned char* arr = thirteen.get_array();
  size_t size = thirteen.get_size();
  unsigned char* answer_of_func = new unsigned char[1];
  answer_of_func[0]= '0';

  // assert
  EXPECT_EQ(*answer_of_func, *arr);
}


TEST(Thirteen2, BasicAssertions) {
  // arrange
  Thirteen thirteen("AAA");

  // act
  unsigned char* arr = thirteen.get_array();
  size_t size = thirteen.get_size();
  string answer = convert_to_string(arr, size);
  string real_answer = "AAA";

  // assert
  EXPECT_EQ(real_answer, answer);
}


TEST(Thirteen3, BasicAssertions) {
  // arrange
  Thirteen thirteen {'B', 'B', 'B'};

  // act
  unsigned char* arr = thirteen.get_array();
  size_t size = thirteen.get_size();
  string answer = convert_to_string(arr, size);;
  string real_answer = "BBB";


  // assert
  EXPECT_EQ(real_answer, answer);
}

TEST(Thirteen4, BasicAssertions) {
  // arrange
  Thirteen first("BBB");
  Thirteen second(first);
  // act
  unsigned char* arr = second.get_array();
  size_t size = second.get_size();
  string answer = convert_to_string(arr, size);;
  string real_answer = "BBB";


  // assert
  EXPECT_EQ(real_answer, answer);
}

TEST(Thirteen5, BasicAssertions) {
  // arrange
  Thirteen first("BBB");
  Thirteen second(move(first));
  // act
  unsigned char* arr = second.get_array();
  size_t size = second.get_size();
  string answer = convert_to_string(arr, size);;
  string real_answer = "BBB";


  // assert
  EXPECT_EQ(real_answer, answer);
}

TEST(Thirteen6, BasicAssertions) {
  // arrange
  Thirteen first("B");
  Thirteen second("A");
  // act
  Thirteen sum(first+second);
  unsigned char* arr = sum.get_array();
  size_t size = sum.get_size();
  string answer = convert_to_string(arr, size);;
  string real_answer = "81";


  // assert
  EXPECT_EQ(real_answer, answer);
}


TEST(Thirteen7, BasicAssertions) {
  // arrange
  Thirteen first("B");
  Thirteen second("A");
  // act
  Thirteen sum = first-second;
  unsigned char* arr = sum.get_array();
  size_t size = sum.get_size();
  string answer = convert_to_string(arr, size);;
  string real_answer = "1";


  // assert
  EXPECT_EQ(real_answer, answer);
}

TEST(Thirteen8, BasicAssertions) {
  // arrange
  Thirteen first("B");
  Thirteen second("A");
  // act
  Thirteen sum = first*second;
  unsigned char* arr = sum.get_array();
  size_t size = sum.get_size();
  string answer = convert_to_string(arr, size);;
  string real_answer = "68";


  // assert
  EXPECT_EQ(real_answer, answer);
}

TEST(Thirteen9, BasicAssertions) {
  // arrange
  Thirteen first("B");
  Thirteen second("AA");
  // act
  bool answer = first<second;

  bool real_answer = true;


  // assert
  EXPECT_EQ(real_answer, answer);
}

TEST(Thirteen10, BasicAssertions) {
  // arrange
  Thirteen first("B");
  Thirteen second("AA");
  // act
  bool answer = first>second;

  bool real_answer = false;


  // assert
  EXPECT_EQ(real_answer, answer);
}

TEST(Thirteen11, BasicAssertions) {
  // arrange
  Thirteen first("A");
  Thirteen second("2");
  // act
  Thirteen sum = first*second;
  unsigned char* arr = sum.get_array();
  size_t size = sum.get_size();
  string answer = convert_to_string(arr, size);;
  string real_answer = "71";


  // assert
  EXPECT_EQ(real_answer, answer);
}

