#include "palindrome.h"

bool IsPalindrome(const std::string& str) {
    size_t l = 0;
    size_t r = str.size() - 1;
    while (r > l) {
        while (str[l] == ' ' && l < str.size()) {
            l++;
        }
        if (l == str.size()) {
            return true;
        }
        while (str[r] == ' ') {
            r--;
        }
        if (str[r] != str[l]) {
            return false;
        }
        l++;
        r--;
    }
    return true;
}
