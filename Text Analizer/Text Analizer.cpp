// Text Analizer.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
#include <vector>

#include "analyzer.h"
#include "interface.h"


int main()
{
    std::cout << "\tWelcome in Text Analyzer!\n\n";
    std::cout << display_menu();
    char choice = options();
};