#ifndef TABLEREADING_DATATYPES_H
#define TABLEREADING_DATATYPES_H

#include <string>
#include <sstream>
#include "readFile.h"

using namespace std;

// is the string made of just digits and +-.
bool isNumeric(const string &str) {
    return str.find_first_not_of("+-0123456789.") == string::npos;
}

// is the string an integer
bool isInteger(const string &str) {
    return str.find_first_not_of("+-0123456789") == string::npos;
}

// is the string a double
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

// converting string to int
int stringToInt(string word) {
    if (isNumeric(word)) {
        stringstream ss(word);
        int resultInt = 0;
        ss >> resultInt;
        return resultInt;
    }
}

// converting string to double
double stringToDouble(string word) {
    if (isNumeric(word)) {
        stringstream ss(word);
        double resultDouble = 0;
        ss >> resultDouble;
        return resultDouble;
    }
}

// removing the spaces from the left side of the stirng
string &ltrim(string &str, const string &chars = "\t\n\v\f\r ") {
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

// removing the spaces from the right side of the stirng
string &rtrim(string &str, const string &chars = "\t\n\v\f\r ") {
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

// removing the space from both sides of the string
string &trim(string &str, const string &chars = "\t\n\v\f\r ") {
    return ltrim(rtrim(str, chars), chars);
}

// removing quotes from the string
void removeQuotes(string &str) {
    trim(str);
    int size = str.size();
    if (str[0] == '"' && str[size - 1] == '"') {
        str.erase(0, 1);
        str.erase(size - 2, 1);
    }
}

// parsing the string into number
double stringToNumber(string word) {
    trim(word);             // removing the spaces from both sides
    removeQuotes(word);     // removing the quotes whether such exist
    int dotCount = 0;          // counting the number of dots
    for (int i = 0; i < word.size(); ++i) {
        if (word.at(i) == '.') {
            ++dotCount;
        }
    }
    // parsing the string into a number
    if (dotCount == 0) {
        return stringToInt(word);
    } else if (dotCount == 1 && (isNumeric(word))) {
        return stringToDouble(word);
    } else {
        return 0.0;
    }
}

#endif //TABLEREADING_DATATYPES_H
