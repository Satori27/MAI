#include "Figure.hpp"
#include "Rectangle.h"
#include "Romb.h"
#include "Square.h"
#include <gtest/gtest.h>
using namespace std;

TEST(Square1, BasicAssertions) {
  // arrange
  Point a = {1, 2};
  Point b = {2, 1};
  Square sq(a, b);

  // act
  double func_res = sq.area();
  double true_res = 1.0;
  // assert
  EXPECT_EQ(func_res, true_res);
}

TEST(Square2, BasicAssertions) {
  // arrange
  Point a = {1, 2};
  Point b = {2, 1};
  Square sq(a, b);

  // act
  Point func_res = sq.center();
  bool res = (func_res.x == 1.5 && func_res.y == 1.5);

  // assert
  EXPECT_TRUE(res);
}

TEST(Square3, BasicAssertions) {
  // arrange

  Square sq({1, 2}, {2, 1});
  Square sq1({1, 3}, {3, 1});
  // act
  sq1 = sq;
  bool res = sq1 == sq;

  // assert
  EXPECT_TRUE(res);
}

TEST(Square4, BasicAssertions) {
  // arrange
  Point a = {1, 2};
  Point b = {2, 1};
  Square sq(a, b);

  // act
  double func_res = (double)sq;
  double true_res = 1.0;
  // assert
  EXPECT_EQ(func_res, true_res);
}

TEST(Rectangle1, BasicAssertions) {
  // arrange
  Point a = {0, 0};
  Point b = {1, 2};
  Rectangle rec(a, b);

  // act
  double func_res = rec.area();
  double true_res = 2.0;
  // assert
  EXPECT_EQ(func_res, true_res);
}

TEST(Rectangle2, BasicAssertions) {
  // arrange
  Point a = {0, 0};
  Point b = {2, 3};
  Rectangle req(a, b);

  // act
  Point func_res = req.center();
  bool res = (func_res.x == 1.0 && func_res.y == 1.5);

  // assert
  EXPECT_TRUE(res);
}

TEST(Rectangle3, BasicAssertions) {
  // arrange

  Rectangle req({0, 0}, {2, 4});
  Rectangle req1({0, 0}, {1, 5});
  // act
  req1 = req;
  bool res = req1 == req;

  // assert
  EXPECT_TRUE(res);
}

TEST(Rectangle4, BasicAssertions) {
  // arrange
  Point a = {0, 0};
  Point b = {2, 4};
  Rectangle req(a, b);

  // act
  double func_res = (double)req;
  double true_res = 8.0;
  // assert
  EXPECT_EQ(func_res, true_res);
}

TEST(Romb1, BasicAssertions) {
  // arrange
  Point a = {0, 1};
  Point b = {1, 0};
  Point c = {0, -1};
  Point d = {-1, 0};
  Romb romb(a, b, c, d);

  // act
  double func_res = romb.area();
  double true_res = 1.5;
  // assert
  EXPECT_EQ(func_res, true_res);
}

TEST(Romb2, BasicAssertions) {
  // arrange
  Point a = {0, 1};
  Point b = {1, 0};
  Point c = {0, -1};
  Point d = {-1, 0};
  Romb romb(a, b, c, d);

  // act
  Point func_res = romb.center();
  bool res = (func_res.x == 0.0 && func_res.y == 0.0);

  // assert
  EXPECT_TRUE(res);
}

TEST(Romb4, BasicAssertions) {
  // arrange
  Point a = {0, 1};
  Point b = {1, 0};
  Point c = {0, -1};
  Point d = {-1, 0};
  Romb romb(a, b, c, d);

  // act
  double func_res = (double)romb;
  double true_res = 1.5;
  // assert
  EXPECT_EQ(func_res, true_res);
}