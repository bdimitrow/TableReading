#include "application.h"

Application::Application(const string &fname) : filename(fname) {}

void Application::setMatrix(matrix m) { mat = m; }

void Application::setFilename(const string &fname) { filename = fname; }

const string &Application::getCommand() const { return command; }

void Application::setCommand(const string &com) { command = com; }


matrix Application::openFile(string filename) {
    fstream fout;
    fout.open(filename, ios::out | ios::in | ios::app);
    if (fout.is_open()) {
        cout << "Successfully opened " << filename << endl;
        Matrix *mat = mat->getInstance();
        return mat->fileToMatrix(filename);
    } else {
        cout << "Unable to open " << filename << "!" << endl;
    }
}

void Application::close() {
    this->setFilename("");
    cout << "Successfully closed " << filename << endl;
}

void Application::save() {
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

void Application::saveAs() {
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
    cout << "The files was saved as " << filename << "successfully!" << endl;
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

void Application::edit() {
    int row, col;
    cout << "Enter the row of the cell you'd like to edit: ";
    do {
        if (!(cin >> row)) {
            cout << "Invalid entry! Please enter an integer: ";
            cin.clear();                            // reset any error flags
            cin.ignore(10000, '\n');       // ignore any characters in the input buffer                    }
        } else {
            break;
        }
    } while (true);
    cout << "Enter the column of the cell you'd like to edit: ";
    do {
        if (!(cin >> col)) {
            cout << "Invalid entry! Please enter an integer: ";
            cin.clear();                            // reset any error flags
            cin.ignore(10000, '\n');       // ignore any characters in the input buffer                    }
        } else {
            break;
        }
    } while (true);
    try {
        if (row > mat.size() || col > mat[row].size()) {
            throw invalid_argument(
                    "ERROR! You are trying to edit a cell that is beyond the ranges of the table");
        }
        Matrix *mat = mat->getInstance();
        this->setMatrix(mat->edit(row - 1, col - 1));
    } catch (invalid_argument &e) {
        cout << e.what() << endl;
    } catch (domain_error &c) {
        cout << c.what() << endl;
        mat[row - 1][col - 1] = "ERROR";
        this->setMatrix(mat);
    }
}

void Application::functionDispatcher() {
    string command = this->getCommand();
    if (command == "open") {
        string filename;
        cin >> filename;
        this->setMatrix(this->openFile(filename));
        this->setFilename(filename);
    } else if (command == "help") {
        this->help();
    } else if (command == "exit") {
        this->exit();
    } else if (command == "close") {
        if (this->getFilename().empty()) {
            cout << "First you have to open a file!" << endl;
        } else {
            this->close();
        }
    } else if (command == "save") {
        if (this->getFilename().empty()) {
            cout << "First you have to open a file!" << endl;
        } else {
            this->save();
        }
    } else if (command == "saveas") {
        if (this->getFilename().empty()) {
            cout << "First you have to open a file!" << endl;
        } else {
            this->saveAs();
        }
    } else if (command == "print") {
        if (this->getFilename().empty()) {
            cout << "First you have to open a file!" << endl;
        } else {
            Matrix *mat = mat->getInstance();
            mat->setMatrix(this->getMatrix());
            mat->printMatrix();
        }
    } else if (command == "edit") {
        if (this->getFilename().empty()) {
            cout << "First you have to open a file!" << endl;
        } else {
            this->edit();
        }
    } else {
        cout << "Invalid command!Try: help" << endl;
    }
    cout << "What to do now? " << endl;
}

void Application::insertCommand() {
    string command;
    cout << "Enter command: ";
    do {
        cin >> command;
        this->setCommand(command);
        functionDispatcher();
    }while(command != "exit");
}