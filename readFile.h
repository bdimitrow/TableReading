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
#include "formula.h"
#include "dataTypes.h"

using namespace std;

using vec = vector<string>;
using matrix = vector<vec>;

// saving the data from CSV file to a matrix of vectors
matrix fileToMatrix(string filename);

void printMatrix(const matrix &mat);

int maxElementPerRowWholeTable(const matrix &mat);

int maxWidthOfCell(const matrix &mat);

void editInteger(matrix &mat, int row, int col);

void editDouble(matrix &mat, int row, int col);

void editString(matrix &mat, int row, int col);

double formulaWithTwoCells(string formula, const matrix &mat); // =R2C4 + R2C1

double formulaWithTwoNumbers(string formula);

double formulaWithNumberAndCell(string formula, const matrix &mat);

// using regex to extract numbers from string(the numbers are saved as strings into a vector)
void extractNumbers(vector<string> &rowsCols, const string &str);

// parsing vector<string> to vector<int>
vector<int> parseStringVecToIntVec(vector<string> rowsCols);

bool isInteger(double num);

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

void editInteger(matrix &mat, int row, int col) {
    string input;
    cout << "Enter an integer: ";
    cin.ignore();
    getline(cin, input);
    if (isInteger(input)) {
        if (row < mat.size() && col < mat[row].size()) {
            mat[row][col] = input;
        }
    } else {
        throw std::invalid_argument("ERROR! Unknown data type!");
    }
}

void editDouble(matrix &mat, int row, int col) {
    string input;
    cout << "Enter a double: ";
    cin.ignore();
    getline(cin, input);
    if (isDouble(input)) {
        if (row < mat.size() && col < mat[row].size()) {
            mat[row][col] = input;
        }
    } else {
        throw std::invalid_argument("ERROR! Unknown data type!");
    }
}

void editString(matrix &mat, int row, int col) {
    string input;
    cout << "Enter a string: ";
    cin.ignore();
    getline(cin, input);
    string newValue = "\"" + input + "\"";
    if (row < mat.size() && col < mat[row].size()) {
        mat[row][col] = newValue;
    }
}

