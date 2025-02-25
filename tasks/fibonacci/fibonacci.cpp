#include "fibonacci.h"

int64_t CalculateNthFibonacci(int64_t n) {
    if (n <= 1) {
        return n;
    }
    int64_t fibonacci0 = 0;
    int64_t fibonacci1 = 1;
    for (int64_t i = 2; i <= n; ++i) {
        int64_t fibonacci2 = fibonacci0 + fibonacci1;
        fibonacci0 = fibonacci1;
        fibonacci1 = fibonacci2;
    }
    return fibonacci1;
}
