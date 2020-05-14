//
// Created by bozhidar on 5/7/20.
//

#ifndef TABLEREADING_READFILE_H
#define TABLEREADING_READFILE_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include "CellClass.h"
using namespace std;

template <typename T>
using vec = vector<Cell<T>>;
template <typename T>
using matrix = vector<vector<Cell<T>>>;

template <typename T>
vector<vector<Cell<T>>> fileToMatrix(string filename) {
    char delimiter = ',';
    vector<vector<Cell<T>>> result;
    string row, item;

    ifstream ins(filename);
    while(getline(ins, row)) {
        vector<Cell<T>> res;
        stringstream ss(row);
        while(getline(ss, item, delimiter)) {
            res.push_back(item);
        }
        result.push_back(res);
    }
    ins.close();
    return result;
}
// num , + 1
template <typename T>
void printMatrix(const matrix mat) {
    for(vec row : mat) {
        for(string s : row) {
            cout << setw(5) << left << s << "|";
        }
        cout << endl;
    }
}

template <typename T>
void editCell(matrix mat, int row, int col, string newValue) { // CELL
    if(row < mat.size() && col < mat[row].size()) {
        mat[row][col] = newValue;
    } else
        cerr << "Invalid table ranges!" << endl;
}



#endif //TABLEREADING_READFILE_H
