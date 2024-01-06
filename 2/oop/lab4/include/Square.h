#pragma once
#include "Figure.h"
#include <ostream>

using namespace std;

template <class T>
requires std::is_arithmetic_v<T>
class Square : public Figure<T> {
protected:
    vector<Point<T>> _points;
    static void Validate(vector<Point<T>> points) {
        if (points.size() != 2) {
            throw invalid_argument("Invalid number of points");
        }
        if(points[0].x==points[1].x || points[0].y==points[1].y){
            throw invalid_argument("Point<T>s can't be equal");
        }
        if(abs(points[0].x - points[1].x) != abs(points[0].y - points[1].y)){
            throw invalid_argument("It is rectangle, not square");
        }
    }

public:
  explicit Square(vector<Point<T>> p); 
  explicit Square(Point<T> p1, Point<T> p2);

  Square &operator=(Square &sq);
  bool operator==(Square &sq) const;
  explicit operator double() const;

  Point<T> center() const override;
  double area() const override;


  friend std::ostream &operator<<(ostream &os, const Square<T> &p){
    for (int i = 0; i < p._points.size(); ++i) {
      os << p._points[i].x << " " << p._points[i].y;
      os << "\n";
    }
    return os;
  }
  
  void print(std::ostream & os) override {
    os << *this;
  }

  friend std::istream &operator>>(std::istream &is, Square &p) {
	double x, y;
  p._points.clear();
	for (int i = 0; i < 2; ++i) {
	  is >> x >> y;
	  p._points.push_back({x, y});
	}
  Validate(p._points);
	return is;
  }
};


#include "../src/lab0/Square.hpp"
