#include "Square.h"
template <class T> requires std::is_arithmetic_v<T>
Square<T>::Square(vector<Point<T>> p) { 
    Validate(p);
    _points = p; 
}


template <class T> requires std::is_arithmetic_v<T>
double Square<T>::area() const{
  double x = _points[0].x - _points[1].x;
  double sq = x * x;
  return sq;
}


template <class T> requires std::is_arithmetic_v<T>
Square<T>::Square(Point<T> p1, Point<T> p2) {
  vector<Point<T>> vec(2);
  vec[0]=p1;
  vec[1]=p2;
  Validate(vec);
  Validate(vec);
  _points.push_back(p1);
  _points.push_back(p2);
}


template <class T> requires std::is_arithmetic_v<T>
Point<T> Square<T>::center() const {
  T x_center = (_points[0].x + _points[1].x) / 2;
  T y_center = (_points[0].y + _points[1].y) / 2;
  return {x_center, y_center};
}


template <class T> requires std::is_arithmetic_v<T>
Square<T>::operator double() const { return this->area(); }


template <class T> requires std::is_arithmetic_v<T>
Square<T> &Square<T>::operator=(Square &sq) {
  this->_points.clear();
  for (int i = 0; i < sq._points.size(); ++i) {
	this->_points.push_back(sq._points[i]);
  }
  return *this;
}


template <class T> requires std::is_arithmetic_v<T>
bool Square<T>::operator==(Square &sq) const {
  for (int i = 0; i < sq._points.size(); ++i) {
	bool is_equal = this->_points[i].x != sq._points[i].x ||
					this->_points[i].y != sq._points[i].y;
	if (is_equal) {
	  return false;
	}
  }
  return true;
}