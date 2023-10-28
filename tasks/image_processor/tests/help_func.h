#pragma once

#include <string>
#include <vector>

class Console {
public:
    std::vector<char*> ptrs;
    char** GetStr(std::vector<std::string>& strings);
};
