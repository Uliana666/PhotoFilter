#pragma once

#include <limits>
#include <cstdint>

class ColorRGB {
    float r_, g_, b_;

public:
    static constexpr uint8_t MaxColor = std::numeric_limits<uint8_t>::max();

    ColorRGB();
    ColorRGB(float r, float g, float b);
    explicit ColorRGB(float c);
    ColorRGB(uint8_t r, uint8_t g, uint8_t b);
    explicit ColorRGB(uint8_t c);

    uint8_t GetRToInt8() const;
    uint8_t GetGToInt8() const;
    uint8_t GetBToInt8() const;

    float GetR() const;
    float GetG() const;
    float GetB() const;

    ColorRGB operator+(const ColorRGB& other) const;
    ColorRGB operator+=(const ColorRGB& other);

    ColorRGB operator*(float value) const;
    ColorRGB operator*=(float value);

    bool operator==(const ColorRGB& other) const;

    bool EqualWithEps(const ColorRGB& other, float Eps) const;
};
