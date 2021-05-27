#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
#include <tuple>

#include "analyzer.h"


std::string read_file(const std::string& file_name) {
    auto ss = std::ostringstream{};
    std::ifstream file(file_name);
    ss << file.rdbuf();
    return ss.str();
};


// Count all the words in text
void ParadigmWords::find_pattern() {
    std::regex word_regex("(\\w+)");
    auto words_begin =
        std::sregex_iterator(text->begin(), text->end(), word_regex);
    auto words_end = std::sregex_iterator();
    result = std::distance(words_begin, words_end);
};


// Find and count words longer than given length
void ParadigmLongerThan::find_pattern() {
    std::regex word_regex("(\\w+)");
    auto words_begin =
        std::sregex_iterator(text->begin(), text->end(), word_regex);
    auto words_end = std::sregex_iterator();
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string match_str = match.str();
        if (match_str.size() > length) {
            patterned_text_ += match_str += " ";
            result++;
        };
    };
};


// Find and count words shorter than given length
void ParadigmShorterThan::find_pattern() {
    std::regex word_regex("(\\w+)");
    auto words_begin =
        std::sregex_iterator(text->begin(), text->end(), word_regex);
    auto words_end = std::sregex_iterator();
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string match_str = match.str();
        if (match_str.size() < length) {
            patterned_text_ += match_str += " ";
            result++;
        };
    };
};


// Find and count words equal given length
void ParadigmEqualLength::find_pattern() {
    std::regex word_regex("(\\w+)");
    auto words_begin =
        std::sregex_iterator(text->begin(), text->end(), word_regex);
    auto words_end = std::sregex_iterator();
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string match_str = match.str();
        if (match_str.size() == length) {
            patterned_text_ += match_str += " ";
            result++;
        };
    };
};


void ParadigmStartsWithLetter::find_pattern() {
    std::string pattern = "(\\";
    pattern += letter_;
    pattern += "\\w+)";
    std::regex word_regex(pattern);
    auto words_begin =
        std::sregex_iterator(text->begin(), text->end(), word_regex);
    auto words_end = std::sregex_iterator();
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string match_str = match.str();
        patterned_text_ += match_str += " ";
        result++;
    };
};


void ParadigmEndsOnLetter::find_pattern() {
    std::string pattern = "(\\w+";
    pattern += "\\";
    pattern += letter_;
    pattern += ")";
    std::regex word_regex(pattern);
    auto words_begin =
        std::sregex_iterator(text->begin(), text->end(), word_regex);
    auto words_end = std::sregex_iterator();
    for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
        std::smatch match = *i;
        std::string match_str = match.str();
        patterned_text_ += match_str += " ";
        result++;
    };
};

int ParadigmIntersection(std::string text, std::vector< std::pair<char, char> > paradigms) {
    std::string to_modify = text;

    for (auto a : paradigms) {

        int number = a.first;

        switch (number) {
        case 1: {
            ParadigmLongerThan p1(to_modify, a.second);
            to_modify = p1.patterned_text();
            break; }
        case 2: {
            ParadigmShorterThan p2(to_modify, a.second);
            to_modify = p2.patterned_text();
            break; }
        case 3: {
            ParadigmEqualLength p3(to_modify, a.second);
            to_modify = p3.patterned_text();
            break; }
        };
    };

    ParadigmWords p(to_modify);
    return p.number_of_words();
};
