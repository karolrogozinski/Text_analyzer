#include <iostream>


std::string display_menu() {
	return "\tMenu: \n\
	1. Read text from file\n\
	2. Analyze text\n\
	3. Exit";
};


char options() {
	char choice;
	std::cin >> choice;
	if (choice != '1' && choice != '2' && choice != '3') return options();
	return choice;
};