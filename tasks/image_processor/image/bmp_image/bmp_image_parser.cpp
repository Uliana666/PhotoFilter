#include <fstream>
#include <iostream>
#include <cstdio>

#include "bmp_image_parser.h"
#include "bmp/bmp_image_headers.h"

void BmpImageParser::Load(Image& image, std::istream& in) const {
    BMPFileHeader file_header;
    BMPInfoHeader info_header;

    file_header.Load(in);
    info_header.Load(in);

    if (!in.good()) {
        throw std::runtime_error("Bad istream");
    }

    if (file_header.signature != bmp::SignatureBmp) {
        throw std::invalid_argument("File is not bmp_file");
    }

    if (info_header.bitsPerPixel != bmp::CountBytes * bmp::CountBitInBytes || info_header.compression != 0) {
        throw std::invalid_argument("This class only supports 24-bit uncompressed BMP images\nbitCount: " +
                                    std::to_string(info_header.bitsPerPixel) +
                                    "\ncompression: " + std::to_string(info_header.compression));
    }
    std::vector<uint8_t> image_buffer(file_header.fileSize - file_header.dataOffset);

    in.read(reinterpret_cast<char*>(image_buffer.data()), static_cast<int64_t>(image_buffer.size()));
    if (!in.good() || in.eof()) {
        throw std::runtime_error("Bad istream");
    }
    image = ConvertRawDataToImage(info_header.width, info_header.height, image_buffer);
}

void BmpImageSaver::Save(const Image& image, std::ostream& out) const {
    std::vector<uint8_t> image_buffer = ConvertImageToRawData(image);
    BMPFileHeader file_header(image_buffer.size());
    BMPInfoHeader info_header(image);

    file_header.Save(out);
    info_header.Save(out);
    out.write(reinterpret_cast<char*>(image_buffer.data()), static_cast<int64_t>(image_buffer.size()));

    if (!out.good()) {
        throw std::runtime_error("Bad ostream");
    }
}

Image BmpImageParser::ConvertRawDataToImage(int32_t width, int32_t height, std::vector<uint8_t> data) const {
    int32_t alignment = (4 - (width * 3 % 4)) % 4;
    if (data.size() != height * (width * 3 + alignment)) {
        throw std::invalid_argument("Incorrect data size");
    }
    Image image = Image(height, width);
    size_t cur_x = 0;
    size_t cur_y = 0;
    for (size_t i = 2; i < data.size(); i += 3) {
        ColorRGB color(data[i], data[i - 1], data[i - 2]);
        image.SetPixel(height - cur_x - 1, cur_y, color);
        cur_y++;
        if (cur_y == width) {
            ++cur_x;
            cur_y = 0;
            i += alignment;
        }
    }
    return image;
}

std::vector<uint8_t> BmpImageSaver::ConvertImageToRawData(const Image& image) const {
    std::vector<uint8_t> data;
    for (size_t x = 0; x < image.Height(); ++x) {
        for (size_t y = 0; y < image.Width(); ++y) {
            ColorRGB color = image.GetPixel(image.Height() - x - 1, y);
            data.push_back(color.GetBToInt8());
            data.push_back(color.GetGToInt8());
            data.push_back(color.GetRToInt8());
        }
        while (data.size() % 4 != 0) {
            data.push_back(0);
        }
    }
    return data;
}

void BmpImageParser::LoadFromPath(Image& image, const std::string& path) const {
    std::ifstream file(path, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file");
    }
    try {
        Load(image, file);
        file.close();
    } catch (std::runtime_error e) {
        throw std::runtime_error("Error reading file");
    }
}

void BmpImageSaver::SaveFromPath(Image& image, const std::string& path) const {
    std::ofstream file(path, std::ios::binary);
    if (!file.is_open()) {
        throw std::runtime_error("Error opening file");
    }
    try {
        Save(image, file);
        file.close();
    } catch (std::runtime_error e) {
        throw std::runtime_error("Error writing file");
    }
}
