#include "is_leap.h"

constexpr int LEAP_YEAR_DIVISOR = 4;
constexpr int NON_LEAP_YEAR_DIVISOR = 100;
constexpr int EXCEPTIONAL_LEAP_YEAR_DIVISOR = 400;

bool IsLeap(int year) {
    return (year % LEAP_YEAR_DIVISOR == 0 && year % NON_LEAP_YEAR_DIVISOR != 0) ||
           (year % (EXCEPTIONAL_LEAP_YEAR_DIVISOR) == 0);
}
