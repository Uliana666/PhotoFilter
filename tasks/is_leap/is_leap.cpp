#include "is_leap.h"

#define YEAR_CONST1 4
#define YEAR_CONST2 100

bool IsLeap(int year) {
    if (year % YEAR_CONST1 == 0 && year % YEAR_CONST2 != 0) {
        return true;
    } else {
        return year % (YEAR_CONST1 * YEAR_CONST2) == 0;
    }
}
