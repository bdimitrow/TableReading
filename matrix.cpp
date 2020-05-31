#include "matrix.h"

string deleteSpacesFromString(string str) {
    str.erase(remove(str.begin(), str.end(), ' '), str.end());
    return str;
}

// is the string an integer
bool isInteger(const string &str) {
    return str.find_first_not_of("+-0123456789") == string::npos;
}

// is the string a double
bool isDouble(const string &str) {
    int dotCounter = 0;
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == '.') {
            dotCounter++;
        } else if (!isdigit(str[i])) {
            return false;
        }
    }
    return dotCounter == 1;
}

Matrix *Matrix::instance = 0;

matrix Matrix::fileToMatrix(const string &filename) {
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

void Matrix::printMatrix() {
    int length = maxElementPerRowWholeTable();
    int copiedCounter = 0;
    for (vec row : mat) {
        cout << setw(maxWidthOfCell());
        for (string s : row) {
            cout << setw(maxWidthOfCell()) << s << "|";
            ++copiedCounter;
        }
        // adding '|' whether the row is shorter
        while (copiedCounter < length) {
            cout << setw(maxWidthOfCell()) << "" << "|";
            copiedCounter++;
        }
        cout << endl;
        copiedCounter = 0;
    }
}

int Matrix::maxElementPerRowWholeTable() {
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

int Matrix::maxWidthOfCell() {
    int maxWidth = 0;
    int currentWidth = 0;
    for (vec row : mat) {
        for (string s : row) {
            currentWidth = s.length();
            if (currentWidth > maxWidth) {
                maxWidth = currentWidth;
            }
        }
    }
    return maxWidth;
}

matrix Matrix::editInteger(int row, int col) {
    matrix mat = this->getMat();
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
    return mat;
}

matrix Matrix::editDouble(int row, int col) {
    matrix mat = this->getMat();
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
    return mat;
}

matrix Matrix::editString(int row, int col) {
    matrix mat = this->getMat();
    string input;
    cout << "Enter a string: ";
    cin.ignore();
    getline(cin, input);
    // adding qoutes to the input
    string newValue = "\"" + input + "\"";
    if (row < mat.size() && col < mat[row].size()) {
        mat[row][col] = newValue;
    }
    return mat;
}

matrix Matrix::editFormula(int row, int col) {
    matrix mat = this->getMat();
    string input;
    cout << "Enter a formula: ";
    cin.ignore();
    getline(cin, input);
    string formulaString = deleteSpacesFromString(input);
    double newValue = 0;
    int Rcount = 0, Ccount = 0;
    for (int i = 0; i < input.length(); ++i) {
        if (input.at(i) == 'R' || input.at(i) == 'r') Rcount++;
        if (input.at(i) == 'C' || input.at(i) == 'c') Ccount++;
    }
    if (Rcount == 2 && Ccount == 2) {
        Formula formula(formulaString);
        newValue = formula.formulaWithTwoCells(mat);
    } else if (Rcount == 0 && Ccount == 0) {
        Formula formula(formulaString);
        newValue = formula.formulaWithTwoNumbers();
    } else if (Rcount == 1 && Ccount == 1) {
        Formula formula(formulaString);
        newValue = formula.formulaWithNumberAndCell(mat);
    } else if (Rcount != Ccount) {
        throw invalid_argument("ERROR! Wrong formula!");
    }
    if (row < mat.size() && col < mat[row].size()) {
        string value;
        stringstream ss;
        ss << newValue;
        value = ss.str();
        mat[row][col] = value;
    }
    return mat;
}

matrix Matrix::edit(int row, int col) {
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
                    this->setMatrix(editInteger(row, col));
                    return mat;
                }
                case 2: {
                    this->setMatrix(editDouble(row, col));
                    return mat;
                }
                case 3: {
                    this->setMatrix(editString(row, col));
                    return mat;
                }
                case 4:
                    this->setMatrix(editFormula(row, col));
                    return mat;
            }
        } else {
            cout << "Invalid choice!" << endl;
        }
    } while (true);
}

const matrix &Matrix::getMat() const {
    return mat;
}
