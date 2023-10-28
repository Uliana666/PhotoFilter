#pragma once

#include <string>

class Console {
public:
    std::vector<char*> ptrs;
    char** GetStr(std::vector<std::string>& strings);
};
