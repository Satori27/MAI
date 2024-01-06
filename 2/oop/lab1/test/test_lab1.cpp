#include "lib.h"
#include <gtest/gtest.h>
using namespace std;

TEST(TestClosetPairTonumFirst, BasicAssertions) {
  // arrange
  int number = 0;
  pair<int, int> true_answer = {0, 0};

  // act
  pair<int, int> answer_of_func = closest_pair_tonum(number);

  // assert
  EXPECT_EQ(answer_of_func, true_answer);
}

TEST(TestClosetPairTonumSecond, BasicAssertions) {
  // arrange
  int number = 50;
  pair<int, int> true_answer = {45, 36};

  // act
  pair<int, int> answer_of_func = closest_pair_tonum(number);

  // assert
  EXPECT_EQ(answer_of_func, true_answer);



  // arrange
  number = 30;
  true_answer = {29, 20};

  // act
  answer_of_func = closest_pair_tonum(number);

  // assert
  EXPECT_EQ(answer_of_func, true_answer);
}

TEST(TestClosetPairTonumThird, BasicAssertions) {
  // arrange
  int number = 10;
  pair<int, int> true_answer = {5, 4};

  // act
  pair<int, int> answer_of_func = closest_pair_tonum(number);

  // assert
  EXPECT_EQ(answer_of_func, true_answer);

  

  // arrange
  number = -50;
  true_answer = {0, 0};

  // act
  answer_of_func = closest_pair_tonum(number);

  // assert
  EXPECT_EQ(answer_of_func, true_answer);
}