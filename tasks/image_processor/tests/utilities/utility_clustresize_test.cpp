#include "catch.hpp"

#include "utilities/clusterize/utility_clusterize.h"

TEST_CASE("Custerize Simple test, k = 1") {
    std::vector<Point> points = {Point(0.1, 0.5, 0),    Point(0.105, 0.51, 0), Point(0.1, 0.515, 0),
                                 Point(0.102, 0.48, 0), Point(0.5, 0.5, 0),    Point(0.48, 0.52, 0)};
    auto [cluster, type] = utility::clusterize::FindClusters(points, 1);
    std::vector<size_t> ans = {0, 0, 0, 0, 0, 0};
    REQUIRE(type == ans);
    REQUIRE(cluster.size() == 1);
    REQUIRE(cluster[0].EqualWithEps(Point(0.2311666667, 0.5041666667, 0), 0.01));
}

TEST_CASE("Clusterize Simple test, k = 2") {
    std::vector<Point> points = {Point(0.1, 0.5, 0),    Point(0.105, 0.51, 0), Point(0.1, 0.515, 0),
                                 Point(0.102, 0.48, 0), Point(0.5, 0.5, 0),    Point(0.48, 0.52, 0)};
    auto [cluster, type] = utility::clusterize::FindClusters(points, 2);
    std::vector<size_t> ans0 = {0, 0, 0, 0, 1, 1};
    std::vector<size_t> ans1 = {1, 1, 1, 1, 0, 0};
    if (type != ans0 && type != ans1) {
        REQUIRE(type == ans0);
    }
    if (type == ans1) {
        std::swap(cluster[0], cluster[1]);
    }
    REQUIRE(cluster[0].EqualWithEps(Point(0.10175, 0.50125, 0), 0.01));
    REQUIRE(cluster[1].EqualWithEps(Point(0.49, 0.51, 0), 0.01));
}

TEST_CASE("Clusterize Different data smaller than k, k = 100") {
    std::vector<Point> points = {Point(0.1, 0.5, 0),    Point(0.105, 0.51, 0), Point(0.1, 0.515, 0),
                                 Point(0.102, 0.48, 0), Point(0.5, 0.5, 0),    Point(0.48, 0.52, 0)};
    auto [cluster, type] = utility::clusterize::FindClusters(points, 100);
    REQUIRE(cluster.size() == 100);
    REQUIRE(type.size() == points.size());
    for (int32_t i = 0; i < points.size(); ++i) {
        REQUIRE(cluster[type[i]].EqualWithEps(points[i], 0.001));
    }
}
