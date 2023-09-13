#include "reduce_fraction.h"
#include <algorithm>

int64_t ReduceFraction(int64_t numerator, int64_t denominator) {
    int64_t num_copy = numerator;
    int64_t den_copy = denominator;
    while (den_copy) {
        num_copy %= den_copy, std::swap(num_copy, den_copy);
    }
    return (numerator + denominator) / num_copy;
}
