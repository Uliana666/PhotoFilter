#include <string>
#include <iostream>

#include "image/bmp_image/bmp_image_parser.h"
#include "filters/crop/crop.h"
#include "filters/grayscale/grayscale.h"
#include "filters/negative/negative.h"
#include "filters/sharpening/sharpening.h"
#include "filters/edge_detection/edge_detection.h"
#include "filters/gaussian_blur/gaussian_blur.h"
#include "filters/cluster/cluster.h"

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cerr << "Please use format:\n"
                     "{program name} {path to input file} {path to output file} [-{filter_interface name 1} "
                     "[filter_interface parameter "
                     "1] [filter_interface parameter 2] ...] [-{filter_interface name 2} [filter_interface parameter "
                     "1] [filter_interface parameter 2] ...] ...\n";
        exit(1);
    }
    try {
        Image image;
        BmpImageParser parser;
        parser.LoadFromPath(image, argv[1]);
        const char* const* cur = argv + 3;
        std::unordered_map<std::string, std::unique_ptr<ConsoleFilterInterface>> data_filters;
        data_filters["-crop"] = std::make_unique<Crop>();
        data_filters["-gs"] = std::make_unique<Grayscale>();
        data_filters["-neg"] = std::make_unique<Negative>();
        data_filters["-sharp"] = std::make_unique<Sharpening>();
        data_filters["-edge"] = std::make_unique<EdgeDetection>();
        data_filters["-blur"] = std::make_unique<GaussianBlur>();
        data_filters["-clust"] = std::make_unique<Cluster>();
        while (*cur != nullptr) {
            std::string name_filter = *cur;
            cur++;
            if (data_filters.find(name_filter) == data_filters.end()) {
                throw std::invalid_argument("Incorrect filter " + name_filter);
            }
            cur = data_filters[name_filter]->ConsumeArgs(cur);
            data_filters[name_filter]->Apply(image);
        }
        BmpImageSaver saver;
        saver.SaveFromPath(image, argv[2]);
    } catch (const std::exception& e) {
        std::cerr << "Wrong: " << e.what() << std::endl;
        exit(1);
    } catch (...) {
        std::cerr << "Something went wrong...." << std::endl;
        exit(1);
    }
}
