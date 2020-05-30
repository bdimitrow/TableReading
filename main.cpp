#include <iostream>
#include "application.h"

using namespace std;

int main() {
    cout << "Welcome to Table's reading app!" << endl;
    Application app;
    app.insertCommand();
    return 0;
}

/*!
 * \mainpage Table Reading App Documentation
 *
 * \section First Project's aim
 *  The aim of this project is to create an application that represents an information
 *  from a text file into a table. Every line in the file is represented by a single
 *  row in the table. Also every row can contain different number of elements(cells).
 *  Two cells are separeted by a comma. Between two commas there could be nothing. That
 *  represents an empty cell.
 *      Every cell has its own type. The supported ones are: whole number(int),
 *  rational number(double), symbolic string(string) and formula. A formula consists
 *  of three parts. A single operator in the middle and the other two parts can be
 *  a number or a reference to a cell in the table.
 *
 * \subsection Github
 * https://github.com/bdimitrow/TableReading
 *
 * \section Second Happy path
 * * Let's consider having a 3x3 table as file with the name tableTest.txt. <br>
 *   1  |  2   | 4 <br>
 *   3  | "da" | 10.5 <br>
 *  5.5 |      | 11 <br>
 *
 * \subsection running Run the program
 * Output: Welcome to Table's reading app! <br>
          Enter command: <br>
  Input: open tableTest.txt <br>
  Output: Successfully opened tableTest.txt <br>
           What to do now? <br>
  Input: print <br>
  Output:      1  |  2   | 4 <br>
               3  | "da" | 10.5 <br>
              5.5 |      | 11 <br>
              What to do now? <br>
  Input: edit <br>
  Output: Enter the row of the cell you'd like to edit: <br>
  Input: 1 <br>
  Output: Enter the column of the cell you'd like to edit:  <br>
  Input: 2 <br>
  Output: What type of data would you like to insert?<br>
            1. Integer<br>
            2. Double<br>
            3. String<br>
            4. Formula<br>
   * Choose an action: <br>
    Input: 4 <br>
    Output: Enter a formula: <br>
    Input: =R2C1*R3C1 <br>
    Output: What to do now? <br>
 *  Input: print <br>
 *  Output:  *   1  | 16.5 | 4 <br>
 *               3  | "da" | 10.5 <br>
 *              5.5 |      | 11 <br>
 *             What to do now? <br>
 *   Input: close <br>
 *   Output: Successfully closed tableTest.txt <br>
            What to do now? <br>
 *  Input: exit <br>
 *  Output: Exiting the program!<br>
 *
 */
