#pragma once
#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <assert.h>
#include <concepts>
#include <memory>
#include <cstddef>
#include <type_traits>

using namespace std;


template <class T>
concept Arrayable = std::is_default_constructible<T>::value;
template <Arrayable T>
class Array{
public:
    Array(): _size(0), _array{nullptr}{}
    Array(const initializer_list<T> &t){
        _array = std::shared_ptr<T[]>(new T[t.size()]);
        size_t i{0};
        for(auto &c: t){
            _array[i++]=c;
        _size = t.size();
        }
    }

    Array(const Array &other){
        _size = other._size;
        _array = std::shared_ptr<T>(new T[_size]);
        for(size_t i=0; i<_size;++i){
            _array[i] = other._array[i];
        }
    }

    Array(Array &&other) noexcept
    {
        std::cout << "Move constructor" << std::endl;
        _size = other._size;
        _array = other._array;

        other._size = 0;
        other._array = nullptr;
    }

    T& operator[](size_t index){
        assert(index<_size);
        return _array[index];
    }

    void print_center(){
        if(_size==0){
            throw invalid_argument("Array is empty!");
        }
        for(size_t i=0;i<_size;++i){
            auto p = _array[i]->center();
            cout<<i+1 <<": "<< p.x << " "<< p.y<<endl;
        }
    }

    void print_coordinates(){
        if(_size==0){
            throw invalid_argument("Array is empty!");
        }
        for(size_t i=0;i<_size;++i){
            _array[i]->print(std::cout);
        }
    }

    void print_square(){
        if(_size==0){
            throw invalid_argument("Array is empty!");
        }
        for(size_t i=0;i<_size;++i){
            double sq = _array[i]->area();
            cout<< sq<< endl;
        }
    }

    double area_sum(){
        if(_size==0){
            throw invalid_argument("Array is empty!");
        }
        double sum;
        for(size_t i=0;i<_size;++i){
            sum+=_array[i]->area();
        }
        return sum;
    }

    void delete_el(size_t num){
        if(num>_size|| _size == 0){
            throw invalid_argument("Invalid argument or array is empty");
        }
        size_t array_it=0;
        shared_ptr<T[]> new_array(new T[_size-1]);
        for(size_t i=0;i<_size;++i){
            if(i==num){
                continue;
            }
            new_array[array_it] = _array[i];
            ++array_it;
        }
        --_size;
        _array = new_array;

    }

    size_t size() const{
        return _size;
    }

private:
    size_t _size;
    std:: shared_ptr<T[]> _array;
};
