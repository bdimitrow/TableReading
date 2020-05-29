#ifndef TABLEREADING_MATRIX_H
#define TABLEREADING_MATRIX_H

#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
#include <exception>
#include <regex>
#include <cmath>
#include <string>
#include "formula.h"

using namespace std;

using vec = vector<string>;
using matrix = vector<vec>;

class Matrix {
public:
    static Matrix *getInstance() {
        if (!instance) {
            instance = new Matrix;
        }
        return instance;
    }

    Matrix(matrix m) : mat(m) {}

    // saving the data from CSV file to a matrix of vectors
    matrix fileToMatrix(string filename);

    // displaying the matrix
    void printMatrix();

    // editting the matrix
    matrix edit(matrix &mat, int row, int col);

private:
    matrix mat;

    // Signleton pattern
    Matrix() {}

    static Matrix *instance;

    // finding the max number of elements on row (from the whole matrix)
    int maxElementPerRowWholeTable();

    // finds the lenght of the longest cell
    int maxWidthOfCell();

    // used when editing cell with data of type int
    void editInteger(matrix &mat, int rol, int col);

    // used when editing cell with data of type double
    void editDouble(matrix &mat, int rol, int col);

    // used when editing cell with data of type string
    void editString(matrix &mat, int rol, int col);
};

#endif //TABLEREADING_MATRIX_H
