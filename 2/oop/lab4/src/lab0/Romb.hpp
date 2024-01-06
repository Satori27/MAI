#include "Romb.h"


template <class T> requires std::is_arithmetic_v<T>
Romb<T>::Romb(vector<Point<T>> p) { 
  Validate(p);
  _points = p; 
}


template <class T> requires std::is_arithmetic_v<T>
Romb<T>::Romb(Point<T> x, Point<T> y, Point<T> x1, Point<T> y1) {
  _points.push_back(x);
  _points.push_back(y);
  _points.push_back(x1);
  _points.push_back(y1);
  Validate(_points);
}


template <class T> requires std::is_arithmetic_v<T>
double Romb<T>::area() const {
  double diagonal1 = sqrt(pow(_points[1].x - _points[3].x, 2) +
						  pow(_points[1].y - _points[3].y, 2));
  double diagonal2 = sqrt(pow(_points[2].x - _points[4].x, 2) +
						  pow(_points[2].y - _points[4].y, 2));
  double area = (diagonal1 + diagonal2) / 2;
  return area;
}


template <class T> requires std::is_arithmetic_v<T>
Point<T> Romb<T>::center() const {
  double x_center =
	  (_points[0].x + _points[1].x + _points[2].x + _points[3].x) / 4;
  double y_center =
	  (_points[0].y + _points[1].y + _points[2].y + _points[3].y) / 4;
  return {x_center, y_center};
}


template <class T> requires std::is_arithmetic_v<T>
Romb<T>::operator double() const { return this->area(); }


template <class T> requires std::is_arithmetic_v<T>
Romb<T> &Romb<T>::operator=(Romb &romb) {
  this->_points.clear();
  for (int i = 0; i < romb._points.size(); ++i) {
	this->_points.push_back(romb._points[i]);
  }
  return *this;
}


template <class T> requires std::is_arithmetic_v<T>
bool Romb<T>::operator==(Romb &romb) const {
  for (int i = 0; i < romb._points.size(); ++i) {
	bool is_equal = this->_points[i].x != romb._points[i].x ||
					this->_points[i].y != romb._points[i].y;
	if (is_equal) {
	  return false;
	}
  }
  return true;
}