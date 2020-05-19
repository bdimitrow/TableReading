//
// Created by bozhidar on 5/7/20.
//

#ifndef TABLEREADING_COMMANDS_H
#define TABLEREADING_COMMANDS_H

#include <iostream>
#include <cstring>
#include <fstream>
#include "readFile.h"

using namespace std;

void open(string);

void close(string);

void save(matrix, string);

void saveAs(matrix);

void help();

void exit();

void open(string filename) {
    fstream fout;
    fout.open(filename, ios::out | ios::in | ios::app);
    if (fout.is_open()) {
        cout << "Successfully opened " << filename << endl;
    } else
        cout << "Unable to open " << filename << "!" << endl;
}

void close(string filename) {
    fstream fout;
    fout.close();
    cout << "Successfully closed " << filename << endl;
}

void save(matrix mat, string filename) {
    ofstream out;
    out.open(filename, ios::out | ios::trunc);
    for (vec row : mat) {
        for (string s : row) {
            out << s << ",";
        }
        out << endl;
    }
    out.close();
}

void saveAs(matrix mat) {
    cout << "Enter the name and the extension where the table should be saved: ";
    string filename;
    cin.ignore();
    getline(cin, filename);
    ofstream out;
    out.open(filename, ios::out | ios::trunc);
    for (vec row : mat) {
        for (string s : row) {
            out << s << ",";
        }
        out << endl;
    }
    out.close();
}

void help() {
    cout << "The following commands are supported: " << endl
         << "open <file>  -  opens <file>" << endl
         << "close  -  closes currently opened file" << endl
         << "save  -  saves the currently open file" << endl
         << "saveas <file>  -  saves the currently open file in <file>" << endl
         << "help  -  prints this information" << endl
         << "exit  -  exists the program" << endl << endl;
}

void exit() {
    cout << "Exiting the program!" << endl;
    exit(EXIT_SUCCESS);
}


#endif //TABLEREADING_COMMANDS_H
