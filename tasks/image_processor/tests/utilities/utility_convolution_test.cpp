#include "catch.hpp"

#include "utilities/convolution/utility_convolution.h"
#include <iostream>

// NOLINTBEGIN
TEST_CASE("Test ApplyMatrixFilter, Correct small data") {
    std::mt19937 gen;
    Image image;
    image.GenerateRand(2, 2, gen);
    std::vector<std::vector<float>> filter = {{1}, {4}, {7}};
    utility::convolution::ApplyMatrixFilter(image, filter);
    std::vector<std::vector<ColorRGB>> ans = {
        {
            ColorRGB(1.94118f, 11, 9.77255),
            ColorRGB(3.55294f, 3.58039, 5.38824),
        },
        {
            ColorRGB(0.576471f, 10.6706, 8.95686),
            ColorRGB(2.32941f, 4.44314, 2.47059),
        },
    };
    REQUIRE(image.EqualWithEps(Image(ans), 0.001));
}

TEST_CASE("Test ApplyMatrixFilter, Correct data, big data") {
    std::mt19937 gen;
    Image image;
    image.GenerateRand(7, 15, gen);
    std::vector<std::vector<float>> filter = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};
    utility::convolution::ApplyMatrixFilter(image, filter);
    auto res = image.GetImage();
    std::vector<std::vector<ColorRGB>> ans = {
        {
            ColorRGB(16.2824f, 22.0118, 28.1529),
            ColorRGB(17.4784f, 28.0549, 32.8824),
            ColorRGB(16.8392f, 22.1255, 25.4118),
            ColorRGB(22.1804f, 17.1686, 22.8863),
            ColorRGB(20.0627f, 15.8863, 23.3569),
            ColorRGB(18.1726f, 25.1725, 29.9451),
            ColorRGB(12.9765f, 29.2039, 27.5804),
            ColorRGB(20.3255f, 27.7726, 22.5804),
            ColorRGB(25.6353f, 20.5647, 18.2275),
            ColorRGB(34.9569f, 21.4078, 14.1961),
            ColorRGB(28.698f, 19.2235, 16.2824),
            ColorRGB(20.6431f, 24.4784, 16.8039),
            ColorRGB(17.6275f, 17.6235, 23.098),
            ColorRGB(22.2431f, 15.2549, 28.9843),
            ColorRGB(28.3804f, 10.302, 36.5059),
        },
        {
            ColorRGB(9.77647f, 32.7294, 30.4588),
            ColorRGB(19.7529f, 30.3922, 29.7333),
            ColorRGB(22.1255f, 22.6863, 19.7373),
            ColorRGB(27.5725f, 16.1216, 21.1726),
            ColorRGB(22.4941f, 13.9686, 17.9137),
            ColorRGB(23.5333f, 17.2039, 22.4706),
            ColorRGB(23.5725f, 20.5255, 25.0784),
            ColorRGB(29.9059f, 24.051, 25.6),
            ColorRGB(32.9725f, 21.1882, 24.4235),
            ColorRGB(36.0118f, 20.0824, 21.1961),
            ColorRGB(26.2314f, 19.2078, 19.2275),
            ColorRGB(16.1961f, 20.9098, 16.9059),
            ColorRGB(14.9451f, 17.0627, 19.6863),
            ColorRGB(17.9569f, 12.7725, 22.5961),
            ColorRGB(21.2588f, 9.95686, 25.2941),
        },
        {
            ColorRGB(9.8f, 32.7294, 22.8),
            ColorRGB(19.0078f, 23.8824, 26.6275),
            ColorRGB(22.3843f, 16.2431, 19.6275),
            ColorRGB(27.4431f, 15.0118, 15.7961),
            ColorRGB(23.0157f, 20.4235, 16.6824),
            ColorRGB(23.3529f, 17.9529, 18.251),
            ColorRGB(22.3843f, 15.7529, 20.5137),
            ColorRGB(26.9412f, 17.5725, 17.5216),
            ColorRGB(27.4549f, 15.8667, 16.5216),
            ColorRGB(29.102f, 19.7098, 18.3922),
            ColorRGB(21.2353f, 17.0431, 22.8353),
            ColorRGB(16.8471f, 23.4353, 20.8235),
            ColorRGB(18.9961f, 20.6078, 18.3529),
            ColorRGB(24.1216f, 17.8549, 20.5804),
            ColorRGB(26.7176f, 13.3765, 25.9176),
        },
        {
            ColorRGB(18.8471f, 26.8235, 24.5882),
            ColorRGB(24.3216f, 21.9294, 27.6314),
            ColorRGB(20.8549f, 18.4471, 23.7451),
            ColorRGB(24.9686f, 20.051, 19.2667),
            ColorRGB(15.8157f, 22.9765, 17.1804),
            ColorRGB(18.1765f, 20.8157, 16.2902),
            ColorRGB(21.349f, 18.4784, 20.8706),
            ColorRGB(29.4588f, 16.4824, 20.2314),
            ColorRGB(32.4941f, 16.3294, 22.6588),
            ColorRGB(26.5333f, 17.9176, 19.5765),
            ColorRGB(19.0549f, 16.6314, 21.2588),
            ColorRGB(15.9059f, 17.5294, 21.6118),
            ColorRGB(22.5137f, 21.1647, 22.5647),
            ColorRGB(24.0314f, 23.6275, 19),
            ColorRGB(23.4667f, 24.2275, 15.7294),
        },
        {
            ColorRGB(27.7412f, 19.4941, 26.1176),
            ColorRGB(29.5451f, 18.898, 27.0353),
            ColorRGB(23.5451f, 17.7373, 27.098),
            ColorRGB(25.0353f, 22.2902, 18.8353),
            ColorRGB(19.8196f, 25.1882, 22.2706),
            ColorRGB(22.251f, 24.8706, 24.2),
            ColorRGB(20.4039f, 16.7373, 29.4),
            ColorRGB(25.9765f, 18.4745, 28.6549),
            ColorRGB(27.6078f, 18.6784, 29.2431),
            ColorRGB(20.9333f, 25.3294, 26.2431),
            ColorRGB(18.0627f, 20.9294, 30.0941),
            ColorRGB(19.2157f, 20.5255, 24.4039),
            ColorRGB(28.6196f, 19.2549, 23.0667),
            ColorRGB(26.102f, 26.5098, 21.9647),
            ColorRGB(22.6784f, 32.1686, 25.1726),
        },
        {
            ColorRGB(21.7882f, 14.9647, 19.8824),
            ColorRGB(22.4549f, 15.3255, 26.6157),
            ColorRGB(23.4745f, 14.2863, 25.9098),
            ColorRGB(24.502f, 16.8353, 24.9725),
            ColorRGB(26.6549f, 19.2118, 19.5412),
            ColorRGB(22.1882f, 19.498, 25.4118),
            ColorRGB(22.8078f, 14.4627, 25.8627),
            ColorRGB(22.f, 12.2392, 30.1843),
            ColorRGB(20.1608f, 13.8941, 33.9725),
            ColorRGB(17.6039f, 23.5765, 26.1725),
            ColorRGB(17.1137f, 21.2471, 30.0431),
            ColorRGB(25.2667f, 22.7608, 28.0353),
            ColorRGB(30.2745f, 16.6275, 31.9137),
            ColorRGB(27.7961f, 19.8902, 30.2706),
            ColorRGB(22.4627f, 19.2392, 31.6471),
        },
        {
            ColorRGB(17.1765f, 13.3529, 16.1529),
            ColorRGB(16.7216f, 12.5765, 26.7686),
            ColorRGB(23.0471f, 11.251, 23.5765),
            ColorRGB(24.9569f, 13.4275, 28.6471),
            ColorRGB(30.8902f, 15.9569, 17.9373),
            ColorRGB(21.3726f, 15.1333, 24.7255),
            ColorRGB(23.4235f, 12.651, 21.6),
            ColorRGB(18.9333f, 8.21961, 29.098),
            ColorRGB(14.7333f, 9.8902, 34.6941),
            ColorRGB(16.9059f, 22.1059, 25.0353),
            ColorRGB(17.2039f, 21.0706, 29.9294),
            ColorRGB(28.5373f, 24.2784, 29.6039),
            ColorRGB(30.7765f, 15.2353, 36.5529),
            ColorRGB(29.2196f, 14.6784, 36.2863),
            ColorRGB(23.4f, 9.57647, 36.3216),
        },
    };
    REQUIRE(image.EqualWithEps(Image(ans), 0.001));
}

