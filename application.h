//
// Created by bozhidar on 5/21/20.
//

#ifndef TABLEREADING_APPLICATION_H
#define TABLEREADING_APPLICATION_H

#include <string>
#include <iostream>
#include "commands.h"
#include "readFile.h"

using namespace std;

class Application {
private:
    string filename;
    matrix mat;
public:
    Application(const string &filename = "") : filename(filename) {}

    matrix getMat() const { return mat; }

    void setMat(matrix m) { mat = m; }

    const string &getFilename() const { return filename; }

    void setFilename(const string &fname) { filename = fname; }

    matrix openFile(string filename) {
        fstream fout;
        fout.open(filename, ios::out | ios::in | ios::app);
        if (fout.is_open()) {
            cout << "Successfully opened " << filename << endl;
            matrix opened = fileToMatrix(filename);
            return opened;
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
        if (!out.is_open()) {
            cerr << "Unable to open file!\n";
        }
        for (vec row : mat) {
            for (string s : row) {
                out << s << ",";
            }
            out << endl;
        }
        out.close();
        cout << filename << " was successfully saved!" << endl;
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
        ::exit(EXIT_SUCCESS);
    }
};

#endif //TABLEREADING_APPLICATION_H
