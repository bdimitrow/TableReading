//
// Created by bozhidar on 5/17/20.
//

#ifndef TABLEREADING_CELLSTRINGCLASS_H
#define TABLEREADING_CELLSTRINGCLASS_H

#include <iostream>
#include <cstring>

using namespace std;

class Cell {
public:
    Cell() = default;

    Cell(string _value) : value(_value) {}

    Cell(const Cell &other) {
        value = other.value;
    }

    Cell &operator=(const Cell &other) {
        if (this != &other) {
            value = other.value;
        }
        return *this;
    }

    string getValue() const { return value; }

    void setValue(string v) { value = v; }

private:
    string value;
};

#endif //TABLEREADING_CELLCLASS_H



#endif //TABLEREADING_CELLSTRINGCLASS_H
