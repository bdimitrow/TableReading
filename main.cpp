#include <iostream>
#include <string>
#include "matrix.h"
#include "application.h"

using namespace std;

int main() {
    cout << "Welcome to Table's reading app!" << endl;
    string command;
    cout << "Enter command: ";
    Application file;
    while (cin >> command ) {
        if (command == "open") {
            string filename;
            cin >> filename;
            file.setMatrix(file.openFile(filename));
            file.setFilename(filename);
        } else if (command == "help") {
            file.help();
        } else if (command == "exit") {
            file.exit();
        } else if (command == "close") {
            if (file.getFilename().empty()) {
                cout << "First you have to open a file!" << endl;
            } else {
                file.close(file.getFilename());
            }
        } else if (command == "save") {
            if (file.getFilename().empty()) {
                cout << "First you have to open a file!" << endl;
            } else {
                file.save(file.getMatrix(), file.getFilename());
            }
        } else if (command == "saveas") {
            if (file.getFilename().empty()) {
                cout << "First you have to open a file!" << endl;
            } else {
                file.saveAs(file.getMatrix());
            }
        } else if (command == "print") {
            if (file.getFilename().empty()) {
                cout << "First you have to open a file!" << endl;
            } else {
                Matrix *mat = mat->getInstance();
                mat->setMatrix(file.getMatrix());
                mat->printMatrix();
            }
        } else if (command == "edit") {
            if (file.getFilename().empty()) {
                cout << "First you have to open a file!" << endl;
            } else {
                int row, col;
                cout << "Enter the row of the cell you'd like to edit: ";
                cin >> row;
                cout << "Enter the column of the cell you'd like to edit: ";
                cin >> col;
                matrix beingEditted = file.getMatrix();
                try {
                    if (row > beingEditted.size() || col > beingEditted[row].size()) {
                        throw invalid_argument(
                                "ERROR! You are trying to edit a cell that is beyond the ranges of the table");
                    }
                    Matrix *mat = mat->getInstance();
                    file.setMatrix(mat->edit(beingEditted, row - 1, col - 1));
                } catch (invalid_argument &e) {
                    cout << e.what() << endl;
                } catch (domain_error &c) {
                    cout << c.what() << endl;
                    matrix mat = file.getMatrix();
                    mat[row - 1][col - 1] = "ERROR";
                    file.setMatrix(mat);
                }
            }
        } else {
            cout << "Invalid command!Try: help" << endl;
        }
        cout << "What to do now? " << endl;
    }
    return 0;
}
