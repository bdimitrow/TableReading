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

void editInteger(matrix &mat, int row, int col);

void editDouble(matrix &mat, int row, int col);

void editString(matrix &mat, int row, int col);


double formula(string formula, matrix mat); // =R2C4 + R2C1
void extractRowsCols(vector<int> &rowsCols, const string &str);

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
//                case 4:
//                    string input;
//                    cout << "Enter a formula: ";
//                    cin.ignore();
//                    getline(cin, input);
//                    double newValue;
//                    newValue = formula(input, mat);
//                    if (row < mat.size() && col < mat[row].size()) {
//                        string value = std::to_string(newValue);
//                        mat[row][col] = value;
//                    }
//                    return;
//                    break;
            }
        } else {
            cout << "Invalid choice!" << endl;
        }
    } while (true);
}


double formula(string formula, matrix mat) {  // =R2C4 + R2C1
    vector<int> rowsCols;
    double firstCell, secondCell;
    extractRowsCols(rowsCols, formula);
    for (int i = 0; i < mat.size(); ++i) {
        if (i == rowsCols.at(0) - 1) {
            for (int j = 0; i < mat[i].size(); ++i) {
                if (j == rowsCols.at(1) - 1) {
                    firstCell = stringToNumber(mat[i][j]);
                    goto label;
                }
            }
        }
    }
    label:
    for (int i = 0; i < mat.size(); ++i) {
        if (i == rowsCols.at(2) - 1) {
            for (int j = 0; i < mat[i].size(); ++i) {
                if (j == rowsCols.at(3) - 1) {
                    secondCell = stringToNumber(mat[i][j]);
                }
            }
        }
    }
    return firstCell + secondCell;
}

void extractRowsCols(vector<int> &rowsCols, const string &str) {
    for (auto i : str) {
        if (isdigit(i)) {
            rowsCols.push_back(stoi(string{i}));
        }
    }
}


#endif //TABLEREADING_READFILE_H