TEST_CASE("Test ApplyMatrixFilter, Incorrect data") {
    std::mt19937 gen;
    Image image(2, 2);
    std::vector<std::vector<float>> filter = {};
    REQUIRE_THROWS(utility::convolution::ApplyMatrixFilter(image, filter));
    filter.resize(4);
    REQUIRE_THROWS(utility::convolution::ApplyMatrixFilter(image, filter));
    filter.resize(5);
    REQUIRE_THROWS(utility::convolution::ApplyMatrixFilter(image, filter));
    filter[0].resize(1);
    REQUIRE_THROWS(utility::convolution::ApplyMatrixFilter(image, filter));
    for (size_t i = 0; i < filter.size(); ++i) {
        filter[i].resize(1);
    }
    REQUIRE_NOTHROW((utility::convolution::ApplyMatrixFilter(image, filter)));
}

TEST_CASE("Test ApplyFunction") {
    std::mt19937 gen;
    Image image(2, 2);
    image.GenerateRand(2, 2, gen);
    utility::convolution::ApplyFunction(image,
                                        [](ColorRGB c) { return ColorRGB(c.GetB() * 2, c.GetR(), c.GetG() / 2); });
    auto res = image.GetImage();
    std::vector<std::vector<ColorRGB>> ans = {{
                                                  ColorRGB(1.86667f, 0.360784, 0.482353),
                                                  ColorRGB(1.74902f, 0.47451, 0.0862745),
                                              },
                                              {
                                                  ColorRGB(1.45882f, 0.0196078, 0.441176),
                                                  ColorRGB(0.290196f, 0.168627, 0.194118),
                                              }};
    REQUIRE(image.EqualWithEps(Image(ans), 0.001));
}

