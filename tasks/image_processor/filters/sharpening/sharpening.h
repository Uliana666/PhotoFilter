#pragma once

#include "../../image/image.h"
#include "../filter_interface.h"

class Sharpening : public ConsoleFilterInterface {
public:
    Sharpening() = default;

    void Apply(Image& image) const override;

    const char* const* ConsumeArgs(const char* const* args) override;

    ~Sharpening() override = default;
};
