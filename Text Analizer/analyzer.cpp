#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>

#include "analyzer.h"


std::string read_file(const std::string& file_name) {
    auto ss = std::ostringstream{};
    std::ifstream file(file_name);
    ss << file.rdbuf();
    return ss.str();
};


void ParadigmWords::find_pattern() {
    std::regex word_regex("(\\w+)");
    auto words_begin =
        std::sregex_iterator(text->begin(), text->end(), word_regex);
    auto words_end = std::sregex_iterator();
    result = std::distance(words_begin, words_end);
};
