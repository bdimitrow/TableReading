#ifndef TABLEREADING_APPLICATION_H
#define TABLEREADING_APPLICATION_H

#include <string>
#include <iostream>
#include "matrix.h"
#include "formula.h"

using namespace std;

class Application {
public:
    Application(const string &fname = "");

    matrix getMat() const { return mat; }

    void setMat(matrix m);

    const string &getFilename() const { return filename; }

    void setFilename(const string &fname);

    matrix openFile(string filename);

    void close(string filename);

    void save(matrix mat, string filename);

    void saveAs(matrix mat);

    void help();

    void exit();

private:
    string filename;
    matrix mat;
};

#endif //TABLEREADING_APPLICATION_H
