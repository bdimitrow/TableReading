//
// Created by bozhidar on 5/7/20.
//

#ifndef TABLEREADING_CELLCLASS_H
#define TABLEREADING_CELLCLASS_H

#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

template <class T>
class Cell {
public:
    Cell() = default;
    Cell(T _value) : value(_value) {}
    Cell(const Cell& other) {
        value = other.value;
    }
    Cell &operator=(const Cell& other) {
        if(this != &other) {
            value = other.value;
        }
        return *this;
    }
    T getValue() const { return value; }

    void setValue(T v) { value = v; }
private:
    T value;
};

#endif //TABLEREADING_CELLCLASS_H
