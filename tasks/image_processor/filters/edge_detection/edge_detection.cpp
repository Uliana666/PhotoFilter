#include "edge_detection.h"
#include "../../utilities/convolution/utility_convolution.h"
#include "../grayscale/grayscale.h"

void EdgeDetection::Apply(Image& image) const {
    Grayscale gray_filter;
    gray_filter.Apply(image);
    utility::convolution::ApplyMatrixFilterWithLimit(image, {{0, -1, 0}, {-1, 4, -1}, {0, -1, 0}}, ColorRGB(0.f),
                                                     ColorRGB(1.f));
    utility::convolution::ApplyFunction(image, [this](ColorRGB c) {
        if (c.GetR() > threshold_) {
            return ColorRGB(static_cast<float>(1));
        }
        return ColorRGB(static_cast<float>(0));
    });
}

const char* const* EdgeDetection::ConsumeArgs(const char* const* args) {
    if (args[0] == nullptr) {
        throw std::invalid_argument("Edge Detection Filter: Need threshold.");
    }
    try {
        size_t pos = 0;
        threshold_ = std::stof(args[0], &pos);
        if (pos != strlen(args[0])) {
            throw std::invalid_argument("Edge Detection Filter: Not a float");
        }
    } catch (...) {
        throw std::invalid_argument("Edge Detection Filter: Not a valid float.");
    }
    if (threshold_ < 0 || threshold_ > 1) {
        throw std::invalid_argument("Edge Detection Filter: Threshold belongs to the range [0, 1]");
    }
    return (args + 1);
}
float EdgeDetection::GetThreshold() const {
    return threshold_;
}
