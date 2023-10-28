#include <catch.hpp>

#include "../image/image.h"

TEST_CASE("Image Correct Data") {
    Image image;
    std::vector<std::vector<ColorRGB>> data(10, std::vector<ColorRGB>(20, ColorRGB(0.f)));
    image.SetImage(data);

    REQUIRE(image.Width() == 20);
    REQUIRE(image.Height() == 10);

    REQUIRE_NOTHROW(image.SetPixel(0, 7, ColorRGB(1.f)));
    REQUIRE_NOTHROW(image.SetPixel(9, 19, ColorRGB(1.f)));

    REQUIRE_NOTHROW(image.GetPixel(0, 7));
    REQUIRE(image.GetPixel(0, 7) == ColorRGB(1.f));
    REQUIRE_NOTHROW(image.GetPixel(2, 19));
    REQUIRE(image.GetPixel(2, 19) == ColorRGB(0.f));
}

TEST_CASE("Image InCorrect Data") {
    REQUIRE_THROWS(Image(0, -1));
    REQUIRE_THROWS(Image(-100, 0));
    auto image = Image(10, 10);
    REQUIRE_THROWS(image.SetPixel(-1, 7, ColorRGB(1.f)));
    REQUIRE_THROWS(image.SetPixel(5, 100, ColorRGB(1.f)));

    REQUIRE_THROWS(image.GetPixel(-10, 9));
    REQUIRE_THROWS(image.GetPixel(9, 100));
}