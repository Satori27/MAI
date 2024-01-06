#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>

using namespace std;

struct Point {
    double x;
    double y;
    Point() = default;

    Point(double _x, double _y) : x(_x), y(_y) {}
};

class Figure {

public:
    Figure() = default;

    virtual Point center() const = 0;
    virtual double area() const = 0;

    ~Figure() = default;

};
