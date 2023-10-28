#include <limits>
#include <cmath>

#include "color_rgb.h"

ColorRGB::ColorRGB() : r_(0), g_(0), b_(0) {
}

ColorRGB::ColorRGB(float r, float g, float b) : r_(r), g_(g), b_(b) {
}

ColorRGB::ColorRGB(float c) : ColorRGB(c, c, c) {
}

ColorRGB::ColorRGB(uint8_t r, uint8_t g, uint8_t b) {
    r_ = static_cast<float>(r) / ColorRGB::MaxColor;
    g_ = static_cast<float>(g) / ColorRGB::MaxColor;
    b_ = static_cast<float>(b) / ColorRGB::MaxColor;
}

ColorRGB::ColorRGB(uint8_t c) : ColorRGB(c, c, c) {
}

uint8_t ColorRGB::GetRToInt8() const {
    return static_cast<uint8_t>(r_ * MaxColor);
}

uint8_t ColorRGB::GetGToInt8() const {
    return static_cast<uint8_t>(g_ * MaxColor);
}

uint8_t ColorRGB::GetBToInt8() const {
    return static_cast<uint8_t>(b_ * MaxColor);
}

float ColorRGB::GetR() const {
    return r_;
}

float ColorRGB::GetG() const {
    return g_;
}

float ColorRGB::GetB() const {
    return b_;
}

ColorRGB ColorRGB::operator+(const ColorRGB& other) const {
    return ColorRGB(r_ + other.r_, g_ + other.g_, b_ + other.b_);
}

ColorRGB ColorRGB::operator*(float value) const {
    return ColorRGB(r_ * value, g_ * value, b_ * value);
}

ColorRGB ColorRGB::operator+=(const ColorRGB& other) {
    *this = *this + other;
    return *this;
}

ColorRGB ColorRGB::operator*=(float value) {
    *this = *this * value;
    return *this;
}

bool ColorRGB::operator==(const ColorRGB& other) const {
    return r_ == other.r_ && g_ == other.g_ && b_ == other.b_;
}

bool ColorRGB::EqualWithEps(const ColorRGB& other, float Eps) const {
    return abs(r_ - other.r_) <= Eps && abs(g_ - other.g_) <= Eps && abs(b_ - other.b_) <= Eps;
}
