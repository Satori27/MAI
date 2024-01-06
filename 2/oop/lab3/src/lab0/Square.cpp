#include "Square.h"

Square::Square(vector<Point> p) { 
    Validate(p);
    _points = p; 
}

Square::Square(Point p1, Point p2) {
  vector<Point> vec(2);
  vec[0]=p1;
  vec[1]=p2;
  Validate(vec);
  Validate(vec);
  _points.push_back(p1);
  _points.push_back(p2);
}

double Square::area() const {
  double x = _points[0].x - _points[1].x;
  double sq = x * x;
  return sq;
}

Point Square::center() const {
  double x_center = (_points[0].x + _points[1].x) / 2;
  double y_center = (_points[0].y + _points[1].y) / 2;
  return {x_center, y_center};
}

Square::operator double() const { return this->area(); }

Square &Square::operator=(Square &sq) {
  this->_points.clear();
  for (int i = 0; i < sq._points.size(); ++i) {
	this->_points.push_back(sq._points[i]);
  }
  return *this;
}

bool Square::operator==(Square &sq) const {
  for (int i = 0; i < sq._points.size(); ++i) {
	bool is_equal = this->_points[i].x != sq._points[i].x ||
					this->_points[i].y != sq._points[i].y;
	if (is_equal) {
	  return false;
	}
  }
  return true;
}

