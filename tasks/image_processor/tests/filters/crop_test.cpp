#include "catch.hpp"

#include "filters/crop/crop.h"
#include "../help_func.h"

// NOLINTBEGIN
TEST_CASE("Crop Check Consume Arguments Correct") {
    Crop filter;
    Console console;
    const char* const* ptr;
    std::vector<std::string> a = {"10", "20"};
    REQUIRE_NOTHROW((ptr = filter.ConsumeArgs(console.GetStr(a))));
    REQUIRE(filter.GetWidth() == 10);
    REQUIRE(filter.GetHeight() == 20);
    REQUIRE(ptr == (console.ptrs.data() + 2));
    std::vector<std::string> b = {"1000000", "1", "40"};
    REQUIRE_NOTHROW((ptr = filter.ConsumeArgs(console.GetStr(b))));
    REQUIRE(filter.GetWidth() == 1000000);
    REQUIRE(filter.GetHeight() == 1);
    REQUIRE(ptr == (console.ptrs.data() + 2));
}

TEST_CASE("Crop Check Consume Arguments Incorrect") {
    Crop filter;
    Console console;
    std::vector<std::string> a = {"-10", "-20"};
    REQUIRE_THROWS(filter.ConsumeArgs(console.GetStr(a)));
    std::vector<std::string> b = {"0", "0", "40"};
    REQUIRE_THROWS(filter.ConsumeArgs(console.GetStr(b)));
    std::vector<std::string> c = {"10a", "100"};
    REQUIRE_THROWS(filter.ConsumeArgs(console.GetStr(c)));
    std::vector<std::string> d = {"10", "100.5"};
    REQUIRE_THROWS(filter.ConsumeArgs(console.GetStr(d)));
    std::vector<std::string> e = {"10"};
    REQUIRE_THROWS(filter.ConsumeArgs(console.GetStr(e)));
    std::vector<std::string> f = {};
    REQUIRE_THROWS(filter.ConsumeArgs(console.GetStr(e)));
}

TEST_CASE("Crop Check Apply") {
    Crop filter;
    Image image;
    Console console;
    std::vector<std::string> a = {"200", "1000"};
    filter.ConsumeArgs(console.GetStr(a));
    std::mt19937 gen(777);
    image.GenerateRand(251, 3950, gen);
    filter.Apply(image);
    auto res = image.GetImage();
    REQUIRE(res.size() == 251);
    for (size_t i = 0; i < res.size(); ++i) {
        REQUIRE(res[i].size() == 200);
    }
    auto data = image.GetImage();
    for (size_t i = 0; i < res.size(); ++i) {
        for (size_t j = 0; j < res[i].size(); ++j) {
            REQUIRE(res[i][j].GetR() == data[i][j].GetR());
            REQUIRE(res[i][j].GetG() == data[i][j].GetG());
            REQUIRE(res[i][j].GetB() == data[i][j].GetB());
        }
    }
}
// NOLINTEND