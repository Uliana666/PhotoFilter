#include "password.h"
#include <cctype>

struct LEN {
    enum : int { MIN = 8, MAX = 14 };
};

struct CODE {
    enum : int { MIN = 33, MAX = 126 };
};

struct TYPES {
    enum : int { BIG_LET = 0, SMALL_LET, DIGIT, OTHER, NUMBER_OF_TYPES };
};

bool ValidatePassword(const std::string& password) {
    bool used[TYPES::NUMBER_OF_TYPES] = {false};
    if (password.size() < LEN::MIN || password.size() > LEN::MAX) {
        return false;
    }
    for (size_t i = 0; i < password.size(); ++i) {
        if (password[i] < CODE::MIN || password[i] > CODE::MAX) {
            return false;
        }
        if (isupper(password[i])) {
            used[TYPES::BIG_LET] = true;
        } else if (islower(password[i])) {
            used[TYPES::SMALL_LET] = true;
        } else if (isdigit(password[i])) {
            used[TYPES::DIGIT] = true;
        } else {
            used[TYPES::OTHER] = true;
        }
    }
    size_t count = 0;
    for (size_t i = 0; i < TYPES::NUMBER_OF_TYPES; ++i) {
        count += used[i];
    }
    return count >= 3;
}
