#include <fstream>
#include <iostream>
#include <cstring>
#include <vector>
#include <string>
#include "commands.h"
#include "readFile.h"
#include "dataTypes.h"
#include "CellClass.h"
#include "application.h"
#include "heterogeneousContainer.h"

using namespace std;

int main() {
    cout << "Welcome to Table's reading app!" << endl;
    string command;
    cout << "Enter command: ";
    Application file;
    while (cin >> command || command == "exit") {
        if (command == "open") {
            string filename;
            cin >> filename;
            file.setMat(file.openFile(filename));
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
                file.save(file.getMat(), file.getFilename());
            }
        } else if (command == "saveas") {
            if (file.getFilename().empty()) {
                cout << "First you have to open a file!" << endl;
            } else {
                file.saveAs(file.getMat());
            }
        } else if (command == "print") {
            if (file.getFilename().empty()) {
                cout << "First you have to open a file!" << endl;
            } else {
                printMatrix(file.getMat());
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
                matrix beingEditted = file.getMat();
                try {
                    edit(beingEditted, row - 1, col - 1);
                    cout << "File was editted successfully! Do you want to save is? [Y/N]  ";
                    char choice;
                    cin >> choice;
                    if(choice =='Y' || choice == 'y') {
                        file.save(beingEditted, file.getFilename());
                    }
                } catch (exception &e) {
                    cout << e.what() << endl;
                }

            }
        } else {
            cout << "Invalid command!" << endl;
        }
        cout << "What to do now? " << endl;
    }














    //    menu();
//        open("table.txt");
//    matrix table = fileToMatrix("table.txt");
//    edit(table, 2, 3);
//    save(table, "table.txt");
//    cout << "blabla";
//    matrix test = fileToMatrix("test.txt");
//    printMatrix(test);
//    cout << maxWidthOfCell(table);
//    cout << maxElementPerRowWholeTable(table);
//    editCell(table, 2, 1, "=nene da");
//    printMatrix(table);
//    save(table, "table.txt");
//    string inte = "-333";
//    string chislo = "123.32";
//    string num = "123.32.32";
//    string duma = "213.32ас";
//    string prazen = "";
//    string str = "\"123\"";
//    cout << stringToNumber(str) << endl;
//    cout << stringToNumber(inte) << endl;
//    cout << stringToNumber(chislo) << endl;
//    cout << stringToDouble(chislo) << endl;
//    cout << stringToDouble(num) << endl;
//    cout << stringToNumber(num) << endl;
//    cout << stringToNumber(duma) << endl;
//    cout << stringToNumber(prazen) << endl;

//    string a = "123";
//    string b ="123.13";
//    cout << isInteger(a) << endl;
//    cout << isDouble(a) << endl;
//    cout << isInteger(b) << endl;
//    cout << isDouble(b) << endl;

//    string formula = "=R12C14 + R5C2";
//    vector<int> digits;
//    extractRowsCols(digits, formula);
//    extractIntegersFromString(formula);



    return 0;
}



