#pragma once

#include "../../image/image.h"
#include "../filter_interface.h"

class GaussianBlur : public ConsoleFilterInterface {
    float sigma_;
    static constexpr int32_t SizeGauss = 37;

public:
    GaussianBlur();

    void Apply(Image& image) const override;

    const char* const* ConsumeArgs(const char* const* args) override;

    ~GaussianBlur() override = default;

    float GetSigma() const;
};
