#include <cmath>
#include <cstring>

#include "gaussian_blur.h"
#include "../../utilities/convolution/utility_convolution.h"

void GaussianBlur::Apply(Image& image) const {
    float distribution = static_cast<float>(2 * M_PI * sigma_ * sigma_);
    std::vector<std::vector<float>> gauss_matrix(1, std::vector<float>(SizeGauss));
    float size_mid = static_cast<float>(SizeGauss - 1) / 2;
    for (int32_t x = 0; x < SizeGauss; ++x) {
        float x0 = static_cast<float>(x);
        float power = ((x0 - size_mid) * (x0 - size_mid)) / (2 * sigma_ * sigma_);
        gauss_matrix[0][x] = static_cast<float>(1 / distribution * exp(-power));
    }
    try {
        utility::convolution::Normalize(gauss_matrix);
    } catch (...) {
        throw std::invalid_argument("Sigma module too large");
    }
    utility::convolution::ApplyMatrixFilterWithLimit(image, gauss_matrix, ColorRGB(0.f), ColorRGB(1.f));
    utility::convolution::TransposeMatrix(gauss_matrix);
    utility::convolution::ApplyMatrixFilterWithLimit(image, gauss_matrix, ColorRGB(0.f), ColorRGB(1.f));
}

const char* const* GaussianBlur::ConsumeArgs(const char* const* args) {
    if (args[0] == nullptr) {
        throw std::invalid_argument("Gaussian Blur Filter: Need sigma.");
    }
    try {
        size_t pos = 0;
        sigma_ = std::stof(args[0], &pos);
        if (pos != strlen(args[0])) {
            throw std::invalid_argument("Gaussian Blur Filter: Not a float");
        }
    } catch (...) {
        throw std::invalid_argument("Gaussian Blur Filter: Not a valid float.");
    }
    return (args + 1);
}

float GaussianBlur::GetSigma() const {
    return sigma_;
}

GaussianBlur::GaussianBlur() : sigma_(1) {
}
