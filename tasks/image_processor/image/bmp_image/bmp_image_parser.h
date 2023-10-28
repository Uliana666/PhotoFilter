#pragma once

#include <string>
#include <cstdint>

#include "../image.h"

class BmpImageParser {
public:
    Image ConvertRawDataToImage(int32_t width, int32_t height, std::vector<uint8_t> data) const;

    void Load(Image& image, std::istream& in) const;

    void LoadFromPath(Image& image, const std::string& path) const;
};

class BmpImageSaver {
public:
    std::vector<uint8_t> ConvertImageToRawData(const Image& image) const;

    void Save(const Image& image, std::ostream& out) const;

    void SaveFromPath(Image& image, const std::string& path) const;
};
