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

    /**
     * Method accepting a string(filename) and is opening the file with that name.
     * @param filename : string
     * @return matrix opened
     */
    matrix openFile(string filename);

    /**
     * Method accepting a string(filename) and is closing the file with that name.
     * @param filename : string
     */
    void close();

    /**
     * Method accepting a matrix(probably an editted one) and is saving it to the same file.
     * @param mat : matrix
     * @param filename : string
     */
    void save();

    /**
     * Method accepting a matrix(probably and editted one) and is saving it to a new file. The user
     * should enter the name of the new file.
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

private:
    string filename;
    matrix mat;
};

#endif //TABLEREADING_APPLICATION_H
