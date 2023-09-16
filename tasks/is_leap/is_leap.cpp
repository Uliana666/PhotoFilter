#include "is_leap.h"

const int YEAR_CONST1 = 4;
const int YEAR_CONST2 = 100;
const int CONST1_CONST2 = 400;

bool IsLeap(int year) {
    if (year % YEAR_CONST1 == 0 && year % YEAR_CONST2 != 0) {
        return true;
    } else {
        return year % (CONST1_CONST2) == 0;
    }
}
