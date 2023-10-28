#pragma once

#include <cstring>

#include "../../image/image.h"
#include "../filter_interface.h"

class EdgeDetection : public ConsoleFilterInterface {
    float threshold_;

public:
    EdgeDetection() = default;

    void Apply(Image& image) const override;

    const char* const* ConsumeArgs(const char* const* args) override;

    ~EdgeDetection() override = default;

    float GetThreshold() const;
};
