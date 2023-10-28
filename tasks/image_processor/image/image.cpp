#include <string>

#include "image.h"

Image::Image(int32_t h, int32_t w) : h_(h), w_(w) {
    if (w_ < 0 || h_ < 0) {
        throw std::invalid_argument("Image() incorrect width and height: Height and width must be greater than 0");
    }
    data_ = std::vector<std::vector<ColorRGB>>(h, std::vector<ColorRGB>(w));
}

Image::Image() : h_(0), w_(0) {
}

void Image::SetPixel(size_t x, size_t y, ColorRGB c) {
    if (x >= h_ || y >= w_) {
        throw std::invalid_argument("Set incorrect pixel position: " + std::to_string(x) + " " + std::to_string(y));
    }
    data_[x][y] = c;
}

int32_t Image::Width() const {
    return w_;
}

int32_t Image::Height() const {
    return h_;
}

ColorRGB Image::GetPixel(size_t x, size_t y) const {
    if (x >= h_ || y >= w_) {
        throw std::invalid_argument("Get incorrect pixel position: " + std::to_string(x) + " " + std::to_string(y));
    }
    return data_[x][y];
}

void Image::SetImage(const std::vector<std::vector<ColorRGB>>& data) {
    data_ = data;
    h_ = data_.size();
    w_ = 0;
    if (!data.empty()) {
        w_ = data[0].size();
    }
}

std::vector<std::vector<ColorRGB>> Image::GetImage() const {
    return data_;
}

Image::Image(const std::vector<std::vector<ColorRGB>>& data) {
    SetImage(data);
}

bool Image::EqualWithEps(const Image& other, float Eps) const {
    if (Width() != other.Width() || Height() != other.Height()) {
        return false;
    }
    for (size_t i = 0; i < Height(); ++i) {
        for (size_t j = 0; j < Width(); ++j) {
            if (!GetPixel(i, j).EqualWithEps(other.GetPixel(i, j), Eps)) {
                return false;
            }
        }
    }
    return true;
}
