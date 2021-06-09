#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
#include <tuple>
#include <string_view>
#include <string>

#include "paradigms.h"
#include "paradigm_functions.h"


// Find and count words longer than given length
std::vector <std::string> ParadigmLongerThan::find_pattern(std::vector <std::string> words) {
    int i = 0;
    for (auto word : words) {
        if (word.size() <= length) {
            words.erase(words.begin() + i);
            return find_pattern(words);
        }
        ++i;
    }
    return words;
};


// Find and count words shorter than given length
std::vector <std::string> ParadigmShorterThan::find_pattern(std::vector <std::string> words) {
    int i = 0;
    for (auto word : words) {
        if (word.size() >= length) {
            words.erase(words.begin() + i);
            return find_pattern(words);
        }
        ++i;
    }
    return words;
};


// Find and count words equal given length
std::vector <std::string> ParadigmEqualLength::find_pattern(std::vector <std::string> words) {
    int i = 0;
    for (auto word : words) {
        if (word.size() != length) {
            words.erase(words.begin() + i);
            return find_pattern(words);
        }
        ++i;
    }
    return words;
};


std::vector <std::string> ParadigmStartsWithSequence::find_pattern(std::vector <std::string> words) {
    if (seq_.empty()) {
        if (words.empty()) {
            return words;
        }
        words.clear();
        return words;
    }

    int n = 0;
    for (auto word : words) {
        bool result = not word.starts_with(seq_);
        if (result) {
            words.erase(words.begin() + n);
            return find_pattern(words);
        }
        ++n;
    }
    return words;
};


std::vector <std::string> ParadigmEndsOnSequence::find_pattern(std::vector <std::string> words) {
    if (seq_.empty()) {
        if (words.empty()) {
            return words;
        }
        words.clear();
        return words;
    }

    int n = 0;
    for (auto word : words) {
        bool result = not word.ends_with(seq_);
        if (result) {
            words.erase(words.begin() + n);
            return find_pattern(words);
        }
        ++n;
    }
    return words;
}


std::vector <std::string> ParadigmContainSequence::find_pattern(std::vector <std::string> words){
    if (seq_.empty() || words.empty()) {
        words.clear();
        return words;
    }  //to correct for more spaces
    
    int n = 0;
    for (auto word : words) {
        if (word.find(" ") != std::string::npos) {
            words.clear();
            return words;
        }
        if (word.find(seq_) == std::string::npos) {
            words.erase(words.begin() + n);
            return find_pattern(words);
        }
        ++n;
    }
    return words;
};


std::vector <std::string> ParadigmCustom::find_pattern(std::vector <std::string> words) {
    if (regex_.empty() || words.empty()) {
        words.clear();
        return words;
    }

    std::regex word_regex(regex_);
    int n = 0;
    bool flag = true; //false if match regex, true if not
    for (auto word : words) {
        auto words_begin = std::sregex_iterator(word.begin(), word.end(), word_regex);
        auto words_end = std::sregex_iterator();
        for (std::sregex_iterator i = words_begin; i != words_end; ++i) {
            flag = false;
        };
        if (flag){
            words.erase(words.begin() + n);
            return find_pattern(words);
        }
        flag = true;
        ++n;
    }
    return words;
};


//return number of words being in intersection of paradigms given in vector
//int ParadigmIntersection(std::string text, std::vector< std::pair<char, std::string> > paradigms) {
//    std::string to_modify = get_intersection(text, paradigms);
//    ParadigmWords p(to_modify);
//    return p.number_of_words();
//};


//return number of words being in union of paradigms given in vector
//int ParadigmUnion(std::string text, std::vector< std::pair<char, std::string> > paradigms) {
//
//    std::string union_string = get_union(text, paradigms);
//    ParadigmWords p(union_string);
//    return p.number_of_words();
//};




