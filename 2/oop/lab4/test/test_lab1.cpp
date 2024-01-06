#include "Figure.h"
#include "Rectangle.h"
#include "Romb.h"
#include "Square.h"
#include <gtest/gtest.h>
using namespace std;

TEST(Square1, BasicAssertions) {
  // arrange
  Point<double> a = {1, 2};
  Point<double> b = {2, 1};
  Square<double> sq(a, b);

  // act
  double func_res = sq.area();
  double true_res = 1.0;
  // assert
  EXPECT_EQ(func_res, true_res);
}

TEST(Square2, BasicAssertions) {
  // arrange
  Point<double> a = {1, 2};
  Point<double> b = {2, 1};
  Square<double> sq(a, b);

  // act
  Point<double> func_res = sq.center();
  bool res = (func_res.x == 1.5 && func_res.y == 1.5);

  // assert
  EXPECT_TRUE(res);
}


TEST(Square4, BasicAssertions) {
  // arrange
  Point<double> a = {1, 2};
  Point<double> b = {2, 1};
  Square<double> sq(a, b);

  // act
  double func_res = (double)sq;
  double true_res = 1.0;
  // assert
  EXPECT_EQ(func_res, true_res);
}

TEST(Rectangle1, BasicAssertions) {
  // arrange
  Point<double> a = {0, 0};
  Point<double> b = {1, 2};
  Rectangle<double> rec(a, b);

  // act
  double func_res = rec.area();
  double true_res = 2.0;
  // assert
  EXPECT_EQ(func_res, true_res);
}

TEST(Rectangle2, BasicAssertions) {
  // arrange
  Point<double> a = {0, 0};
  Point<double> b = {2, 3};
  Rectangle<double> req(a, b);

  // act
  Point<double> func_res = req.center();
  bool res = (func_res.x == 1.0 && func_res.y == 1.5);

  // assert
  EXPECT_TRUE(res);
}

TEST(Array1, BasicAssertions){
  // arrange
    Point<double> a = {0, 0};
  Point<double> b = {3, 3};
  Point<double> c = {2, 1};
  Array<std::shared_ptr<Figure<double>>> arr{
    std::make_shared<Square<double>>(a,b),
    std::make_shared<Rectangle<double>>(a,c)
  };

  // act
  double ans = arr.area_sum();
  double real_ans = 11;

  // assert 
  EXPECT_EQ(ans, real_ans);
}


TEST(Array2, BasicAssertions){
  // arrange
    Point<double> a = {0, 0};
  Point<double> b = {3, 3};
  Point<double> c = {2, 1};
  Array<std::shared_ptr<Figure<double>>> arr{
    std::make_shared<Square<double>>(a,b),
    std::make_shared<Rectangle<double>>(a,c)
  };

  // act
  arr.delete_el(0);
  double ans = arr.area_sum();
  double real_ans = 2;

  // assert 
  EXPECT_EQ(ans, real_ans);
}


TEST(Rectangle4, BasicAssertions) {
  // arrange
  Point<double> a = {0, 0};
  Point<double> b = {2, 4};
  Rectangle<double> req(a, b);

  // act
  double func_res = (double)req;
  double true_res = 8.0;
  // assert
  EXPECT_EQ(func_res, true_res);
}

TEST(Romb1, BasicAssertions) {
  // arrange
  Point<double> a = {0, 1};
  Point<double> b = {1, 0};
  Point<double> c = {0, -1};
  Point<double> d = {-1, 0};
  Romb<double> romb(a, b, c, d);

  // act
  double func_res = romb.area();
  double true_res = 1.5;
  // assert
  EXPECT_EQ(func_res, true_res);
}

TEST(Romb2, BasicAssertions) {
  // arrange
  Point<double> a = {0, 1};
  Point<double> b = {1, 0};
  Point<double> c = {0, -1};
  Point<double> d = {-1, 0};
  Romb<double> romb(a, b, c, d);

  // act
  Point<double> func_res = romb.center();
  bool res = (func_res.x == 0.0 && func_res.y == 0.0);

  // assert
  EXPECT_TRUE(res);
}

TEST(Romb4, BasicAssertions) {
  // arrange
  Point<double> a = {0, 1};
  Point<double> b = {1, 0};
  Point<double> c = {0, -1};
  Point<double> d = {-1, 0};
  Romb<double> romb(a, b, c, d);

  // act
  double func_res = (double)romb;
  double true_res = 1.5;
  // assert
  EXPECT_EQ(func_res, true_res);
}