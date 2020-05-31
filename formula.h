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
/*!
 * \class Formula
 * \brief The Formula class is used for editing a cell with a formula.
 *
 * This class is used to initialize a formula and to read(decipher) it. There are three types of formulas: <br>
 * 1. number - operator - number ( = 10 ^ 2 );
 * 2. reference to a cell - operator - number ( = R1C1 / 5 );<br>
 *    number - operator - reference to a cell ( = 5 * R1C1 );
 * 3. reference to a cell - operator - reference to a cell ( = R2C2 - R3C4 );
 *
 * @param string fomrula
 */
// class formula used for editing a cell with data of type formula
class Formula {
public:
    /**
     * A parametrized constructor.
     * @param form
     */
    Formula(string form) : formula(form) {}

    /**
     * Method calculating the value of formula with two references to a cell.
     * @param mat
     * @return double
     */
    // used to edit a cell with formula made of two cells
    double formulaWithTwoCells(const matrix &mat);
    /**
     * Method calculating the value of formula with two numbers.
     * @return double
     */
    // used to edit a cell with formula made of two numbers
    double formulaWithTwoNumbers();

    /**
     * Method calculating the value of formula with a number and a refenrence to a cell.
     * @param mat
     * @return
     */
    // used to edit a cell with formula made of a cell and a number
    double formulaWithNumberAndCell(const matrix &mat);

    /**
     * Getter for a formula.
     * @return formula
     */
    const string &getFormula() const;

    /**
     * Setter for a formula.
     * @param formula
     */
    void setFormula(const string &formula);

private:
    string formula;

    /**
     * This function is splitting the formula into two parts and the delimeter is the operator.
     * @param formula
     * @param firstPart
     * @param secondPart
     * @param two strings
     */
    // spliting the formula into two part(before the operator and after the operator)
    void splitFormula(const string &formula, string &firstPart, string &secondPart, int &p);

    /**
     * Checks whether the formula with two numbers is valid.
     * @return true or false
     */
    bool isValidFormulaWithTwoNumbers() const;

    /**
     * Checks whether the formula with a number and a reference to a cell is valid.
     * @return true or false
     */
    bool isValidFormulaWithNumberAndCell() const;

    /**
     * Returning the result from the formula when the reference is first in the formula.
     * @param mat
     * @param formula
     * @param firstPartOfFormula
     * @param secondPartOfFormula
     * @param pos
     * @return double
     */
    double resultWhenCellReferenceIsFirst(const matrix &mat, string formula, const string &firstPartOfFormula,
                                          const string &secondPartOfFormula, int pos);

    /**
     * Returning the result from the formula when the reference is second in the formula.
     * @param mat
     * @param formula
     * @param firstPartOfFormula
     * @param secondPartOfFormula
     * @param pos
     * @return double
     */
    double resultWhenCellReferenceIsSecond(const matrix &mat, string formula, const string &firstPartOfFormula,
                                           const string &secondPartOfFormula, int pos);
    /**
     * Accepts two integers(one for row and one for column) and extracts the value of the cell references with
     * these numbers.
     * @param mat
     * @param row
     * @param col
     * @return
     */
    // return the value of a cell
    double getTheValueOfCell(const matrix &mat, int row, int col);

    /**
     * Used to determine in which part of the formula is the reference to a cell.
     * @param str
     * @return true or false
     */
    // used to determine on which side of the operator is the cell in the formula
    bool foundInPart(const string &str);

};

#endif //TABLEREADING_FORMULA_H
