#include "fibonacci.h"
#include <vector>

int64_t CalculateNthFibonacci(int64_t n) {
    if (n <= 1) {
        return n;
    }
    std::vector<int64_t> dp(n + 1);
    dp[1] = 1;
    for (int i = 2; i <= n; ++i) {
        dp[i] = dp[i - 1] + dp[i - 2];
    }
    return dp[n];
}
