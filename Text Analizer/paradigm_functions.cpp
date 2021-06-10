#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
#include <tuple>

#include "paradigms.h"
#include "paradigm_functions.h"



// clean text from non-letter characters and lowercase
std::string clean_string(const std::string& text_) {
    std::string exclude_chars(",.!'?()[]{}@#$%^&*\"<>?/\\0123456789-_");
    std::string text = text_;

    auto write_iter = text.begin();
    for (auto read_iter = text.begin(); read_iter != text.end(); ++read_iter) {
        auto c = *read_iter;
        if (exclude_chars.find(c) != std::string::npos) continue;
        *write_iter = c;
        ++write_iter;
    }
    text.erase(write_iter, text.end());
    text += " ";

    return text;
};


// read text from file 
std::string read_file(const std::string& file_name) {
    std::stringstream ss;
    std::ifstream file(file_name);
    ss << file.rdbuf();
    return ss.str();
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


std::string to_str(const std::vector <std::string>& text) {
    std::string s_text = "";

    for (auto a : text) {
        s_text += a;
        s_text += " ";
    };

    return s_text;
};
