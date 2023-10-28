#pragma once

#include "../../image/image.h"
#include "../filter_interface.h"

class GaussianBlur : public ConsoleFilterInterface {
    float sigma_;
    int32_t size_gauss_ = 37;

public:
    GaussianBlur();

    void Apply(Image& image) const override;

    const char* const* ConsumeArgs(const char* const* args) override;

    void SetSize(int32_t size);

    ~GaussianBlur() override = default;

    float GetSigma() const;
};
