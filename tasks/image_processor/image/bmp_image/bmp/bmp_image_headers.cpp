#include <fstream>
#include <iostream>
#include <cstdio>

#include "bmp_image_headers.h"

BMPInfoHeader::BMPInfoHeader(const Image& image) {
    headerSize = bmp::SizeOfHeaderInfo;
    width = image.Width();
    height = image.Height();
    planes = 1;
    bitsPerPixel = bmp::CountBytes * 8;
    compression = 0;
    dataSize = 0;
    horizontalResolution = 0;
    verticalResolution = 0;
    colors = 0;
    importantColors = 0;
}

BMPFileHeader::BMPFileHeader(size_t size_data) {
    signature = bmp::SignatureBmp;
    fileSize = bmp::SizeOfHeaderFile + bmp::SizeOfHeaderInfo + size_data;
    reserved1 = 0;
    reserved2 = 0;
    dataOffset = bmp::SizeOfHeaderFile + bmp::SizeOfHeaderInfo;
}

void BMPFileHeader::Load(std::istream& file) {
#define FIELD(type, name) file.read(reinterpret_cast<char*>(&name), sizeof(type));
#include "fields_of_bmp_file_header.def"
}

void BMPFileHeader::Save(std::ostream& file) {
#define FIELD(type, name) file.write(reinterpret_cast<char*>(&name), sizeof(type));
#include "fields_of_bmp_file_header.def"  // NOLINT(readability-duplicate-include)
}

void BMPInfoHeader::Load(std::istream& file) {
#define FIELD(type, name) file.read(reinterpret_cast<char*>(&name), sizeof(type));
#include "fields_of_bmp_info.def"
}

void BMPInfoHeader::Save(std::ostream& file) {
#define FIELD(type, name) file.write(reinterpret_cast<char*>(&name), sizeof(type));
#include "fields_of_bmp_info.def"  // NOLINT(readability-duplicate-include)
}
