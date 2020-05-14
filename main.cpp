#include <fstream>
#include <iostream>
#include <cstring>
#include "commands.h"
#include "readFile.h"
#include "dataTypes.h"
#include "CellClass.h"

using namespace std;

void menu();

int main() {
//    menu();
//        open("table.txt");
//    matrix table = fileToMatrix("table.txt");
//    editCell(table, 2, 1, "100da");
//    save(table, "table.txt");
    string inte = "-333";
    string chislo = "123.32";
    string num = "123.32.32";
    string duma = "213.32ас";
    cout << stringToNumber(inte) << endl;
    cout << stringToNumber(chislo) << endl;
    cout << stringToNumber(num) << endl;
    cout << stringToNumber(duma) << endl;

//    Cell<int> inte(2,2,10);
//    cout << inte.getValue() << endl;
//    Cell<string> stri(3,3,"dada");
//    cout << stringToNumber(stri.getValue()) << endl;
//    Cell<double> doble(4,4,123.3);
//    cout << doble.getValue() << endl;

    return 0;
}

void menu() {
    cout << "Welcome to the TableReading App!" << endl;
    cout << "Please enter the name of the file to be opened: ";
    string filename;
    cin >> filename;
    open(filename);

    cout << "Choose an operation: " << endl;
    cout << "Press 1 to print the file!" << endl;
    cout << "Press 2 to edit a cell in the file!" << endl;
    int driver;
    cin >> driver;
    switch (driver) {
        case 1: {
            vector<vector<string>> table = fileToMatrix(filename);
            printMatrix(table);
//            menu();
        }
            break;
        case 2: {
            vector<vector<string>> table = fileToMatrix(filename);
            cout << "Please enter the row and the col of the cell to be edited: ";
            int row, col;
            cin >> row >> col;
            cout << "Enter the new value: ";
            string newValue;
            cin.ignore();
            getline(cin, newValue);
            editCell(table, row, col, newValue);
//            save(filename);
        }
            break;
    }

}