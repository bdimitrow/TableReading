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
void save();

void open(string filename) {
    fstream fout;
    fout.open(filename, ios::out | ios::in | ios:: app);
    if(fout.is_open()) {
        cout << "Successfully opened "<< filename << endl;
    } else
        cout << "Unable to open " << filename << "!" << endl;
}

void close(string filename) {
    fstream fout;
    fout.close();
    cout << "Successfully closed " << filename << endl;
}

void save(matrix mat, string filename) {
    fstream ftable;
    ftable.open(filename, ios::in | ios::out | ios::trunc);
    for(vec row : mat) {
        for(string s : row) {
            ftable >> s;
        }
        cout << endl;
    }
}



#endif //TABLEREADING_COMMANDS_H
