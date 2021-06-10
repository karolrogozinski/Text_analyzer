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


//return vector of words having as many chars as given int
std::vector <std::string> ParadigmLongerThan::find_pattern(std::vector <std::string> words) {
    int i = 0;
    int length = std::stoi(param);
    for (auto word : words) {
        if (word.size() <= length) {
            words.erase(words.begin() + i);
            return find_pattern(words);
        }
        ++i;
    }
    return words;
};


//return vector of words being shorter than given int
std::vector <std::string> ParadigmShorterThan::find_pattern(std::vector <std::string> words) {
    int i = 0;
    int length = std::stoi(param);
    for (auto word : words) {
        if (word.size() >= length) {
            words.erase(words.begin() + i);
            return find_pattern(words);
        }
        ++i;
    }
    return words;
};


//return vector of words being equal length to given int
std::vector <std::string> ParadigmEqualLength::find_pattern(std::vector <std::string> words) {
    int i = 0;
    int length = std::stoi(param);
    for (auto word : words) {
        if (word.size() != length) {
            words.erase(words.begin() + i);
            return find_pattern(words);
        }
        ++i;
    }
    return words;
};

//return vector of words starting with given sequence
std::vector <std::string> ParadigmStartsWithSequence::find_pattern(std::vector <std::string> words) {
    if (param.empty()) {
        if (words.empty()) {
            return words;
        }
        words.clear();
        return words;
    }

    int n = 0;
    for (auto word : words) {
        bool result = not word.starts_with(param);
        if (result) {
            words.erase(words.begin() + n);
            return find_pattern(words);
        }
        ++n;
    }
    return words;
};

//return vector of words which ends on given sequence
std::vector <std::string> ParadigmEndsOnSequence::find_pattern(std::vector <std::string> words) {
    if (param.empty()) {
        if (words.empty()) {
            return words;
        }
        words.clear();
        return words;
    }

    int n = 0;
    for (auto word : words) {
        bool result = not word.ends_with(param);
        if (result) {
            words.erase(words.begin() + n);
            return find_pattern(words);
        }
        ++n;
    }
    return words;
}

//return vector of words which contains given sequence
std::vector <std::string> ParadigmContainSequence::find_pattern(std::vector <std::string> words){
    if (param.empty() || words.empty()) {
        words.clear();
        return words;
    }  //to correct for more spaces
    
    int n = 0;
    for (auto word : words) {
        if (word.find(" ") != std::string::npos) {
            words.clear();
            return words;
        }
        if (word.find(param) == std::string::npos) {
            words.erase(words.begin() + n);
            return find_pattern(words);
        }
        ++n;
    }
    return words;
};

//return vector of words containing given regex
std::vector <std::string> ParadigmCustom::find_pattern(std::vector <std::string> words) {
    if (param.empty() || words.empty()) {
        words.clear();
        return words;
    }

    std::regex word_regex(param);
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

//return vector of words made of intersections of paradigms
std::vector <std::string> get_intersection(std::vector <std::string> words, std::vector <std::shared_ptr<IParadigm>> paradigms) {

    for (auto ptr : paradigms) {
        words = ptr->find_pattern(words);
    }

    return words;
}

//remove elements of words2 existing in words1 from words1
std::vector <std::string> remove_from_vector(std::vector <std::string> words1, std::vector <std::string> words2) {
    int n = 0;
    for (auto word1 : words1) {
        for (auto word2 : words2) {
            if (word1 == word2) {
                words1.erase(words1.begin() + n);
                return remove_from_vector(words1, words2);
            }                                               
        }                                                   
        ++n;                                                
    }
    return words1;
}

//return vector of words in union of given paradigms
std::vector <std::string> get_union(std::vector <std::string> words, std::vector <std::shared_ptr<IParadigm>> paradigms) {

    std::vector <std::string> to_modify;
    int first = 0; int second = 1;

    if (paradigms.size() < 2) { return get_intersection(words, paradigms); };

    std::shared_ptr<IParadigm> first_par = paradigms[first];
    std::shared_ptr<IParadigm> second_par = paradigms[second];
    std::vector <std::shared_ptr<IParadigm>> curr_vec = { first_par, second_par };

    std::vector <std::string> union_words = get_intersection(words, curr_vec); //intersection of A and B

    curr_vec = { first_par };
    std::vector <std::string> first_words = get_intersection(words, curr_vec); //get A
    first_words = remove_from_vector(first_words, union_words); //get A wo intersection

    curr_vec = { second_par };
    std::vector <std::string> second_words = get_intersection(words, curr_vec); //get B
    for (auto word : second_words) {
        first_words.push_back(word);                        //A (wo intersection) + B
    }

    to_modify = first_words;
    int len = paradigms.size() - 2;
    second = 2;

    while (len > 0) {
        second_par = paradigms[second]; //3rd pattern
        curr_vec = { second_par };
        union_words = get_intersection(to_modify, curr_vec); //next intersection
        to_modify = remove_from_vector(to_modify, union_words);

        second_words = get_intersection(words, curr_vec); //get C
        for (auto word : second_words) {
            to_modify.push_back(word); //add C, and so on
        }
        len -= 1; second += 1;
    }

    return to_modify;
}   





