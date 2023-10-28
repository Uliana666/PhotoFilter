#pragma once

#include "../../image/image.h"

namespace utility::convolution {

void ApplyMatrixFilter(Image& image, const std::vector<std::vector<float>>& convolution);

void ApplyMatrixFilterWithLimit(Image& image, const std::vector<std::vector<float>>& convolution, ColorRGB min,
                                ColorRGB max);

void MaxEqual(Image& image, ColorRGB value);

void MinEqual(Image& image, ColorRGB value);

template <class T>
void TransposeMatrix(std::vector<std::vector<T>>& convolution) {
    if (convolution.empty()) {
        return;
    }
    if (convolution[0].empty()) {
        throw std::invalid_argument("If one dimension is not zero, then the second one is too");
    }
    for (size_t i = 0; i < convolution.size(); ++i) {
        if (convolution[i].size() != convolution[0].size()) {
            throw std::invalid_argument("Need matrix n * m");
        }
    }
    std::vector<std::vector<T>> res(convolution[0].size(), std::vector<T>(convolution.size()));
    for (size_t x = 0; x < convolution.size(); ++x) {
        for (size_t y = 0; y < convolution[x].size(); ++y) {
            res[y][x] = convolution[x][y];
        }
    }
    convolution = res;
}

void Transpose(Image& image);

template <class F>
void ApplyFunction(Image& image, F func) {
    for (int x = 0; x < image.Height(); ++x) {
        for (int y = 0; y < image.Width(); ++y) {
            image.SetPixel(x, y, func(image.GetPixel(x, y)));
        }
    }
}

void Normalize(std::vector<std::vector<float>>& convolution);

}  // namespace utility::convolution
