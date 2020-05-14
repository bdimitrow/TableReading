//
// Created by bozhidar on 5/9/20.
//

#ifndef TABLEREADING_FILE_H
#define TABLEREADING_FILE_H

#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class File {
public:
    File(string _fileName) : fileName(_fileName) {}

    void open(string filename){
        fstream fout;
        fout.open(filename, ios::out | ios::in | ios:: app);
        if(fout.is_open()) {
            cout << "Successfully opened "<< filename << endl;
        } else
            throw "Error opening the file!"; cout << endl;
    }
    void close();
    void save();
    void saveAs();

private:
    string fileName;
};


#endif //TABLEREADING_FILE_H
