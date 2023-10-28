#pragma once

#include "../filter_interface.h"

class Cluster : public ConsoleFilterInterface {
    int32_t count_colors_;

public:
    Cluster();

    void Apply(Image& image) const override;

    const char* const* ConsumeArgs(const char* const* args) override;

    ~Cluster() override = default;

    int32_t GetCountColors() const;
};
