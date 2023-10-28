#pragma once

#include <cmath>
#include <vector>
#include <random>
#include <algorithm>

class Point {
public:
    float x, y, z;

    Point();

    Point(float x, float y, float z);

    float SquareDist(const Point& other) const;

    bool operator==(const Point& other) const;

    bool EqualWithEps(const Point& other, float eps) const;
};

namespace utility::clusterize {

constexpr float Eps = 0.000001;

std::vector<size_t> FindForPointsCentroid(const std::vector<Point>& centroids, const std::vector<Point>& points);

Point FindCentroid(const std::vector<Point>& points);

std::pair<std::vector<Point>, std::vector<size_t>> FindClusters(const std::vector<Point>& points, size_t k);

}  // namespace utility::clusterize