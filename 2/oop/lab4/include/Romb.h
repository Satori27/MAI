#pragma once
#include "Figure.h"

using namespace std;

template <class T>
requires std::is_arithmetic_v<T>
class Romb : public Figure<T> {
protected:
  vector<Point<T>> _points;

  static double distance(Point<T> p1, Point<T> p2) {
    double x = p1.x - p2.x;
    double y = p1.y - p2.y;
    double dist = sqrt(x * x + y * y);
    return dist;
  };

  void Validate(vector<Point<T>> points) {
      double ab = distance(points[0], points[1]);
      double bc = distance(points[1], points[2]);
      double cd = distance(points[2], points[3]);
      double da = distance(points[3], points[0]);

      bool equal_side = (ab == bc) && (bc == cd) && (cd == da);
      if (!equal_side) {
        throw invalid_argument("Sides must be equals");
    }

    Point ab_vector{points[0].x - points[2].x, points[0].y - points[2].y};
    Point cd_vector{points[1].x - points[3].x, points[1].y - points[3].y};
    double scalar = ab_vector.x * cd_vector.x + ab_vector.y * cd_vector.y;
    if (scalar != 0) {
      cout << scalar << "\n";
      throw invalid_argument("Diagonals must be perpendicular");
    }
  }


public:
  explicit Romb(vector<Point<T>> p);
  explicit Romb(Point<T> x, Point<T> y, Point<T> x1, Point<T> y1);

  Romb &operator=(Romb &romb);
  bool operator==(Romb &romb) const;
  explicit operator double() const;

  Point<T> center() const override;
  double area() const override;

  friend std::ostream &operator<<(ostream &os, const Romb &p) {
	for (int i = 0; i < p._points.size(); ++i) {
	  os << p._points[i].x << " " << p._points[i].y;
	  os << "\n";
	}
	return os;
  }
  void print(std::ostream & os) override {
    os << *this;
  }

  friend std::istream &operator>>(std::istream &is, Romb &p) {
	double x, y;
	p._points.clear();
	for (int i = 0; i < 4; ++i) {
	  is >> x >> y;
	  p._points.push_back({x, y});
	}
	return is;
  }
};

#include "../src/lab0/Romb.hpp"