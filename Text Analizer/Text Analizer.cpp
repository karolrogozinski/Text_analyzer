// Text Analizer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include "analyzer.h"
#include <vector>


int main()
{
    std::string text = read_file("war_and_peace.txt");
    ParadigmLongerThan pw(text, 6);
    pw.find_pattern();
    std::cout << pw.number_of_words() << std::endl << pw.patterned_text();
}
