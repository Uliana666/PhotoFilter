#pragma once

#include "../../image/image.h"
#include "../filter_interface.h"

class Grayscale : public ConsoleFilterInterface {
public:
    Grayscale() = default;

    void Apply(Image& image) const override;

    const char* const* ConsumeArgs(const char* const* args) override;

    ~Grayscale() override = default;
};
