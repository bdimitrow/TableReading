#include "formula.h"
#include "stringUtils.h"

double Formula::formulaWithTwoNumbers(string formula) {
    formula.erase(0, 1);  //removing '=' from the formula;
    // TODO if .... else throw
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
    vector<int> numbersRowsCols = parseStringVectorToIntVector(rowsColsAsStrings);
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
    // TODO if ... else throw
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
        vector<int> coordinates = parseStringVectorToIntVector(cellCoordinatesAsString);
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
        vector<int> coordinates = parseStringVectorToIntVector(cellCoordinatesAsString);
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

void Formula::splitFormula(const string &formula, string &firstPart, string &secondPart, int &position) {
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
    position = formula.find(delim);
    firstPart = formula.substr(0, position);
    secondPart = formula.substr(position + 1);
}

void Formula::isValidFormulaWithTwoNumbers(const string &formula) {
    for (int i = 0; i < formula.length(); ++i) {    // checking for invalid symbols
        if (formula.at(i) != '0' && formula.at(i) != '9' && formula.at(i) != '.' && formula.at(i) != '+' &&
            formula.at(i) != '-' && formula.at(i) != '*' && formula.at(i) != '/' && formula.at(i) != '^' &&
            formula.at(i) != ' ' && formula.at(i) != '1' && formula.at(i) != '2' && formula.at(i) != '3' &&
            formula.at(i) != '4' && formula.at(i) != '5' && formula.at(i) != '6' && formula.at(i) != '7' && formula.at(i) != '8') {
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
            formula.at(i) != '5' && formula.at(i) != '6' && formula.at(i) != '7' && formula.at(i) != '8' &&
            formula.at(i) != '9' && formula.at(i) != 'R' && formula.at(i) != 'r' && formula.at(i) != 'C' && formula.at(i) != 'c') {
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
