#ifndef TABLEREADING_READFILE_H
#define TABLEREADING_READFILE_H

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
#include "dataTypes.h"

using namespace std;

using vec = vector<string>;
using matrix = vector<vec>;

class Matrix {
public:
    Matrix() {}

    // saving the data from CSV file to a matrix of vectors
    matrix fileToMatrix(string filename);

    // displaying the matrix
    void printMatrix(const matrix &mat);

    // editting the matrix
    matrix edit(matrix &mat, int row, int col);

private:
    // finding the max number of elements on row (from the whole matrix)
    int maxElementPerRowWholeTable(const matrix &mat);

    // finds the lenght of the longest cell
    int maxWidthOfCell(const matrix &mat);

    // used when editing cell with data of type int
    void editInteger(matrix &mat, int rol, int col);

    // used when editing cell with data of type double
    void editDouble(matrix &mat, int rol, int col);

    // used when editing cell with data of type string
    void editString(matrix &mat, int rol, int col);
};

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

matrix Matrix::fileToMatrix(string filename) {
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

void Matrix::printMatrix(const matrix &mat) {
    int lenght = maxElementPerRowWholeTable(mat);
    int coppiedAlready = 0;
    for (vec row : mat) {
        cout << setw(maxWidthOfCell(mat));
        for (string s : row) {
            cout << setw(maxWidthOfCell(mat)) << s << "|";
            ++coppiedAlready;
        }
        // adding '|' whether the row is shorter
        while (coppiedAlready < lenght) {
            cout << setw(maxWidthOfCell(mat)) << "" << "|";
            coppiedAlready++;
        }
        cout << endl;
        coppiedAlready = 0;
    }
}

int Matrix::maxElementPerRowWholeTable(const matrix &mat) {
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

int Matrix::maxWidthOfCell(const matrix &mat) {
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

void Matrix::editInteger(matrix &mat, int row, int col) {
    string input;
    cout << "Enter an integer: ";
    cin.ignore();
    getline(cin, input);
    // checking whether the input is an int
    if (isInteger(input)) {
        if (row < mat.size() && col < mat[row].size()) {
            mat[row][col] = input;
        }
    } else {
        throw invalid_argument("ERROR! Unknown data type!");
    }
}

void Matrix::editDouble(matrix &mat, int row, int col) {
    string input;
    cout << "Enter a double: ";
    cin.ignore();
    getline(cin, input);
    // checking whether the input is a double
    if (isDouble(input)) {
        if (row < mat.size() && col < mat[row].size()) {
            mat[row][col] = input;
        }
    } else {
        throw invalid_argument("ERROR! Unknown data type!");
    }
}

void Matrix::editString(matrix &mat, int row, int col) {
    string input;
    cout << "Enter a string: ";
    cin.ignore();
    getline(cin, input);
    // adding qoutes to the input
    string newValue = "\"" + input + "\"";
    if (row < mat.size() && col < mat[row].size()) {
        mat[row][col] = newValue;
    }
}

matrix Matrix::edit(matrix &mat, int row, int col) {
    cout << "What type of data would you like to insert?" << endl;
    cout << "1. Integer" << endl;
    cout << "2. Double" << endl;
    cout << "3. String" << endl;
    cout << "4. Formula" << endl;
    int choice;
    do {
        cout << "Choose an action: ";
        if (!(cin >> choice)) {
            cout << "Invalid choice! Please enter an integer! " << endl;
            cin.clear();                            // reset any error flags
            cin.ignore(10000, '\n');                // ignore any characters in the input buffer
        } else if (choice == 1 || choice == 2 || choice == 3 || choice == 4) {
            switch (choice) {
                case 1: {
                    editInteger(mat, row, col);
                    return mat;
                }
                case 2: {
                    editDouble(mat, row, col);
                    return mat;
                }
                case 3: {
                    editString(mat, row, col);
                    return mat;
                }
                case 4:
                    string input;
                    cout << "Enter a formula: ";
                    cin.ignore();
                    getline(cin, input);
                    double newValue = 0;
                    int Rcount = 0, Ccount = 0;
                    for (int i = 0; i < input.length(); ++i) {
                        if (input.at(i) == 'R' || input.at(i) == 'r') Rcount++;
                        if (input.at(i) == 'C' || input.at(i) == 'c') Ccount++;
                    }
                    if (Rcount == 2 && Ccount == 2) {
                        Formula formula(input);
                        newValue = formula.formulaWithTwoCells(input, mat);
                    } else if (Rcount == 0 && Ccount == 0) {
                        Formula formula(input);
                        newValue = formula.formulaWithTwoNumbers(input);
                    } else if (Rcount == 1 && Ccount == 1) {
                        Formula formula(input);
                        newValue = formula.formulaWithNumberAndCell(input, mat);
                    } else if (Rcount != Ccount) {
                        throw invalid_argument("ERROR! Wrong formula!");
                    }
                    if (row < mat.size() && col < mat[row].size()) {
                        string value;
                        if (ceil(newValue) == floor(newValue)) {
                            int number;
                            number = static_cast<int>(newValue);
                            value = to_string(number);
                        } else {
                            value = to_string(newValue);
                        }
                        mat[row][col] = value;
                    } else if (row > mat.size() || col > mat[row].size()) {
                        throw invalid_argument("You are trying to edit a cell that is beyond the ranges of the table");
                    }
                    return mat;
                    break;
            }
        } else {
            cout << "Invalid choice!" << endl;
        }
    } while (true);
}

double Formula::formulaWithTwoNumbers(string formula) {
    formula.erase(0, 1);  //removing '=' from the formula;
    isValidFormulaWithTwoNumbers(formula);
    string firstPartOfFormula, secondPartOfFormula;
    int pos;
    splitFormula(formula, firstPartOfFormula, secondPartOfFormula, pos);
    double firstNumber = stod(firstPartOfFormula);
    double secondNumber = stod(secondPartOfFormula);
    if (formula.at(pos) == '+') {
        return firstNumber + secondNumber;
    } else if (formula.at(pos) == '-') {
        return firstNumber - secondNumber;
    } else if (formula.at(pos) == '*') {
        return firstNumber * secondNumber;
    } else if (formula.at(pos) == '/') {
        if (secondNumber == 0) {
            throw domain_error("ERROR! Can not divide by 0!");
        } else {
            return firstNumber / secondNumber;
        }
    } else if (formula.at(pos) == '^') {
        return pow(firstNumber, secondNumber);
    }
}

double Formula::formulaWithTwoCells(string formula, const matrix &mat) {
    vector<string> rowsColsAsStrings;
    extractNumbers(rowsColsAsStrings, formula);
    vector<int> numbersRowsCols = parseStringVecToIntVec(rowsColsAsStrings);
    double firstCell = getTheValueOfCell(mat, numbersRowsCols.at(0) - 1, numbersRowsCols.at(1) - 1);
    double secondCell = getTheValueOfCell(mat, numbersRowsCols.at(2) - 1, numbersRowsCols.at(3) - 1);
    for (int i = 0; i < formula.length(); ++i) {
        if (formula.at(i) == '+') {
            return firstCell + secondCell;
        } else if (formula.at(i) == '-') {
            return firstCell - secondCell;
        } else if (formula.at(i) == '*') {
            return firstCell * secondCell;
        } else if (formula.at(i) == '/') {
            if (secondCell == 0) {
                throw domain_error("ERROR! Can not divide by 0!");
            } else {
                return firstCell / secondCell;
            }
        } else if (formula.at(i) == '^') {
            return pow(firstCell, secondCell);
        }
    }
    throw invalid_argument("ERROR! Invalid operator!");
}

double Formula::formulaWithNumberAndCell(string formula, const matrix &mat) {
    formula.erase(0, 1);  //removing '=' from the formula;
    isValidFormulaWithNumberAndCell(formula);
    string firstPartOfFormula, secondPartOfFormula;
    int pos;
    splitFormula(formula, firstPartOfFormula, secondPartOfFormula, pos);
    bool foundInFirst = foundInPart(firstPartOfFormula);
    bool foundInSecond = foundInPart(secondPartOfFormula);
    if (foundInFirst && !foundInSecond) {
        // the first part of the formula is the cell
        vector<string> cellCoordinatesAsString;
        extractNumbers(cellCoordinatesAsString, firstPartOfFormula);
        vector<int> coordinates = parseStringVecToIntVec(cellCoordinatesAsString);
        double cellDouble = getTheValueOfCell(mat, coordinates.at(0) - 1, coordinates.at(1) - 1);
        double numberInFormula = stod(secondPartOfFormula);
        if (formula.at(pos) == '+') {
            return cellDouble + numberInFormula;
        } else if (formula.at(pos) == '-') {
            return cellDouble - numberInFormula;
        } else if (formula.at(pos) == '*') {
            return cellDouble * numberInFormula;
        } else if (formula.at(pos) == '/') {
            if (numberInFormula == 0) {
                throw domain_error("Can not divide by 0!");
            } else {
                return cellDouble / numberInFormula;
            }
        } else if (formula.at(pos) == '^') {
            return pow(cellDouble, numberInFormula);
        }
    }
    if (!foundInFirst && foundInSecond) {
        // the second part of the formula is the cell
        vector<string> cellCoordinatesAsString;
        extractNumbers(cellCoordinatesAsString, secondPartOfFormula);
        vector<int> coordinates = parseStringVecToIntVec(cellCoordinatesAsString);
        double cellDouble = getTheValueOfCell(mat, coordinates.at(0) - 1, coordinates.at(1) - 1);
        double numberInFormula = stod(firstPartOfFormula);
        if (formula.at(pos) == '+') {
            return numberInFormula + cellDouble;
        } else if (formula.at(pos) == '-') {
            return numberInFormula - cellDouble;
        } else if (formula.at(pos) == '*') {
            return numberInFormula * cellDouble;
        } else if (formula.at(pos) == '/') {
            if (cellDouble == 0) {
                throw domain_error("ERROR! Can not divide by 0!");
            } else {
                return numberInFormula / cellDouble;
            }
        } else if (formula.at(pos) == '^') {
            return pow(numberInFormula, cellDouble);
        }
    }
}

void Formula::splitFormula(const string &formula, string &firstPart, string &secondPart, int &p) {
    char delim = '0';
    for (int i = 1; i < formula.length(); ++i) {
        if (formula.at(i) == '+') {
            delim = '+';
            break;
        } else if (formula.at(i) == '-') {
            delim = '-';
            break;
        } else if (formula.at(i) == '*') {
            delim = '*';
            break;
        } else if (formula.at(i) == '/') {
            delim = '/';
            break;
        } else if (formula.at(i) == '^') {
            delim = '^';
            break;
        }
    }
    p = formula.find(delim);
    firstPart = formula.substr(0, p);
    secondPart = formula.substr(p + 1);
}

void Formula::isValidFormulaWithTwoNumbers(const string &formula) {
    for (int i = 0; i < formula.length(); ++i) {    // checking for invalid symbols
        if (formula.at(i) != '0' && formula.at(i) != '9' && formula.at(i) != '.' && formula.at(i) != '+' &&
            formula.at(i) != '-' && formula.at(i) != '*' && formula.at(i) != '/' && formula.at(i) != '^' &&
            formula.at(i) != ' ' && formula.at(i) != '1' && formula.at(i) != '2' && formula.at(i) != '3' &&
            formula.at(i) != '4' && formula.at(i) != '5' && formula.at(i) != '6' && formula.at(i) != '8') {
            throw invalid_argument("ERROR! Invalid formula!");
        }
    }
}

double Formula::getTheValueOfCell(const matrix &mat, int row, int col) {
    double result;
    string cellValueAsString;
    for (int i = 0; i < mat.size(); ++i) {
        if (i == row) {
            for (int j = 0; j < mat[i].size(); ++j) {
                if (j == col) {
                    cellValueAsString = mat[i][j];
                }
            }
        }
    }
    result = stringToNumber(cellValueAsString);
    return result;
}

void Formula::isValidFormulaWithNumberAndCell(const string &formula) {
    for (int i = 0; i < formula.length(); ++i) { // checking for invalid symbols
        if (formula.at(i) != '.' && formula.at(i) != '+' && formula.at(i) != '-' && formula.at(i) != '*' &&
            formula.at(i) != '/' && formula.at(i) != '^' && formula.at(i) != ' ' && formula.at(i) != '0' &&
            formula.at(i) != '1' && formula.at(i) != '2' && formula.at(i) != '3' && formula.at(i) != '4' &&
            formula.at(i) != '5' && formula.at(i) != '6' && formula.at(i) != '8' && formula.at(i) != '9' &&
            formula.at(i) != 'R' && formula.at(i) != 'r' && formula.at(i) != 'C' && formula.at(i) != 'c') {
            throw invalid_argument("ERROR! Invalid formula!");
        }
    }
}

bool Formula::foundInPart(const string &str) {
    for (char i : str) {
        if (i == 'R' || i == 'r')
            return true;
    }
    return false;
}

void Formula::extractNumbers(vector<string> &rowsCols, const string &str) {
    regex e(R"(\d+)");
    sregex_iterator iter(str.begin(), str.end(), e);
    sregex_iterator end;
    while (iter != end) {
        for (unsigned i = 0; i < iter->size(); ++i) {
            string number = (*iter)[i];
            rowsCols.push_back(number);
        }
        ++iter;
    }
}

vector<int> Formula::parseStringVecToIntVec(vector<string> rowsCols) {
    vector<int> vectorOfNumbers;
    for (auto &s : rowsCols) {
        stringstream parser(s);
        int x = 0;
        parser >> x;
        vectorOfNumbers.push_back(x);
    }
    return vectorOfNumbers;
}

#endif //TABLEREADING_READFILE_H
