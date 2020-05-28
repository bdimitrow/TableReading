//
// Created by bozhidar on 5/28/20.
//

#include "formula.h"

bool isNumeric(const string &str);

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

// is the string made of just digits and +-.
bool Formula::isNumeric(const string &str) {
    return str.find_first_not_of("+-0123456789.") == string::npos;
}


// converting string to int
int Formula::stringToInt(string word) {
    if (isNumeric(word)) {
        stringstream ss(word);
        int resultInt = 0;
        ss >> resultInt;
        return resultInt;
    }
}

// converting string to double
double Formula::stringToDouble(string word) {
    if (isNumeric(word)) {
        stringstream ss(word);
        double resultDouble = 0;
        ss >> resultDouble;
        return resultDouble;
    }
}

// removing the spaces from the left side of the stirng
string &Formula::ltrim(string &str) {
    const string &chars = "\t\n\v\f\r ";
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

// removing the spaces from the right side of the stirng
string &Formula::rtrim(string &str) {
    const string &chars = "\t\n\v\f\r ";
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

// removing the space from both sides of the string
string &Formula::trim(string &str) {
    const string &chars = "\t\n\v\f\r ";
    return ltrim(rtrim(str));
}

// removing quotes from the string
void Formula::removeQuotes(string &str) {
    trim(str);
    int size = str.size();
    if (str[0] == '"' && str[size - 1] == '"') {
        str.erase(0, 1);
        str.erase(size - 2, 1);
    }
}

// parsing the string into number
double Formula::stringToNumber(string word) {
    trim(word);             // removing the spaces from both sides
    removeQuotes(word);     // removing the quotes whether such exist
    int dotCount = 0;          // counting the number of dots
    for (int i = 0; i < word.size(); ++i) {
        if (word.at(i) == '.') {
            ++dotCount;
        }
    }
    // parsing the string into a number
    if (dotCount == 0) {
        return stringToInt(word);
    } else if (dotCount == 1 && (isNumeric(word))) {
        return stringToDouble(word);
    } else {
        return 0.0;
    }
}
