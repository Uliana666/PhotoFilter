#pragma once

#include "../../image/image.h"
#include "../filter_interface.h"

class Crop : public ConsoleFilterInterface {
    int32_t width_, height_;

public:
    Crop() = default;

    void Apply(Image& image) const override;

    const char* const* ConsumeArgs(const char* const* args) override;

    int32_t GetWidth() const;
    int32_t GetHeight() const;

    ~Crop() override = default;
};
