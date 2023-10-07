#include "provinces.h"

#include <queue>

int64_t CountPassports(const std::vector<int>& provinces) {
    std::priority_queue<int64_t, std::vector<int64_t>, std::greater<int64_t>> cur_provinces;
    for (const auto& people : provinces) {
        cur_provinces.push(people);
    }
    int64_t result = 0;
    while (cur_provinces.size() > 1) {
        int64_t best_small_province = cur_provinces.top();
        cur_provinces.pop();
        int64_t next_best_small_province = cur_provinces.top();
        cur_provinces.pop();
        int64_t new_province = best_small_province + next_best_small_province;
        result += new_province;
        cur_provinces.push(new_province);
    }
    return result;
}
