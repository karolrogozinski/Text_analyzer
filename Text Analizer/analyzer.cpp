#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
#include <tuple>

#include "analyzer.h"


// read text from file 
std::string read_file(const std::string& file_name) {
    auto ss = std::ostringstream{};
    std::ifstream file(file_name);
    ss << file.rdbuf();
    return ss.str();
};


// clean text from non-letter characters and lowercase
std::string clean_string(const std::string& text_) {
    std::string exclude_chars(",.!'?()[]{}@#$%^&*\"<>?/\\0123456789-_");
    std::string text = text_;

    auto write_iter = text.begin();
    for (auto read_iter = text.begin(); read_iter != text.end(); ++read_iter) {
        auto c = *read_iter;
        if (exclude_chars.find(c) != std::string::npos) continue;
        *write_iter = tolower((unsigned char)c);
        ++write_iter;
    }
    text.erase(write_iter, text.end());

    return text;
};


// split string to vector of words
std::vector <std::string> split_string(const std::string& text) {
    std::string word = "";
    std::vector <std::string> splitted;
    for (auto a : text) {
        if (a == ' ' && word != "") { 
            splitted.push_back(word); 
            word = ""; continue;
        }
        if (a != ' ') word += a;
    };
    return splitted;
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


void ParadigmStartsWithSequence::find_pattern() {
    if (seq_.empty()) { return; }

    std::string pattern = "\\b(";
    pattern += seq_;
    pattern += ")([^ ]*)";
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


void ParadigmEndsOnSequence::find_pattern() {
    if (seq_.empty()) { return; }

    std::string pattern = "([^ ]*)(";
    pattern += seq_;
    pattern += ")([ ])";
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

int ParadigmIntersection(std::string text, std::vector< std::pair<char, std::string> > paradigms) {
    std::string to_modify = text;

    for (auto a : paradigms) {

        int number = a.first;

        switch (number) {
        case 1: {
            ParadigmLongerThan p1(to_modify, std::stoi(a.second));
            to_modify = p1.patterned_text();
            break; }
        case 2: {
            ParadigmShorterThan p2(to_modify, std::stoi(a.second));
            to_modify = p2.patterned_text();
            break; }
        case 3: {
            ParadigmEqualLength p3(to_modify, std::stoi(a.second));
            to_modify = p3.patterned_text();
            break; }
        case 4: {
            ParadigmStartsWithSequence p4(to_modify, a.second);
            to_modify = p4.patterned_text();
            break; }
        case 5: {
            ParadigmEndsOnSequence p5(to_modify, a.second);
            to_modify = p5.patterned_text();
            break;}
        };
    };

    ParadigmWords p(to_modify);
    return p.number_of_words();
};
