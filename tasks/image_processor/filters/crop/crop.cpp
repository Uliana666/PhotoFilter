#include <cstring>

#include "crop.h"

void Crop::Apply(Image& image) const {
    std::vector<std::vector<ColorRGB>> data = image.GetImage();
    data.resize(std::min(height_, image.Height()));
    for (size_t i = 0; i < data.size(); ++i) {
        data[i].resize(std::min(image.Width(), width_));
    }
    image.SetImage(data);
}

const char* const* Crop::ConsumeArgs(const char* const* args) {
    if (args[0] == nullptr || args[1] == nullptr) {
        throw std::invalid_argument("Crop Filter: Need width and height.");
    }
    size_t pos0 = 0;
    size_t pos1 = 0;
    width_ = std::stoi(args[0], &pos0);
    height_ = std::stoi(args[1], &pos1);
    if (width_ <= 0 || height_ <= 0 || pos0 != strlen(args[0]) || pos1 != strlen(args[1])) {
        throw std::invalid_argument("Crop Filter: Height and width is integer and cannot be less than 1.");
    }
    return (args + 2);
}

int32_t Crop::GetWidth() const {
    return width_;
}

int32_t Crop::GetHeight() const {
    return height_;
}
