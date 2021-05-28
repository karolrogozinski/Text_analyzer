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


void ParadigmStartsWithSequence::find_pattern() {
    if (seq_.empty()) {
        return;
    }

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
    if (seq_.empty()) {
        return;}

    std::string pattern = "([^ ]*)(";
    pattern += seq_;
    pattern += "[ ])";
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

int ParadigmIntersection(std::string text, std::vector< std::pair<char, std::string> > paradigms) {
    std::string to_modify = get_intersection(text, paradigms);
    ParadigmWords p(to_modify);
    return p.number_of_words();
};

std::string get_union(std::string text, std::vector< std::pair<char, std::string> > paradigms) {

    std::string to_modify;
    std::string text_copy = text;

    int first = 0;
    int second = 1;

    std::pair<char, std::string> first_pair = paradigms[first];
    std::pair<char, std::string> second_pair = paradigms[second];
    std::vector< std::pair<char, std::string> > curr_vec = { first_pair, second_pair };

    std::string union_text = get_intersection(text_copy, curr_vec); //intersection of A and B

    curr_vec = { first_pair };
    std::string first_text = get_intersection(text_copy, curr_vec); //get A

    curr_vec = { second_pair };
    std::string second_text = get_intersection(text_copy, curr_vec); //get B

    std::string::size_type f = first_text.find(union_text);
    //std::string::size_type s = second_text.find(union_text);

    if (f != std::string::npos) { first_text.erase(f, union_text.length()); }; //A - intersection  !!!!
    //need to split string into string words and then remove word by word
    //if (s != std::string::npos) { second_text.erase(s, union_text.length()); };

    first_text += second_text; //A - intersection + B
    to_modify = first_text;

    int len = paradigms.size() - 2;
    second = 2;

    while (len > 0) {

        //first_pair = second_pair; //2nd pattern
        second_pair = paradigms[second]; //3rd pattern
        curr_vec = { second_pair };

        //union_text = get_intersection(text_copy, curr_vec); //

        second_text = get_intersection(text_copy, curr_vec); //get C, wyfiltrowane z ca³ego tekstu

        union_text = get_intersection(to_modify, curr_vec); //text mutual for AiB oraz C, czêœæ wspólna wystêpuj¹ca w tym ograniczonym kawa³ku

        std::string::size_type f = to_modify.find(union_text);

        if (f != std::string::npos) { to_modify.erase(f, union_text.length()); }; //A+B - intersection with C

        //first_text += second_text;
        to_modify += second_text; //dodaje do modyfikowanego tekstu C, powstaje //A+B+C

        len -= 1; second += 1;
    }
    return to_modify;
}

int ParadigmUnion(std::string text, std::vector< std::pair<char, std::string> > paradigms) {

    std::string union_string = get_union(text, paradigms);
    ParadigmWords p(union_string);
    return p.number_of_words();
};
