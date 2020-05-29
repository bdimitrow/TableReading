#ifndef TABLEREADING_STRINGUTILS_H
#define TABLEREADING_STRINGUTILS_H

#include <string>
#include <sstream>

using namespace std;

// is the string made of just digits and +-.
bool isNumeric(const string &str) {
    return str.find_first_not_of("+-0123456789.") == string::npos;
}

// converting string to int
int stringToInt(string numberString) {
    if (isNumeric(numberString)) {
        stringstream ss(numberString);
        int resultInt = 0;
        ss >> resultInt;
        return resultInt;
    }
}

// converting string to double
double stringToDouble(string numberString) {
    if (isNumeric(numberString)) {
        stringstream ss(numberString);
        double resultDouble = 0;
        ss >> resultDouble;
        return resultDouble;
    }
}

// removing the spaces from the left side of the stirng
string &ltrim(string &str) {
    const string &chars = "\t\n\v\f\r ";
    str.erase(0, str.find_first_not_of(chars));
    return str;
}

// removing the spaces from the right side of the stirng
string &rtrim(string &str) {
    const string &chars = "\t\n\v\f\r ";
    str.erase(str.find_last_not_of(chars) + 1);
    return str;
}

// removing the space from both sides of the string
string &trim(string &str) {
    const string &chars = "\t\n\v\f\r ";
    return ltrim(rtrim(str));
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
double stringToNumber(string numberString) {
    trim(numberString);             // removing the spaces from both sides
    removeQuotes(numberString);     // removing the quotes whether such exist
    int dotCount = 0;          // counting the number of dots
    for (int i = 0; i < numberString.size(); ++i) {
        if (numberString.at(i) == '.') {
            ++dotCount;
        }
    }
    // parsing the string into a number
    if (dotCount == 0) {
        return stringToInt(numberString);
    } else if (dotCount == 1 && (isNumeric(numberString))) {
        return stringToDouble(numberString);
    } else {
        return 0.0;
    }
}

// using regex to extract numbers from string(the numbers are saved as strings into a vector)
void extractNumbers(vector<string> &rowsCols, const string &str) {
    regex e(R"(\d+)");
    sregex_iterator iter(str.begin(), str.end(), e);
    sregex_iterator end;
    while (iter != end) {
        for (unsigned i = 0; i < iter->size(); ++i) {
            string number = (*iter)[i];
            rowsCols.push_back(number);
        }
        ++iter;
    }
}

vector<int> parseStringVectorToIntVector(vector<string> rowsCols) {
    vector<int> vectorOfNumbers;
    for (auto &s : rowsCols) {
        stringstream parser(s);
        int x = 0;
        parser >> x;
        vectorOfNumbers.push_back(x);
    }
    return vectorOfNumbers;
}

#endif //TABLEREADING_STRINGUTILS_H
