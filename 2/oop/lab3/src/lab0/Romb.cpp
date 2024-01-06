#include <Romb.h>

Romb::Romb(vector<Point> p) { 
  Validate(p);
  _points = p; 
}
Romb::Romb(Point x, Point y, Point x1, Point y1) {
  _points.push_back(x);
  _points.push_back(y);
  _points.push_back(x1);
  _points.push_back(y1);
  Validate(_points);
}

double Romb::area() const {
  double diagonal1 = sqrt(pow(_points[1].x - _points[3].x, 2) +
						  pow(_points[1].y - _points[3].y, 2));
  double diagonal2 = sqrt(pow(_points[2].x - _points[4].x, 2) +
						  pow(_points[2].y - _points[4].y, 2));
  double area = (diagonal1 + diagonal2) / 2;
  return area;
}

Point Romb::center() const {
  double x_center =
	  (_points[0].x + _points[1].x + _points[2].x + _points[3].x) / 4;
  double y_center =
	  (_points[0].y + _points[1].y + _points[2].y + _points[3].y) / 4;
  return {x_center, y_center};
}

Romb::operator double() const { return this->area(); }

Romb &Romb::operator=(Romb &romb) {
  this->_points.clear();
  for (int i = 0; i < romb._points.size(); ++i) {
	this->_points.push_back(romb._points[i]);
  }
  return *this;
}

bool Romb::operator==(Romb &romb) const {
  for (int i = 0; i < romb._points.size(); ++i) {
	bool is_equal = this->_points[i].x != romb._points[i].x ||
					this->_points[i].y != romb._points[i].y;
	if (is_equal) {
	  return false;
	}
  }
  return true;
}