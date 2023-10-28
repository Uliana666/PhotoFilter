#include "catch.hpp"

#include "filters/cluster/cluster.h"
#include "../help_func.h"

TEST_CASE("Cluster Check Consume Arguments Correct") {
    Cluster filter;
    const char* const* ptr;
    Console console;
    std::vector<std::string> a = {"10"};
    REQUIRE_NOTHROW((ptr = filter.ConsumeArgs(console.GetStr(a))));
    REQUIRE(filter.GetCountColors() == 10);
    REQUIRE(ptr == (console.ptrs.data() + 1));
    std::vector<std::string> b = {"1000000", "1", "40"};
    REQUIRE_NOTHROW((ptr = filter.ConsumeArgs(console.GetStr(b))));
    REQUIRE(filter.GetCountColors() == 1000000);
    REQUIRE(ptr == (console.ptrs.data() + 1));
}

TEST_CASE("Cluster Check Consume Arguments Incorrect") {
    Cluster filter;
    Console console;
    std::vector<std::string> a = {"-10"};
    REQUIRE_THROWS(filter.ConsumeArgs(console.GetStr(a)));
    std::vector<std::string> b = {"0"};
    REQUIRE_THROWS(filter.ConsumeArgs(console.GetStr(b)));
    std::vector<std::string> c = {"10a"};
    REQUIRE_THROWS(filter.ConsumeArgs(console.GetStr(c)));
    std::vector<std::string> d = {"10.5"};
    REQUIRE_THROWS(filter.ConsumeArgs(console.GetStr(d)));
    std::vector<std::string> e = {};
    REQUIRE_THROWS(filter.ConsumeArgs(console.GetStr(e)));
}

