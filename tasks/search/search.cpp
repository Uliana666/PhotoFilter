#include "search.h"

#include <unordered_map>
#include <unordered_set>
#include <cmath>
#include <ctype.h>

struct CompCaseInsensitive {
    bool operator()(std::string_view lhs, std::string_view rhs) const {
        if (lhs.size() != rhs.size()) {
            return false;
        }
        for (size_t i = 0; i < lhs.size(); ++i) {
            if (tolower(lhs[i]) != tolower(rhs[i])) {
                return false;
            }
        }
        return true;
    }
};

constexpr size_t HASH_BASE = 31;  // NOLINT

struct StrHashCaseInsensitive {
    std::size_t operator()(std::string_view str) const {
        size_t hash = 0;
        for (char c : str) {
            hash = hash * HASH_BASE + static_cast<size_t>(tolower(c));
        }
        return hash;
    }
};

std::vector<std::string_view> Split(std::string_view text, bool (*sep)(char)) {
    std::vector<std::string_view> result;
    for (size_t left = 0; left < text.size(); ++left) {
        if (sep(text[left])) {
            continue;
        }
        size_t len = 1;
        while (left + len < text.size() && !sep(text[left + len])) {
            ++len;
        }
        result.push_back(text.substr(left, len));
        left += len - 1;
    }
    return result;
}

std::vector<std::string_view> Search(std::string_view text, std::string_view query, size_t results_count) {
    std::unordered_map<std::string_view, size_t, StrHashCaseInsensitive, CompCaseInsensitive> num_str;
    std::vector<std::string_view> words_in_query = Split(query, [](char c) { return !isalpha(c); });
    size_t n = 0;
    for (const auto& word : words_in_query) {
        if (!num_str.count(word)) {
            num_str[word] = n;
            ++n;
        }
    }
    std::vector<size_t> count_docs_with_word(n);
    std::vector<std::string_view> lines = Split(text, [](char c) { return c == '\n'; });
    size_t m = lines.size();
    for (const auto& line : lines) {
        std::unordered_set<size_t> check_in;
        std::vector<std::string_view> words_in_str = Split(line, [](char c) { return !isalpha(c); });
        for (const auto& word : words_in_str) {
            if (num_str.count(word)) {
                check_in.insert(num_str[word]);
            }
        }
        for (const auto& num_in : check_in) {
            count_docs_with_word[num_in]++;
        }
    }
    std::vector<double> price(m);
    std::vector<bool> used_line(m);
    for (size_t cur_line = 0; cur_line < m; ++cur_line) {
        std::string_view line = lines[cur_line];
        std::vector<std::string_view> words_in_str = Split(line, [](char c) { return !isalpha(c); });
        std::unordered_map<size_t, size_t> count_word_in_cur_doc;
        for (const auto& word : words_in_str) {
            if (!num_str.count(word)) {
                continue;
            }
            count_word_in_cur_doc[num_str[word]]++;
        }
        for (const auto& [num_word, count] : count_word_in_cur_doc) {
            price[cur_line] += static_cast<double>(count) / static_cast<double>(words_in_str.size()) *
                               log(static_cast<double>(m) / static_cast<double>(count_docs_with_word[num_word]));
            used_line[cur_line] = true;
        }
    }
    std::vector<size_t> priority_num_lines(m);
    for (size_t i = 0; i < m; ++i) {
        priority_num_lines[i] = i;
    }
    stable_sort(priority_num_lines.begin(), priority_num_lines.end(),
                [&price](size_t a, size_t b) { return price[a] > price[b]; });
    std::vector<std::string_view> result;
    for (size_t i = 0; i < std::min(results_count, m); ++i) {
        if (!used_line[priority_num_lines[i]]) {
            break;
        }
        result.push_back(lines[priority_num_lines[i]]);
    }
    return result;
}
