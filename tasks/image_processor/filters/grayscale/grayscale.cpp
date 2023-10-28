#include "grayscale.h"
#include "../../utilities/convolution/utility_convolution.h"

void Grayscale::Apply(Image& image) const {
    utility::convolution::ApplyFunction(
        image, [](ColorRGB c) { return ColorRGB(c.GetR() * 0.299f + c.GetG() * 0.587f + c.GetB() * 0.114f); });
}

const char* const* Grayscale::ConsumeArgs(const char* const* args) {
    return args;
}
