#include "help_func.h"

char** Console::GetStr(std::vector<std::string>& strings) {
    ptrs.clear();
    for (auto& x : strings) {
        ptrs.push_back(x.data());
    }
    ptrs.push_back(NULL);
    return ptrs.data();
}
