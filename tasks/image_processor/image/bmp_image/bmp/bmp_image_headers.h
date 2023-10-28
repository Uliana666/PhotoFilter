#pragma once

#include <cstdio>
#include "../../image.h"

namespace bmp {
static constexpr size_t CountBytes = 3;
static constexpr size_t SizeOfHeaderFile = 14;
static constexpr size_t SizeOfHeaderInfo = 40;
static constexpr size_t SignatureBmp = 0x4D42;
}  // namespace bmp

#define FIELD(type, name) type name;

struct BMPFileHeader {
#include "fields_of_bmp_file_header.def"

    BMPFileHeader(size_t size_data);
    BMPFileHeader() = default;

    void Load(std::istream& file);
    void Save(std::ostream& file);
};

#define FIELD(type, name) type name;

struct BMPInfoHeader {
#include "fields_of_bmp_info.def"

    BMPInfoHeader(const Image& image);
    BMPInfoHeader() = default;

    void Load(std::istream& file);
    void Save(std::ostream& file);
};
