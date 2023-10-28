#include "utility_convolution.h"

void utility::convolution::ApplyMatrixFilter(Image& image, const std::vector<std::vector<float>>& convolution) {
    std::vector<std::vector<ColorRGB>> result(image.Height(), std::vector<ColorRGB>(image.Width()));
    if (convolution.size() % 2 == 0 || convolution[0].size() % 2 == 0) {
        throw std::invalid_argument("Convolution must have odd sizes");
    }
    for (size_t i = 0; i < convolution.size(); ++i) {
        if (convolution[i].size() != convolution[0].size()) {
            throw std::invalid_argument("Convolution is matrix n * m");
        }
    }
    int32_t n = static_cast<int32_t>(convolution.size());
    int32_t m = static_cast<int32_t>(convolution[0].size());
    int32_t mid_n = n / 2;
    int32_t mid_m = m / 2;
    for (int32_t x = 0; x < image.Height(); ++x) {
        for (int32_t y = 0; y < image.Width(); ++y) {
            ColorRGB c;
            for (int32_t k = -mid_n; k <= mid_n; ++k) {
                for (int32_t t = -mid_m; t <= mid_m; ++t) {
                    size_t x0 = std::max(0, std::min(image.Height() - 1, x + k));
                    size_t y0 = std::max(0, std::min(image.Width() - 1, y + t));
                    c += image.GetPixel(x0, y0) * convolution[k + mid_n][t + mid_m];
                }
            }
            result[x][y] = c;
        }
    }
    image.SetImage(result);
}

void utility::convolution::MaxEqual(Image& image, ColorRGB value) {
    ApplyFunction(image, [value](ColorRGB c) {
        return ColorRGB(std::max(value.GetR(), c.GetR()), std::max(value.GetG(), c.GetG()),
                        std::max(value.GetB(), c.GetB()));
    });
}

void utility::convolution::MinEqual(Image& image, ColorRGB value) {
    ApplyFunction(image, [value](ColorRGB c) {
        return ColorRGB(std::min(value.GetR(), c.GetR()), std::min(value.GetG(), c.GetG()),
                        std::min(value.GetB(), c.GetB()));
    });
}

void utility::convolution::Transpose(Image& image) {
    std::vector<std::vector<ColorRGB>> data_image = image.GetImage();
    TransposeMatrix(data_image);
    image.SetImage(data_image);
}

void utility::convolution::Normalize(std::vector<std::vector<float>>& convolution) {
    float sum = 0;
    for (size_t x = 0; x < convolution.size(); ++x) {
        for (size_t y = 0; y < convolution[x].size(); ++y) {
            sum += convolution[x][y];
        }
    }
    if (sum == 0) {
        throw std::invalid_argument("Sum convolution is equal 0");
    }
    float k = 1 / sum;
    for (size_t x = 0; x < convolution.size(); ++x) {
        for (size_t y = 0; y < convolution[x].size(); ++y) {
            convolution[x][y] *= k;
        }
    }
}

void utility::convolution::ApplyMatrixFilterWithLimit(Image& image, const std::vector<std::vector<float>>& convolution,
                                                      ColorRGB min, ColorRGB max) {
    ApplyMatrixFilter(image, convolution);
    MinEqual(image, max);
    MaxEqual(image, min);
}
