#pragma once

#include <cstdio>
#include <vector>

#include "../color/color_rgb.h"

class Image {
protected:
    std::vector<std::vector<ColorRGB>> data_;
    int32_t h_, w_;

public:
    Image(int32_t h, int32_t w);

    Image();

    explicit Image(const std::vector<std::vector<ColorRGB>>& data);

    void SetImage(const std::vector<std::vector<ColorRGB>>& data);
    std::vector<std::vector<ColorRGB>> GetImage() const;

    template <class T>
    void GenerateRand(int32_t n, int32_t m, T& gen) {
        std::vector<std::vector<ColorRGB>> res(n, std::vector<ColorRGB>(m));
        for (size_t i = 0; i < n; ++i) {
            for (size_t j = 0; j < m; ++j) {
                res[i][j] =
                         ColorRGB(static_cast<uint8_t>(gen() % 256), static_cast<uint8_t>(gen() % 256),
                                  static_cast<uint8_t>(gen() % 256));
            }
        }
        SetImage(res);
    }

    int32_t Width() const;
    int32_t Height() const;

    void SetPixel(size_t x, size_t y, ColorRGB c);
    ColorRGB GetPixel(size_t x, size_t y) const;

    bool EqualWithEps(const Image& other, float Eps) const;
};
