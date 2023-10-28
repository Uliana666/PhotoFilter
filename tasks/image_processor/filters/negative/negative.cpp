#include <limits>

#include "negative.h"
#include "../../utilities/convolution/utility_convolution.h"

void Negative::Apply(Image& image) const {
    utility::convolution::ApplyFunction(image,
                                        [](ColorRGB c) { return ColorRGB(1 - c.GetR(), 1 - c.GetG(), 1 - c.GetB()); });
}

const char* const* Negative::ConsumeArgs(const char* const* args) {
    return args;
}
