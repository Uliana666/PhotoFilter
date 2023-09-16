#include "password.h"

#include <cctype>
#include <algorithm>

const int LEN_MIN = 8, LEN_MAX = 14;
const int CODE_MIN = 33, CODE_MAX = 126;
enum TYPES : size_t { BIG_LET = 0, SMALL_LET, DIGIT, OTHER, OUT_OF_RANGE, NUMBER_OF_TYPES };

TYPES DetermineType(char symbol) {
    if (symbol < CODE_MIN || symbol > CODE_MAX) {
        return OUT_OF_RANGE;
    }
    if (isupper(symbol)) {
        return BIG_LET;
    } else if (islower(symbol)) {
        return SMALL_LET;
    } else if (isdigit(symbol)) {
        return DIGIT;
    }
    return OTHER;
}

bool ValidatePassword(const std::string& password) {
    bool used[TYPES::NUMBER_OF_TYPES] = {false};
    if (password.size() < LEN_MIN || password.size() > LEN_MAX) {
        return false;
    }
    for (size_t i = 0; i < password.size(); ++i) {
        TYPES type = DetermineType(password[i]);
        used[type] = true;
    }
    if (used[OUT_OF_RANGE]) {
        return false;
    }
    return std::count(std::begin(used), std::end(used), true) >= 3;
}
