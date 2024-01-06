#pragma once
#include <Figure.hpp>

using namespace std;

class Romb : public Figure {
protected:
  vector<Point> _points;
  static double distance(Point p1, Point p2) {
	double x = p1.x - p2.x;
	double y = p1.y - p2.y;
	double dist = sqrt(x * x + y * y);
	return dist;
  };
  void Validate(vector<Point> points) {
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
  explicit Romb(vector<Point> p);
  explicit Romb(Point x, Point y, Point x1, Point y1);

  Romb &operator=(Romb &romb);
  bool operator==(Romb &romb) const;
  explicit operator double() const;

  Point center() const override;
  double area() const override;

  friend std::ostream &operator<<(ostream &os, const Romb &P) {
	for (int i = 0; i < P._points.size(); ++i) {
	  os << P._points[i].x << " " << P._points[i].y;
	  os << "\n";
	}
	return os;
  }

  friend std::istream &operator>>(std::istream &is, Romb &P) {
	double x, y;
	P._points.clear();
	for (int i = 0; i < 4; ++i) {
	  is >> x >> y;
	  P._points.push_back({x, y});
	}
	return is;
  }
};
