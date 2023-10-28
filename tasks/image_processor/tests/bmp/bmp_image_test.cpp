#include <catch.hpp>

#include "image/bmp_image/bmp_image_parser.h"
#include "image/bmp_image/bmp/bmp_image_headers.h"
#include <sstream>

TEST_CASE("Test Correct data 2 * 2") {
    std::mt19937 gen;
    int32_t n = 2;
    int32_t m = 2;
    Image image(m, n);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            image.SetPixel(i, j, ColorRGB((uint8_t)(gen() % 256), (uint8_t)(gen() % 256), (uint8_t)(gen() % 256)));
        }
    }
    std::stringstream s;
    BmpImageSaver save;
    BmpImageParser parse;
    REQUIRE_NOTHROW(save.Save(image, s));
    Image result;
    REQUIRE_NOTHROW(parse.Load(result, s));
    REQUIRE(image.Width() == result.Width());
    REQUIRE(image.Height() == result.Height());
    for (size_t i = 0; i < image.Height(); ++i) {
        for (size_t j = 0; j < image.Width(); ++j) {
            REQUIRE(image.GetPixel(i, j).EqualWithEps(result.GetPixel(i, j), 0.0001));
        }
    }
}

TEST_CASE("Test Correct data 3 * 7") {
    std::mt19937 gen;
    int32_t n = 3;
    int32_t m = 7;
    Image image(n, m);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            image.SetPixel(i, j, ColorRGB((uint8_t)(gen() % 256), (uint8_t)(gen() % 256), (uint8_t)(gen() % 256)));
        }
    }
    std::stringstream s;
    BmpImageSaver save;
    BmpImageParser parse;
    REQUIRE_NOTHROW(save.Save(image, s));
    Image result;
    REQUIRE_NOTHROW(parse.Load(result, s));
    REQUIRE(image.Width() == result.Width());
    REQUIRE(image.Height() == result.Height());
    for (size_t i = 0; i < image.Height(); ++i) {
        for (size_t j = 0; j < image.Width(); ++j) {
            REQUIRE(image.GetPixel(i, j).EqualWithEps(result.GetPixel(i, j), 0.0001));
        }
    }
}
TEST_CASE("Test Correct data 32 * 64") {
    std::mt19937 gen;
    int32_t n = 32;
    int32_t m = 64;
    Image image(n, m);
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < m; ++j) {
            image.SetPixel(i, j, ColorRGB((uint8_t)(gen() % 256), (uint8_t)(gen() % 256), (uint8_t)(gen() % 256)));
        }
    }
    std::stringstream s;
    BmpImageSaver save;
    BmpImageParser parse;
    REQUIRE_NOTHROW(save.Save(image, s));
    Image result;
    REQUIRE_NOTHROW(parse.Load(result, s));
    REQUIRE(image.Width() == result.Width());
    REQUIRE(image.Height() == result.Height());
    for (size_t i = 0; i < image.Height(); ++i) {
        for (size_t j = 0; j < image.Width(); ++j) {
            REQUIRE(image.GetPixel(i, j).EqualWithEps(result.GetPixel(i, j), 0.0001));
        }
    }
}

TEST_CASE("Test FromPath") {
    BmpImageParser tool;
    BmpImageSaver saver;
    Image image;

    REQUIRE_THROWS(tool.LoadFromPath(image, "../tasks/image_processor/tests/bmp/battered_img.bmp"));
    REQUIRE_THROWS(tool.LoadFromPath(image, "../tasks/image_processor/tests/bmp/incorrect.bmp"));
    REQUIRE_THROWS(tool.LoadFromPath(image, "../tasks/image_processor/tests/bmp/jpg_file.bmp"));
    REQUIRE_THROWS(tool.LoadFromPath(image, "../tasks/image_processor/tests/bmp/not_exist.bmp"));

    REQUIRE_NOTHROW(tool.LoadFromPath(image, "../tasks/image_processor/tests/bmp/correct.bmp"));
    REQUIRE_NOTHROW(saver.SaveFromPath(image, "../tasks/image_processor/tests/bmp/correct_copy.bmp"));
    Image result;
    REQUIRE_NOTHROW(tool.LoadFromPath(result, "../tasks/image_processor/tests/bmp/correct_copy.bmp"));
    REQUIRE(image.Width() == result.Width());
    REQUIRE(image.Height() == result.Height());
    for (size_t i = 0; i < image.Height(); ++i) {
        for (size_t j = 0; j < image.Width(); ++j) {
            REQUIRE(image.GetPixel(i, j).EqualWithEps(result.GetPixel(i, j), 0.0001));
        }
    }
}