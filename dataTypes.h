//
// Created by bozhidar on 5/7/20.
//

#ifndef TABLEREADING_DATATYPES_H
#define TABLEREADING_DATATYPES_H

#include <string>
#include <sstream>
#include "readFile.h"

using namespace std;

/*  1. int (123, -123, +123)
 *  2. double (123.456, -123,34, +123,32)
 *  3. string ("hello")
 *  4. formula ( + - * / ^) starts with =
 */


bool isNumeric(const string &str) {
    return str.find_first_not_of("+-0123456789.") == string::npos;
}

bool isInteger(const string &str) {
    return str.find_first_not_of("+-0123456789") == string::npos;
}

bool isDouble(const string &str) {
    int dotCounter = 0;
    for (int i = 0; i < str.length(); ++i) {
        if (str[i] == '.') {
            dotCounter++;
        } else if (!isdigit(str[i])) {
            return false;
        }
    }
    return dotCounter == 1;
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
        stringstream ss(word);
        double resultDouble = 0;
        ss >> resultDouble;
        return resultDouble;
    }
}

string& ltrim(string& str, const string& chars = "\t\n\v\f\r ")
{
    str.erase(0, str.find_first_not_of(chars));
    return str;
}
string& rtrim(string& str, const string& chars = "\t\n\v\f\r ")
{
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}
string& trim(string& str, const string& chars = "\t\n\v\f\r ")
{
    return ltrim(rtrim(str, chars), chars);
}

double stringToNumber(string word) {
    trim(word);
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
