#include "catch.hpp"

#include "filters/gaussian_blur/gaussian_blur.h"
#include "../help_func.h"

TEST_CASE("Gaussian Blur Check Consume Arguments Correct") {
    GaussianBlur filter;
    const char* const* ptr;
    Console console;
    std::vector<std::string> a = {"7"};
    REQUIRE_NOTHROW((ptr = filter.ConsumeArgs(console.GetStr(a))));
    REQUIRE((filter.GetSigma() - 7) <= 0.00001);
    REQUIRE(ptr == (console.ptrs.data() + 1));
    std::vector<std::string> b = {"-3.5", "1", "40"};
    REQUIRE_NOTHROW((ptr = filter.ConsumeArgs(console.GetStr(b))));
    REQUIRE((filter.GetSigma() + 3.5) <= 0.000001);
    REQUIRE(ptr == (console.ptrs.data() + 1));
}

TEST_CASE("Gaussian Blur Check Consume Arguments Incorrect") {
    GaussianBlur filter;
    Console console;
    std::vector<std::string> c = {"10a"};
    REQUIRE_THROWS(filter.ConsumeArgs(console.GetStr(c)));
    std::vector<std::string> d = {};
    REQUIRE_THROWS(filter.ConsumeArgs(console.GetStr(d)));
}
