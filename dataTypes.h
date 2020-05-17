//
// Created by bozhidar on 5/7/20.
//

#ifndef TABLEREADING_DATATYPES_H
#define TABLEREADING_DATATYPES_H

#include <string>
#include <sstream>

using namespace std;

/*  1. int (123, -123, +123)
 *  2. double (123.456, -123,34, +123,32)
 *  3. string ("hello")
 *  4. formula ( + - * / ^) starts with =
 */


bool isNumeric(const string &str){
    return str.find_first_not_of("+-0123456789.") == string::npos;
}

int stringToInt(string word) {
    if (isNumeric(word)) {
        stringstream ss(word);
        int resultInt = 0;
        ss >> resultInt;
        return resultInt;
    }
}

double stringToDouble(string word) {
    if (isNumeric(word)) {
        for (int i = 0; i < word.size(); ++i) {
            if (word.at(i) >= '0' && word.at(i) <= '9') {
                stringstream ss(word);
                double resultDouble = 0;
                ss >> resultDouble;
                return resultDouble;
            }
        }
    }
}

double stringToNumber(string word) {
    int dotCount = 0;
    for (int i = 0; i < word.size(); ++i) {
        if (word.at(i) == '.') {
            ++dotCount;
        }
    }
    if (dotCount == 0) {
        return stringToInt(word);
    } else if (dotCount == 1 && (isNumeric(word))) {
        return stringToDouble(word);
    } else {
        return 0.0;
    }
}




#endif //TABLEREADING_DATATYPES_H
