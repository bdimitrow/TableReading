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
#include <stdexcept>
#include <exception>
#include <regex>
#include <cmath>
#include <string>
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
        throw std::invalid_argument("Unknown data type!");
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
        throw std::invalid_argument("Unknown data type!");
    }
}

void editString(matrix &mat, int row, int col) {
    string input;
    cout << "Enter a string: ";
    cin.ignore();
    getline(cin, input);
//                    string newValue = "\"" + input + "\"";
    string newValue = input;
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
                        newValue = formulaWithNumberAndCell(input);
                    } else if (Rcount != Ccount) {
                        throw std::invalid_argument("Wrong formula!");
                    }
                    if (row < mat.size() && col < mat[row].size()) {
                        string value = std::to_string(newValue);
                        mat[row][col] = value;
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
    vector<string> numbersString;
    extractNumbers(numbersString, formula);
    vector<int> numbers = parseStringVecToIntVec(numbersString);
    double cellDouble = 0;
    string cellString;
    // determining which one is first in the formula: number or cell
    string R = "R";
    string r = "r";
    int foundRAt = formula.find(R);
    int foundrAt = formula.find(r);
    if (foundRAt < formula.length() / 2 || foundrAt < formula.length() / 2) {
        // cell is first in the formula
        int row = numbers.at(0) - 1;
        int col = numbers.at(1) - 1;
        // getting the value of the cell
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
        for (int i = 0; i < formula.length(); ++i) {
            if (formula.at(i) == '+') {
                return cellDouble + numbers.at(2);
            } else if (formula.at(i) == '-') {
                return cellDouble + numbers.at(2);
            } else if (formula.at(i) == '*') {
                return cellDouble + numbers.at(2);
            } else if (formula.at(i) == '/') {
                if (numbers.at(2) == 0) {
                    throw std::domain_error("Can not divide by 0!");
                } else {
                    return cellDouble + numbers.at(2);
                }
            } else if (formula.at(i) == '^') {
                return pow(cellDouble, numbers.at(2));
            }
        }
        throw invalid_argument("Invalid operator!");
    } else {
        // number is first in the formula
        int row = numbers.at(1) - 1;
        int col = numbers.at(2) - 1;
        // getting the value of the cell
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
        for (int i = 0; i < formula.length(); ++i) {
            if (formula.at(i) == '+') {
                return numbers.at(0) + cellDouble;
            } else if (formula.at(i) == '-') {
                return numbers.at(0) + cellDouble;
            } else if (formula.at(i) == '*') {
                return numbers.at(0) + cellDouble;
            } else if (formula.at(i) == '/') {
                if (cellDouble == 0) {
                    throw std::domain_error("Can not divide by 0!");
                } else {
                    return numbers.at(0) + cellDouble;
                }
            } else if (formula.at(i) == '^') {
                return pow(numbers.at(0), cellDouble);
            }
        }
        throw invalid_argument("Invalid operator!");
    }
}

double formulaWithTwoNumbers(string formula) {
    vector<string> numbersString;
    extractNumbers(numbersString, formula);
    vector<int> numbers = parseStringVecToIntVec(numbersString);
    // determining the operator
    for (int i = 0; i < formula.length(); ++i) {
        if (formula.at(i) == '+') {
            return numbers.at(0) + numbers.at(1);
        } else if (formula.at(i) == '-') {
            return numbers.at(0) + numbers.at(1);
        } else if (formula.at(i) == '*') {
            return numbers.at(0) + numbers.at(1);
        } else if (formula.at(i) == '/') {
            if (numbers.at(1) == 0) {
                throw std::domain_error("Can not divide by 0!");
            } else {
                return numbers.at(0) + numbers.at(1);
            }
        } else if (formula.at(i) == '^') {
            return pow(numbers.at(0), numbers.at(1));
        }
    }
    throw invalid_argument("Invalid operator!");
}

double formulaWithTwoCells(string formula, const matrix &mat) {  // =R22C4 + R2C1
    vector<string> rowsCols;
    extractNumbers(rowsCols, formula);
    vector<int> numbersRowsCols;
    // parsing from vector<string> to vector<int>
    for (auto &s : rowsCols) {
        std::stringstream parser(s);
        int x = 0;
        parser >> x;
        numbersRowsCols.push_back(x);
    }
    double firstCell = 0.0, secondCell = 0.0;
    string first, second;
    int row1 = numbersRowsCols.at(0) - 1;
    int col1 = numbersRowsCols.at(1) - 1;
    // getting the value of the first cell
    for (int i = 0; i < mat.size(); ++i) {
        if (i == row1) {
            for (int j = 0; j < mat[i].size(); ++j) {
                if (j == col1) {
//                    firstCell = stringToNumber(mat[i][j]);
                    first = mat[i][j];
//                    goto label;
                }
            }
        }
    }
    // getting the value of the second cell;
//    label:
    for (int i = 0; i < mat.size(); ++i) {
        if (i == numbersRowsCols.at(2) - 1) {
            for (int j = 0; j < mat[i].size(); ++j) {
                if (j == (numbersRowsCols.at(3) - 1)) {
//                    secondCell = stringToNumber(mat[i][j]);
                    second = mat[i][j];
                }
            }
        }
    }
    firstCell = stringToNumber(first);
    secondCell = stringToNumber(second);
    // determining the operator
    for (int i = 0; i < formula.length(); ++i) {
        if (formula.at(i) == '+') {
            return firstCell + secondCell;
        } else if (formula.at(i) == '-') {
            return firstCell - secondCell;
        } else if (formula.at(i) == '*') {
            return firstCell * secondCell;
        } else if (formula.at(i) == '/') {
            if (secondCell == 0) {
                throw std::domain_error("Can not divide by 0!");
            } else {
                return firstCell / secondCell;
            }
        } else if (formula.at(i) == '^') {
            return pow(firstCell, secondCell);
        }
    }
    throw invalid_argument("Invalid operator!");
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
