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
#include "dataTypes.h"

using namespace std;

using vec = vector<string>;
using matrix = vector<vec>;

// saving the data from CSV file to a matrix of vectors
matrix fileToMatrix(string filename);

void printMatrix(const matrix &mat);

int numberOfRowsInFile(const matrix &mat);

int numberOfElementOnParticularRow(const matrix &mat, int rowN);

int maxElementPerRowWholeTable(const matrix &mat);

int maxWidthOfCell(const matrix &mat);

void editCell(matrix &mat, int row, int col, string newValue);


// saving the data from CSV file to a matrix of vecs
matrix fileToMatrix(string filename) {
    char delimiter = ',';
    matrix result;
    string row, item;

    ifstream ins(filename);
    while (getline(ins, row)) {
        vec Row;
        stringstream ss(row);
        while (getline(ss, item, delimiter)) {
            Row.push_back(item);
        }
        result.push_back(Row);
    }
    ins.close();
    return result;
}

void printMatrix(const matrix &mat) {
    int lenght = maxElementPerRowWholeTable(mat);
    int coppiedAlready = 0;
    for (vec row : mat) {
        cout << setw(maxWidthOfCell(mat));
        for (string s : row) {
            cout << setw(maxWidthOfCell(mat)) << s << "|";
            ++coppiedAlready;
        }
        while (coppiedAlready < lenght) {
            cout << setw(maxWidthOfCell(mat)) << "" << "|";
            coppiedAlready++;
        }
        cout << endl;
        coppiedAlready = 0;
    }
}


int numberOfRowsInFile(const matrix &mat) {
    int numOfRows = 0;
    for (vec row : mat) {
        ++numOfRows;
    }
    return numOfRows;
}

int numberOfElementOnParticularRow(const matrix &mat, int rowN) {
    int numOfElements = 0;
    int rowCurrent = 0;
    for (vec row : mat) {
        ++rowCurrent;
        if (rowCurrent == rowN) {
            for (string s : row) {
                ++numOfElements;
            }
        }
    }
    return numOfElements;
}

int maxElementPerRowWholeTable(const matrix &mat) {
    int maxElements = 0;
    int elementsCurrentRow = 0;
    for (vec row : mat) {
        for (string s : row) {
            ++elementsCurrentRow;
        }
        if (elementsCurrentRow > maxElements) {
            maxElements = elementsCurrentRow;
        }
        elementsCurrentRow = 0;
    }
    return maxElements;
}

int maxWidthOfCell(const matrix &mat) {
    int maxWidth = 0;
    int currentWidth = 0;
    for (vec row: mat) {
        for (string s : row) {
            currentWidth = s.length();
            if (currentWidth > maxWidth) {
                maxWidth = currentWidth;
            }
        }

    }
    return maxWidth;
}

void editCell(matrix &mat, int row, int col, string newValue) {
    if (row < mat.size() && col < mat[row].size()) {
        mat[row][col] = newValue;
    }
}

double addTwoCells(const matrix &mat) {
    int row1, col1, row2, col2;
    cout << "Enter row and col of the first cell: ";
    cin >> row1 >> col1;
    cout << "Enter row and col of the second cell: ";
    cin >> row2 >> col2;
    string cell1, cell2;
    for (int i = 0; i < mat.size(); ++i) {
        if (i == row1) {
            for (int j = 0; i < mat[i].size(); ++i) {
                if (j == col1) {
                    cell1 = mat[i][j];
                }
            }
        }
    }
    for (int i = 0; i < mat.size(); ++i) {
        if (i == row2) {
            for (int j = 0; i < mat[i].size(); ++i) {
                if (j == col2) {
                    cell2 = mat[i][j];
                }
            }
        }
    }
    return stringToNumber(cell1) + stringToNumber(cell2);
}


#endif //TABLEREADING_READFILE_H
