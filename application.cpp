#include "application.h"

Application::Application(const string &fname) : filename(fname) {}

void Application::setMat(matrix m) { mat = m; }

void Application::setFilename(const string &fname) { filename = fname; }

matrix Application::openFile(string filename) {
    fstream fout;
    fout.open(filename, ios::out | ios::in | ios::app);
    if (fout.is_open()) {
        cout << "Successfully opened " << filename << endl;
        Matrix *mat = mat->getInstance();
        matrix opened = mat->fileToMatrix(filename);
        return opened;
    } else
        cout << "Unable to open " << filename << "!" << endl;
}

void Application::close(string filename) {
    fstream fout;
    fout.close();
    cout << "Successfully closed " << filename << endl;
}

void Application::save(matrix mat, string filename) {
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

void Application::saveAs(matrix mat) {
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

void Application::help() {
    cout << "The following commands are supported: " << endl
         << "open <file>  -  opens <file>" << endl
         << "close  -  closes currently opened file" << endl
         << "save  -  saves the currently open file" << endl
         << "saveas <file>  -  saves the currently open file in <file>" << endl
         << "help  -  prints this information" << endl
         << "exit  -  exists the program" << endl << endl;
}

void Application::exit() {
    cout << "Exiting the program!" << endl;
    ::exit(EXIT_SUCCESS);
}
