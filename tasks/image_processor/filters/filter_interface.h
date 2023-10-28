#pragma once

#include <unordered_map>
#include <memory>
#include <string>

#include "../image/image.h"

class FilterInterface {

public:
    virtual void Apply(Image& image) const = 0;

    virtual ~FilterInterface() = default;
};

class ConsoleFilterInterface : public FilterInterface {

public:
    virtual const char* const* ConsumeArgs(const char* const* args) = 0;
};
