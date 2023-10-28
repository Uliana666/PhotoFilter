#include "utility_clusterize.h"

#include <cmath>
#include <vector>
#include <random>
#include <algorithm>
#include <cstdlib>

Point::Point() : x(0), y(0), z(0) {
}

Point::Point(float x, float y, float z) : x(x), y(y), z(z) {
}

float Point::SquareDist(const Point& other) const {
    return powf(other.x - x, 2) + powf(other.y - y, 2) + powf(other.z - z, 2);
}

bool Point::operator==(const Point& other) const {
    return x == other.x && y == other.y && z == other.z;
}

bool Point::EqualWithEps(const Point& other, float eps) const {
    return fabs(x - other.x) <= eps && fabs(y - other.y) <= eps && (z - other.z) <= eps;
}

std::vector<size_t> utility::clusterize::FindForPointsCentroid(const std::vector<Point>& centroids,
                                                               const std::vector<Point>& points) {
    std::vector<size_t> order(centroids.size());
    std::vector<size_t> res(points.size());
    for (size_t num_point = 0; num_point < points.size(); ++num_point) {
        float min_dist = INFINITY;
        size_t num = -1;
        for (size_t num_centroid = 0; num_centroid < centroids.size(); ++num_centroid) {
            float dist = centroids[num_centroid].SquareDist(points[num_point]);
            if (dist < min_dist) {
                min_dist = dist;
                num = num_centroid;
            }
        }
        res[num_point] = num;
    }
    return res;
}

Point utility::clusterize::FindCentroid(const std::vector<Point>& points) {
    Point mid;
    for (size_t i = 0; i < points.size(); ++i) {
        mid.x += points[i].x;
        mid.y += points[i].y;
        mid.z += points[i].z;
    }
    mid.x /= static_cast<float>(points.size());
    mid.y /= static_cast<float>(points.size());
    mid.z /= static_cast<float>(points.size());
    return mid;
}

std::pair<std::vector<Point>, std::vector<size_t>> utility::clusterize::FindClusters(const std::vector<Point>& points,
                                                                                     size_t k) {
    std::mt19937 generator;
    std::vector<Point> centroids;
    for (size_t i = 0; i < k; ++i) {
        size_t num = generator() % points.size();
        centroids.push_back(points[num]);
    }
    bool changes = true;
    while (changes) {
        changes = false;
        std::vector<size_t> cluster_point = FindForPointsCentroid(centroids, points);
        std::vector<std::vector<Point>> clusters(k);
        for (size_t num_point = 0; num_point < points.size(); ++num_point) {
            clusters[cluster_point[num_point]].push_back(points[num_point]);
        }
        for (size_t i = 0; i < k; ++i) {
            if (clusters[i].empty()) {
                for (size_t num_point = 0; num_point < points.size(); ++num_point) {
                    if (points[num_point] == centroids[i]) {
                        continue;
                    }
                    if (std::find(centroids.begin(), centroids.end(), points[num_point]) == centroids.end()) {
                        centroids[i] = points[num_point];
                        changes = true;
                        break;
                    }
                }
            } else {
                Point mid = FindCentroid(clusters[i]);
                if (!mid.EqualWithEps(centroids[i], Eps)) {
                    centroids[i] = mid;
                    changes = true;
                }
            }
        }
    }
    return {std::move(centroids), FindForPointsCentroid(centroids, points)};
}
