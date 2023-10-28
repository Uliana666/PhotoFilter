#include "sharpening.h"
#include "../../utilities/convolution/utility_convolution.h"

void Sharpening::Apply(Image& image) const {
    utility::convolution::ApplyMatrixFilterWithLimit(image, {{0, -1, 0}, {-1, 5, -1}, {0, -1, 0}}, ColorRGB(0.f),
                                                     ColorRGB(1.f));
}

const char* const* Sharpening::ConsumeArgs(const char* const* args) {
    return args;
}
