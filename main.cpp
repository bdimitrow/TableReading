#include <fstream>
#include <iostream>
#include <cstring>
#include "commands.h"
#include "readFile.h"
#include "dataTypes.h"
#include "CellClass.h"
#include "heterogeneousContainer.h"
using namespace std;

int main() {
//    menu();
//        open("table.txt");
    matrix table = fileToMatrix("table.txt");
    matrix test = fileToMatrix("test.txt");
    printMatrix(table);
//    cout << maxWidthOfCell(table);
//    cout << maxElementPerRowWholeTable(table);
//    editCell(table, 2, 1, "1ddadaa");
//    save(table, "table.txt");
//    string inte = "-333";
//    string chislo = "123.32";
//    string num = "123.32.32";
//    string duma = "213.32ас";
//    string prazen = "";
//    cout << stringToNumber(inte) << endl;
//    cout << stringToNumber(chislo) << endl;
//    cout << stringToNumber(num) << endl;
//    cout << stringToNumber(duma) << endl;
//    cout << stringToNumber(prazen) << endl;



//    Cell<int> inte(2,2,10);
//    cout << inte.getValue() << endl;
//    Cell<string> stri(3,3,"dada");
//    cout << stringToNumber(stri.getValue()) << endl;
//    Cell<double> doble(4,4,123.3);
//    cout << doble.getValue() << endl;

    return 0;
}



