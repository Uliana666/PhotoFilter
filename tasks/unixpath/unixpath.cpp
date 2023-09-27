#include "unixpath.h"

#include <vector>

void CalcLastPos(std::vector<std::string>& current_path) {
    if (!current_path.empty() && current_path.back() == "..") {
        current_path.pop_back();
        if (!current_path.empty()) {
            current_path.pop_back();
        }
    }
    if (!current_path.empty() && current_path.back() == ".") {
        current_path.pop_back();
    }
}

void AddPath(std::vector<std::string>& current_path, std::string_view path) {
    bool open_name = false;
    for (const auto& sym : path) {
        if (sym == '/') {
            open_name = false;
            CalcLastPos(current_path);
            continue;
        }
        if (open_name) {
            current_path.back().push_back(sym);
        } else {
            open_name = true;
            current_path.push_back(std::string(1, sym));
        }
    }
    CalcLastPos(current_path);
}

std::string NormalizePath(std::string_view current_working_dir, std::string_view path) {
    std::vector<std::string> current_path;
    if (path[0] != '/') {
        AddPath(current_path, current_working_dir);
    }
    AddPath(current_path, path);
    std::string result = "/";
    for (const auto& name : current_path) {
        result += name;
        result += "/";
    }
    if (result.size() > 1) {
        result.pop_back();
    }
    return result;
}
