#pragma once

#include <string_view>
#include <vector>

struct StrHashCaseInsensitive;

struct CompCaseInsensitive;

std::vector<std::string_view> Split(std::string_view text, bool (*sep)(char));

std::vector<std::string_view> Search(std::string_view text, std::string_view query, size_t results_count);
