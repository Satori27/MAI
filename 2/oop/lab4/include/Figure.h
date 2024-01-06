#pragma once

#include "My_Array.h"
#include "Point.h"

using namespace std;


template <class T>
class Figure {
public:

    virtual Point<T> center() const = 0;
    virtual double area() const = 0;
    friend std::ostream &operator<<(ostream &os, const Figure<T> &p);

    virtual void print(std::ostream & os) = 0;

    ~Figure() = default;

    protected: 
        vector<Point<T>> _points;
};
