#pragma once

#include "../../image/image.h"
#include "../filter_interface.h"

class Negative : public ConsoleFilterInterface {
public:
    Negative() = default;

    void Apply(Image& image) const override;

    const char* const* ConsumeArgs(const char* const* args) override;

    ~Negative() override = default;
};
