#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
#include <tuple>

#include "analyzer.h"



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
    auto ss = std::ostringstream{};
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

//return intersection of paradigms (given in vector) used on given text
std::string get_intersection(std::string text, std::vector< std::pair<char, std::string> > paradigms) {
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
            break; }
        };
    };
    return to_modify;
}

//return number of words being in intersection of paradigms given in vector
int ParadigmIntersection(std::string text, std::vector< std::pair<char, std::string> > paradigms) {
    std::string to_modify = get_intersection(text, paradigms);
    ParadigmWords p(to_modify);
    return p.number_of_words();
};

//return union of paradigms (given in vector) used on given text
std::string get_union(std::string text, std::vector< std::pair<char, std::string> > paradigms) {

    std::string to_modify;
    std::string text_copy = clean_string(text);

    int first = 0;
    int second = 1;

    std::pair<char, std::string> first_pair = paradigms[first];
    std::pair<char, std::string> second_pair = paradigms[second];
    std::vector< std::pair<char, std::string> > curr_vec = { first_pair, second_pair };

    std::string union_text = get_intersection(text_copy, curr_vec); //intersection of A and B
    std::vector <std::string> splitted_union = split_string(union_text);

    curr_vec = { first_pair };
    std::string first_text = get_intersection(text_copy, curr_vec); //get A
    curr_vec = { second_pair };
    std::string second_text = get_intersection(text_copy, curr_vec); //get B

    for (auto a : splitted_union) {                                       //
        std::string::size_type f = first_text.find(a);                    //A - intersection
        if (f != std::string::npos) { first_text.erase(f, a.length()); }; //
    }
    
    first_text += second_text; //A (wo intersection) + B
    to_modify = first_text;

    int len = paradigms.size() - 2;
    second = 2;

    while (len > 0) {

        second_pair = paradigms[second]; //3rd pattern
        curr_vec = { second_pair };
        second_text = get_intersection(text_copy, curr_vec); //get C
        union_text = get_intersection(to_modify, curr_vec); //next intersection
        splitted_union = split_string(union_text);

        for (auto a : splitted_union) {                                      //
            std::string::size_type f = to_modify.find(a);                    //erease intersection 
            if (f != std::string::npos) { to_modify.erase(f, a.length()); }; //
        }
       
        to_modify += second_text; //add C, and so on

        len -= 1; second += 1;
    }
    return to_modify;
}

//return number of words being in union of paradigms given in vector
int ParadigmUnion(std::string text, std::vector< std::pair<char, std::string> > paradigms) {

    std::string union_string = get_union(text, paradigms);
    ParadigmWords p(union_string);
    return p.number_of_words();
};

//remove paradigm of given index from vector containing themselves
std::vector <std::pair<char, std::string>> erease_paradigm(std::vector <std::pair<char, std::string>> list, int index) {
    int i = 0;
    for (auto a : list) {
        if ((int) a.first == index) {
            list.erase(list.begin() + i);
            return list;
        }
        ++i;
    }
    return list;
}
