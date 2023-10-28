#include "catch.hpp"

#include "filters/edge_detection/edge_detection.h"
#include "../help_func.h"

TEST_CASE("Edge Detection Check Consume Arguments Correct") {
    EdgeDetection filter;
    const char* const* ptr;
    Console console;
    std::vector<std::string> a = {"0.1"};
    REQUIRE_NOTHROW((ptr = filter.ConsumeArgs(console.GetStr(a))));
    REQUIRE((filter.GetThreshold() - 0.1) <= 0.00001);
    REQUIRE(ptr == (console.ptrs.data() + 1));
    std::vector<std::string> b = {"0.2", "1", "40"};
    REQUIRE_NOTHROW((ptr = filter.ConsumeArgs(console.GetStr(b))));
    REQUIRE((filter.GetThreshold() - 0.2) <= 0.000001);
    REQUIRE(ptr == (console.ptrs.data() + 1));
}

TEST_CASE("Edge Detection Check Consume Arguments Incorrect") {
    EdgeDetection filter;
    Console console;
    std::vector<std::string> a = {"-10"};
    REQUIRE_THROWS(filter.ConsumeArgs(console.GetStr(a)));
    std::vector<std::string> b = {"10"};
    REQUIRE_THROWS(filter.ConsumeArgs(console.GetStr(b)));
    std::vector<std::string> c = {"10a"};
    REQUIRE_THROWS(filter.ConsumeArgs(console.GetStr(c)));
    std::vector<std::string> d = {"10.5"};
    REQUIRE_THROWS(filter.ConsumeArgs(console.GetStr(d)));
    std::vector<std::string> e = {};
    REQUIRE_THROWS(filter.ConsumeArgs(console.GetStr(e)));
}

