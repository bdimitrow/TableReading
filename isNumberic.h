#ifndef TABLEREADING_ISNUMBERIC_H
#define TABLEREADING_ISNUMBERIC_H

#include <string>
#include <sstream>
#include "matrix.h"
#include "formula.h"

using namespace std;

// is the string made of just digits and +-.
inline bool isNumeric(const string &str) {
    return str.find_first_not_of("+-0123456789.") == string::npos;
}


#endif //TABLEREADING_ISNUMBERIC_H
