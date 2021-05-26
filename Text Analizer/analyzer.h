#pragma once
#include <iostream>
#include <vector>
#include "analyzer.h"
#include <regex>


std::string read_file(const std::string& file_name);


class IParadigm {
	int result;
	std::string* text;

public:
	virtual void find_pattern() = 0;
	virtual int return_data() = 0;
};


class ParadigmWords : public IParadigm {
	int result;
	const std::string* text;

public:
	ParadigmWords(const std::string& text_) { text = &text_; }
	void find_pattern();
	int return_data() { return result; };
};


class ParadigmLongerThan : public IParadigm {
	int result;
	const std::string* text;

};