TEST_CASE("Test TransposeMatrix, Correct data") {
    std::mt19937 gen;
    std::vector<std::vector<float>> data(2, std::vector<float>(6));
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 6; ++j) {
            data[i][j] = (float)(gen()) / 13322422123.f;
        }
    }
    utility::convolution::TransposeMatrix(data);
    std::vector<std::vector<float>> ans = {
        {
            0.262656,
            0.29446,
        },
        {
            0.0436759,
            0.0712584,
        },
        {
            0.292015,
            0.203864,
        },
        {
            0.269195,
            0.0993489,
        },
        {
            0.0409388,
            0.0314457,
        },
        {
            0.31235,
            0.176416,
        },
    };
    for (size_t i = 0; i < 6; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            REQUIRE(fabs(data[i][j] - ans[i][j]) <= 0.001);
        }
    }
}

TEST_CASE("Test TransposeMatrix, Incorrect data") {
    std::vector<std::vector<float>> data;
    REQUIRE_NOTHROW(utility::convolution::TransposeMatrix(data));
    data.resize(3);
    REQUIRE_THROWS(utility::convolution::TransposeMatrix(data));
    data[0].resize(1);
    REQUIRE_THROWS(utility::convolution::TransposeMatrix(data));
    for (size_t i = 0; i < data.size(); ++i) {
        data[i].resize(1);
    }
    REQUIRE_NOTHROW(utility::convolution::TransposeMatrix(data));
}

TEST_CASE("Test Normalize") {
    std::vector<std::vector<float>> data = {{1, 2, 3}, {4, 5}};
    utility::convolution::Normalize(data);
    std::vector<std::vector<float>> ans = {
        {
            0.0666667,
            0.133333,
            0.2,
        },
        {
            0.266667,
            0.333333,
        },
    };
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < data[i].size(); ++j) {
            REQUIRE(fabs(data[i][j] - ans[i][j]) <= 0.001);
        }
    }
    std::vector<std::vector<float>> a, b(3), c = {{1, 3, -1}, {-3}};
    REQUIRE_THROWS(utility::convolution::Normalize(a));
    REQUIRE_THROWS(utility::convolution::Normalize(b));
    REQUIRE_THROWS(utility::convolution::Normalize(c));
}
// NOLINTEND