matrix edit(matrix &mat, int row, int col) {
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
            cin.ignore(10000, '\n');       // ignore any characters in the input buffer
        } else if (choice == 1 || choice == 2 || choice == 3 || choice == 4) {
            switch (choice) {
                case 1: {
                    editInteger(mat, row, col);
                    return mat;
                }
                    break;
                case 2: {
                    editDouble(mat, row, col);
                    return mat;
                }
                    break;
                case 3: {
                    editString(mat, row, col);
                    return mat;
                }
                    break;
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
                        newValue = formulaWithTwoCells(input, mat);
                    } else if (Rcount == 0 && Ccount == 0) {

                        newValue = formulaWithTwoNumbers(input);
                    } else if (Rcount == 1 && Ccount == 1) {
                        newValue = formulaWithNumberAndCell(input, mat);
                    } else if (Rcount != Ccount) {
                        throw std::invalid_argument("Wrong formula!");
                    }
                    if (row < mat.size() && col < mat[row].size()) {
                        string value;
                        if (ceil(newValue) == floor(newValue)) {
                            int number;
                            number = static_cast<int>(newValue);
                            value = std::to_string(number);
                        } else {
                            value = std::to_string(newValue);
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

double formulaWithNumberAndCell(string formula, const matrix &mat) {
    formula.erase(0, 1);  //removing '=' from the formula;
    for (int i = 0; i < formula.length(); ++i) { // checking for invalid symbols
        if (formula.at(i) != '.' && formula.at(i) != '+' && formula.at(i) != '-' && formula.at(i) != '*' &&
            formula.at(i) != '/' && formula.at(i) != '^' && formula.at(i) != ' ' && formula.at(i) != '0' &&
            formula.at(i) != '1' && formula.at(i) != '2' && formula.at(i) != '3' && formula.at(i) != '4' &&
            formula.at(i) != '5' && formula.at(i) != '6' && formula.at(i) != '8' && formula.at(i) != '9' &&
            formula.at(i) != 'R' && formula.at(i) != 'r' && formula.at(i) != 'C' && formula.at(i) != 'c') {
            throw invalid_argument("ERROR! Invalid formula!");
        }
    }
    // finding the operator and splitting the formula into two parts
    char delim;
    for (int i = 2; i < formula.length(); ++i) {
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
    int pos = formula.find(delim);
    string firstPartOfFormula = formula.substr(0, pos);
    string secondPartOfFormula = formula.substr(pos + 1);
    char R = 'R';
    char r = 'r';
    bool foundInFirst = false;
    bool foundInSecond = false;
    for (char i : firstPartOfFormula) {
        if (i == R || i == r)
            foundInFirst = true;
    }
    for (char i : secondPartOfFormula) {
        if (i == R || i == r)
            foundInSecond = true;
    }
    // determining which one is first in the formula: the cell or the number
    if (foundInFirst && !foundInSecond) {
        // the first part of the formula is the cell
        vector<string> coordinatesString;
        extractNumbers(coordinatesString, firstPartOfFormula);
        vector<int> coordinates = parseStringVecToIntVec(coordinatesString);
        double cellDouble = 0;
        string cellString;
        int row = coordinates.at(0) - 1;
        int col = coordinates.at(1) - 1;
        for (int i = 0; i < mat.size(); ++i) {
            if (i == row) {
                for (int j = 0; j < mat[i].size(); ++j) {
                    if (j == col) {
                        cellString = mat[i][j];
                    }
                }
            }
        }
        cellDouble = stringToNumber(cellString);
        double numberInFormula;
        numberInFormula = stod(secondPartOfFormula);
        // returning result
        if (formula.at(pos) == '+') {
            return cellDouble + numberInFormula;
        } else if (formula.at(pos) == '-') {
            return cellDouble - numberInFormula;
        } else if (formula.at(pos) == '*') {
            return cellDouble * numberInFormula;
        } else if (formula.at(pos) == '/') {
            if (numberInFormula == 0) {
                throw std::domain_error("Can not divide by 0!");
            } else {
                return cellDouble / numberInFormula;
            }
        } else if (formula.at(pos) == '^') {
            return pow(cellDouble, numberInFormula);
        }
    }
    if (!foundInFirst && foundInSecond) {
        // the second part of the formula is the cell
        vector<string> coordinatesString;
        extractNumbers(coordinatesString, secondPartOfFormula);
        vector<int> coordinates = parseStringVecToIntVec(coordinatesString);
        double cellDouble = 0;
        string cellString;
        int row = coordinates.at(0) - 1;
        int col = coordinates.at(1) - 1;
        for (int i = 0; i < mat.size(); ++i) {
            if (i == row) {
                for (int j = 0; j < mat[i].size(); ++j) {
                    if (j == col) {
                        cellString = mat[i][j];
                    }
                }
            }
        }
        cellDouble = stringToNumber(cellString);
        double numberInFormula;
        numberInFormula = stod(firstPartOfFormula);
        // returning result
        if (formula.at(pos) == '+') {
            return numberInFormula + cellDouble;
        } else if (formula.at(pos) == '-') {
            return numberInFormula - cellDouble;
        } else if (formula.at(pos) == '*') {
            return numberInFormula * cellDouble;
        } else if (formula.at(pos) == '/') {
            if (cellDouble == 0) {
                throw std::domain_error("ERROR! Can not divide by 0!");
            } else {
                return numberInFormula / cellDouble;
            }
        } else if (formula.at(pos) == '^') {
            return pow(numberInFormula, cellDouble);
        }
    }
}

double formulaWithTwoNumbers(string formula) {
    formula.erase(0, 1);  //removing '=' from the formula;
    for (int i = 0; i < formula.length(); ++i) {    // checking for invalid symbols
        if (formula.at(i) != '0' && formula.at(i) != '9' && formula.at(i) != '.' && formula.at(i) != '+' &&
            formula.at(i) != '-' && formula.at(i) != '*' && formula.at(i) != '/' && formula.at(i) != '^' &&
            formula.at(i) != ' ' && formula.at(i) != '1' && formula.at(i) != '2' && formula.at(i) != '3' &&
            formula.at(i) != '4' && formula.at(i) != '5' && formula.at(i) != '6' && formula.at(i) != '8') {
            throw invalid_argument("ERROR! Invalid formula!");
        }
    }
    // spliting the formula into two parts
    char delim;
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
    int pos = formula.find(delim);
    string firstPartOfFormula = formula.substr(0, pos);
    string secondPartOfFormula = formula.substr(pos + 1);
    double firstNumber = stod(firstPartOfFormula);
    double secondNumber = stod(secondPartOfFormula);
    // returning result
    if (formula.at(pos) == '+') {
        return firstNumber + secondNumber;
    } else if (formula.at(pos) == '-') {
        return firstNumber - secondNumber;
    } else if (formula.at(pos) == '*') {
        return firstNumber * secondNumber;
    } else if (formula.at(pos) == '/') {
        if (secondNumber == 0) {
            throw std::domain_error("ERROR! Can not divide by 0!");
        } else {
            return firstNumber / secondNumber;
        }
    } else if (formula.at(pos) == '^') {
        return pow(firstNumber, secondNumber);
    }
}

double formulaWithTwoCells(string formula, const matrix &mat) {  // =R22C4 + R2C1
    vector<string> rowsCols;
    extractNumbers(rowsCols, formula);
    // parsing from vector<string> to vector<int>
    vector<int> numbersRowsCols = parseStringVecToIntVec(rowsCols);
    double firstCell = 0.0, secondCell = 0.0;
    string first, second;
    int row1 = numbersRowsCols.at(0) - 1;
    int col1 = numbersRowsCols.at(1) - 1;
    // getting the value of the first cell
    for (int i = 0; i < mat.size(); ++i) {
        if (i == row1) {
            for (int j = 0; j < mat[i].size(); ++j) {
                if (j == col1) {
                    first = mat[i][j];
                }
            }
        }
    }
    // getting the value of the second cell;
    for (int i = 0; i < mat.size(); ++i) {
        if (i == numbersRowsCols.at(2) - 1) {
            for (int j = 0; j < mat[i].size(); ++j) {
                if (j == (numbersRowsCols.at(3) - 1)) {
                    second = mat[i][j];
                }
            }
        }
    }
    firstCell = stringToNumber(first);
    secondCell = stringToNumber(second);
    // determining the operator and returning result
    for (int i = 0; i < formula.length(); ++i) {
        if (formula.at(i) == '+') {
            return firstCell + secondCell;
        } else if (formula.at(i) == '-') {
            return firstCell - secondCell;
        } else if (formula.at(i) == '*') {
            return firstCell * secondCell;
        } else if (formula.at(i) == '/') {
            if (secondCell == 0) {
                throw std::domain_error("ERRO! Can not divide by 0!");
            } else {
                return firstCell / secondCell;
            }
        } else if (formula.at(i) == '^') {
            return pow(firstCell, secondCell);
        }
    }
    throw invalid_argument("ERROR! Invalid operator!");
}

vector<int> parseStringVecToIntVec(vector<string> rowsCols) {
    vector<int> vectorOfNumbers;
    for (auto &s : rowsCols) {
        stringstream parser(s);
        int x = 0;
        parser >> x;
        vectorOfNumbers.push_back(x);
    }
    return vectorOfNumbers;
}

void extractNumbers(vector<string> &rowsCols, const string &str) {
    std::regex e(R"(\d+)");
    std::sregex_iterator iter(str.begin(), str.end(), e);
    std::sregex_iterator end;
    while (iter != end) {
        for (unsigned i = 0; i < iter->size(); ++i) {
            string number = (*iter)[i];
            rowsCols.push_back(number);
        }
        ++iter;
    }
}

#endif //TABLEREADING_READFILE_H
