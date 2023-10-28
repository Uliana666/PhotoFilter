#include <cstring>

#include "cluster.h"
#include "../../utilities/clusterize/utility_clusterize.h"

void Cluster::Apply(Image& image) const {
    std::vector<Point> points;
    for (size_t i = 0; i < image.Height(); ++i) {
        for (size_t j = 0; j < image.Width(); ++j) {
            ColorRGB color = image.GetPixel(i, j);
            points.push_back({color.GetR(), color.GetG(), color.GetB()});
        }
    }
    auto [clusters, type_point] = utility::clusterize::FindClusters(points, count_colors_);
    std::vector<ColorRGB> clusters_colors;
    for (size_t i = 0; i < clusters.size(); ++i) {
        clusters_colors.push_back(ColorRGB(clusters[i].x, clusters[i].y, clusters[i].z));
    }
    for (size_t i = 0; i < image.Height(); ++i) {
        for (size_t j = 0; j < image.Width(); ++j) {
            size_t pos = i * image.Width() + j;
            image.SetPixel(i, j, clusters_colors[type_point[pos]]);
        }
    }
}

const char* const* Cluster::ConsumeArgs(const char* const* args) {
    if (args[0] == nullptr) {
        throw std::invalid_argument("Cluster Filter: Need count colors.");
    }
    size_t pos0 = 0;
    count_colors_ = std::stoi(args[0], &pos0);
    if (count_colors_ <= 0 || pos0 != strlen(args[0])) {
        throw std::invalid_argument("Cluster Filter: Count colors is integer and cannot be less than 1.");
    }
    return (args + 1);
}

Cluster::Cluster() : count_colors_(1) {
}

int32_t Cluster::GetCountColors() const {
    return count_colors_;
}
