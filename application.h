#ifndef TABLEREADING_APPLICATION_H
#define TABLEREADING_APPLICATION_H

#include <string>
#include <iostream>
#include "matrix.h"
#include "formula.h"

using namespace std;
/*! \class Application
 *  \brief A class executing the common operations open, close, save, save as, help and exit.
 *
 *  This class is used to assign a file to an object of class Application. After that the common
 *  operations can be performed: open, close, save, save as, help and exit.
 */

/**
 * @param filename : String
 * @param mat : matrix
 */
class Application {
public:

    /**
     * A parametrized constructor with a default value.
     * @param fname : string
     */
    explicit Application(const string &fname = "");

    /**
     * Getter for matrix.
     * @return matrix mat
     */
    matrix getMatrix() const { return mat; }

    /**
     * Method setting the matrix.
     * @param m : matrix
     */
    void setMatrix(matrix m);

    /**
     * Getter for filename.
     * @return string filename
     */
    const string &getFilename() const { return filename; }

    /**
     * Methdd setting the filename.
     * @param fname : string
     */
    void setFilename(const string &fname);

    const string &getCommand() const;

    void setCommand(const string &command);

    /**
     * Function asking for command to be executed.
     */
    void insertCommand();

private:
    string filename;
    matrix mat;
    string command;

    /**
     * Method accepting a string(filename) and is opening the file with that name.
     * @param filename : string
     * @return matrix opened
     */
    matrix openFile(string filename);

    /**
     * Method closing the file with that name.
     * @param filename : string
     */
    void close();

    /**
     * Method saving a matrix(probably an edited one) to the same file.
     * @param mat : matrix
     * @param filename : string
     */
    void save();

    /**
     * Method saving the matrix(probably and edited one) to a new file.
     * The user should enter the name of the new file.
     * @param mat : matrix
     */
    void saveAs();

    /**
     * Method displaying all supported command by the application.
     */
    void help();

    /**
     * Method exiting the program.
     */
    void exit();

    /**
     * Method used to edit a cell in the matrix.
     */
    void edit();

    /**
     * Method used to print the table.
     */
    void print();

    /**
    * Method accepting string(command) and according to it calls another function.
    * @param command
    */
    void functionDispatcher();
};

#endif //TABLEREADING_APPLICATION_H
