//
// Created by bozhidar on 5/9/20.
//

#ifndef TABLEREADING_ROWCLASS_H
#define TABLEREADING_ROWCLASS_H

#include <string>
#include "CellClass.h"
using namespace std;

class Row{
public:
    Row() : numberOfElementsPerRow(0), cells(nullptr) {}
    Row(Cell* _cells, int _numberOfElementsPerRow) : cells(nullptr), numberOfElementsPerRow(_numberOfElementsPerRow) {
        setCells(_cells, numberOfElementsPerRow);
    }
    Row(const Row& other) : numberOfElementsPerRow(other.numberOfElementsPerRow) {
        setCells(other.cells, other.numberOfElementsPerRow);
    }
    Row& operator=(const Row& other){
        if(this != &other){
            numberOfElementsPerRow = other.numberOfElementsPerRow;
            setCells(other.cells, other.numberOfElementsPerRow);
        }
    }
    ~Row() { delete[] cells; }

    void setNumberOfElementsPerRow(int num) { numberOfElementsPerRow = num; }
    void setCells(Cell* _cells, int _numberOfElementsPerRow) {
        delete[] cells;
        cells = new (nothrow) Cell[_numberOfElementsPerRow];

        for(int i = 0; i < _numberOfElementsPerRow; ++i) {
            cells = &_cells[i];
        }
        numberOfElementsPerRow = _numberOfElementsPerRow;
    }

    Cell getCellAt(Cell* cells, int index) const { return cells[index]; }
    int getNumberOfElementsPerRow() const { return numberOfElementsPerRow; }

private:
    int numberOfElementsPerRow;
    template<typename T>
    Cell *cells;
};

#endif //TABLEREADING_ROWCLASS_H
