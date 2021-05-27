// Text Analizer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "analyzer.h"
#include <vector>


int main()
{
    std::string text = read_file("war_and_peace.txt");
    ParadigmEndsOnLetter p(text, 'a');
    std::cout << p.patterned_text();
}