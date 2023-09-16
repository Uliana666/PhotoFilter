#include "is_leap.h"

constexpr int LeapYearDivisor = 4;
constexpr int NonLeapYearDivisor = 100;
constexpr int ExceptionalLeapYearDivisor = 400;

bool IsLeap(int year) {
    return (year % LeapYearDivisor == 0 && year % NonLeapYearDivisor != 0) ||
           (year % (ExceptionalLeapYearDivisor) == 0);
}
