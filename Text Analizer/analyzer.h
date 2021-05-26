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
	int result = 0;
	const std::string* text;

public:
	ParadigmWords(const std::string& text_) { text = &text_; }
	void find_pattern();
	int return_data() { return result; };
};


class ParadigmLongerThan : public IParadigm {
	int result = 0;
	const std::string* text;
	int length;

public:
	ParadigmLongerThan(const std::string& text_, int len) { text = &text_; length = len; }
	void find_pattern();
	int return_data() { return result; };
};


class ParadigmShorterThan : public IParadigm {
	int result = 0;
	const std::string* text;
	int length;

public:
	ParadigmShorterThan(const std::string& text_, int len) { text = &text_; length = len; }
	void find_pattern();
	int return_data() { return result; };
};


class ParadigmEqualLength : public IParadigm {
	int result = 0;
	const std::string* text;
	int length;

public:
	ParadigmEqualLength(const std::string& text_, int len) { text = &text_; length = len; }
	void find_pattern();
	int return_data() { return result; };
};