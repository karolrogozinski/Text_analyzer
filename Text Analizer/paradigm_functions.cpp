#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <regex>
#include <tuple>

#include "paradigm_functions.h"
#include "paradigms.h"


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
        case 6: {
            ParadigmContainSequence p6(to_modify, a.second);
            to_modify = p6.patterned_text();
            break; }
        case 7: {
            ParadigmCustom p7(to_modify, a.second);
            to_modify = p7.patterned_text();
            break; }
        };
    };
    return to_modify;
}

//return union of paradigms (given in vector) used on given text
std::string get_union(std::string text, std::vector< std::pair<char, std::string> > paradigms) {

    std::string to_modify;
    std::string text_copy = clean_string(text);

    int first = 0;
    int second = 1;

    if (paradigms.size() < 2) {
        return get_intersection(text_copy, paradigms);
    }

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

std::vector <std::string> describe_filters(std::vector <std::pair<char, std::string>> filters) {
    std::vector <std::string> description;
    for (auto a : filters) {
        int number = a.first;

        switch (number) {
        case 1: {
            description.push_back("Length longer than: " + a.second);
            break; }
        case 2: {
            description.push_back("Length shorter than: " + a.second);
            break; }
        case 3: {
            description.push_back("Length equal: " + a.second);
            break; }
        case 4: {
            description.push_back("Start with sequence: " + a.second);
            break; }
        case 5: {
            description.push_back("End with sequence: " + a.second);
            break; }
        case 6: {
            description.push_back("Contain sequence: " + a.second);
            break; }
        case 7: {
            description.push_back("Custom word regex: " + a.second);
            break; }
        };
    };
    return description;
};

//remove paradigm of given index from vector containing themselves
std::vector <std::pair<char, std::string>> erease_paradigm(std::vector <std::pair<char, std::string>> list, int index) {
    int i = 0;
    for (auto a : list) {
        if ((int)a.first == index) {
            list.erase(list.begin() + i);
            return list;
        }
        ++i;
    }
    return list;
}