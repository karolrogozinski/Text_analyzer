// Text Analizer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "analyzer.h"
#include <vector>


int main()
{
    std::string text = read_file("war_and_peace.txt");
    ParadigmLongerThan pw(text, 3);
    ParadigmShorterThan ps(text, 6);
    std::vector <IParadigm*> params;
    params.push_back(&pw);
    params.push_back(&ps);
    for (auto a : params) {
        std::cout << a->number_of_words() << std::endl << std::endl;
    };
}
