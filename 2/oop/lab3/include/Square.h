#pragma once
#include "Figure.hpp"
#include <ostream>

using namespace std;


class Square : public Figure {
protected:
  vector<Point> _points;
    static void Validate(vector<Point> points) {
        if (points.size() != 2) {
            throw invalid_argument("Invalid number of points");
        }
        if(points[0].x==points[1].x || points[0].y==points[1].y){
            throw invalid_argument("Points can't be equal");
        }
        if(abs(points[0].x - points[1].x) != abs(points[0].y - points[1].y)){
            throw invalid_argument("It is rectangle, not square");
        }
    }

public:
  explicit Square(vector<Point> p); 
  explicit Square(Point p1, Point p2);

  Square &operator=(Square &sq);
  bool operator==(Square &sq) const;
  explicit operator double() const;

  Point center() const override;
  double area() const override;

  friend std::ostream &operator<<(ostream &os, const Square &P) {
	for (int i = 0; i < P._points.size(); ++i) {
	  os << P._points[i].x << " " << P._points[i].y;
	  os << "\n";
	}
	return os;
  }

  friend std::istream &operator>>(std::istream &is, Square &P) {
	double x, y;
  P._points.clear();
	for (int i = 0; i < 2; ++i) {
	  is >> x >> y;
	  P._points.push_back({x, y});
	}
  Validate(P._points);
	return is;
  }
};
