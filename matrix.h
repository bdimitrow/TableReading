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
/*! \class Matrix
 *  \brief A Matrix class using a singleton design pattern.
 *
 *  This class is used to initialize a matrix when opening a file. It uses a singleton pattern becasue
 *  after initializing a matrix the program is performing operations only on that particular matrix. That's
 *  why we need just one instance of class Matrix.
 */

/**
 * @param mat
 */
class Matrix {
public:
    /**
     * Method that servers as a constructor but it does not initialize a new object.
     * It is accessing the same instance of this class over and over.
     */
    static Matrix *getInstance() {
        if (!instance) {
            instance = new Matrix;
        }
        return instance;
    }
    /**
     * Method that is reading the information from a file and saves it into a matrix.
     * @param filename
     * @return
     */
    // saving the data from CSV file to a matrix of vectors
    matrix fileToMatrix(string filename);

    /**
     * Method displaying the matrix.
     */
    // displaying the matrix
    void printMatrix();

    /**
     * Method that is used to edit a cell in the matrix. It is accepting two integers(one for row and one for column).
     * The user is asked to enter the desired data type for the cell that is going to be editted. He can choose from:
     * integer, double, string or formula(= reference(to cell)/number - operator - reference(to cell)/number).
     * @param mat
     * @param row
     * @param col
     * @return editted matrix
     */
    // editting the matrix
    matrix edit(matrix &mat, int row, int col);

    /**
     * Method setting a matrix.
     * @param mat
     */
    // setting a matrix
    void setMat(const matrix &mat) { Matrix::mat = mat; }

private:
    matrix mat;
    /**
     * A default constructor. It is in the private section because the class uses singleton design pattern.
     */
    Matrix() {}
    /**
     * A parametrized constructor. It is in the private section because the class uses singleton design pattern.
     */
    Matrix(matrix m) : mat(m) {}
    /**
     * 
     */
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
