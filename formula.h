//
// Created by bozhidar on 5/28/20.
//

#ifndef TABLEREADING_FORMULA_H
#define TABLEREADING_FORMULA_H

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
#include "matrix.h"

using namespace std;

using vec = vector<string>;
using matrix = vector<vec>;

// class formula used for editing a cell with data of type formula
class Formula {
public:
    Formula(string form) : formula(form) {}

    // used to edit a cell with formula made of two cells
    double formulaWithTwoCells(string formula, const matrix &mat);

    // used to edit a cell with formula made of two numbers
    double formulaWithTwoNumbers(string formula);

    // used to edit a cell with formula made of a cell and a number
    double formulaWithNumberAndCell(string formula, const matrix &mat);

private:
    string formula;

    // spliting the formula into two part(before the operator and after the operator)
    void splitFormula(const string &formula, string &firstPart, string &secondPart, int &p);

    // throws an exception when the formula in incorrect
    void isValidFormulaWithTwoNumbers(const string &formula);

    // throws an exception when the formula is incorrect
    void isValidFormulaWithNumberAndCell(const string &formula);

    // return the value of a cell
    double getTheValueOfCell(const matrix &mat, int row, int col);

    // used to determine on which side of the operator is the cell in the formula
    bool foundInPart(const string &str);

    // using regex to extract numbers from string(the numbers are saved as strings into a vector)
    void extractNumbers(vector<string> &rowsCols, const string &str);

    // parsing vector<string> to vector<int>
    vector<int> parseStringVecToIntVec(vector<string> rowsCols);
};

#endif //TABLEREADING_FORMULA_H
