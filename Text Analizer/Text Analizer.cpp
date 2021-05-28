// Text Analizer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

#include "analyzer.h"
#include "interface.h"


int main()
{
    std::string text = read_file("war_and_peace.txt");
    text = clean_string(text);
    std::vector<std::string> splitted = split_string(text);
    for (auto a : splitted) {
        std::cout << a << std::endl;
    }
    /*ParadigmEndsOnSequence p(text, "s");
    std::cout << p.patterned_text();
    std::cout << p.number_of_words();*/
};