#include "password.h"

#include <cctype>
#include <algorithm>

constexpr size_t LEN_MIN = 8;   // NOLINT
constexpr size_t LEN_MAX = 14;  // NOLINT
constexpr int CODE_MIN = 33;    // NOLINT
constexpr int CODE_MAX = 126;   // NOLINT
enum TYPES {                    // NOLINT
    BIG_LET,                    // NOLINT
    SMALL_LET,                  // NOLINT
    DIGIT,                      // NOLINT
    OTHER,                      // NOLINT
    OUT_OF_RANGE,               // NOLINT
    NUMBER_OF_TYPES             // NOLINT
};

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
