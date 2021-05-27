#pragma once
#include <iostream>
#include <vector>
#include "analyzer.h"
#include <regex>
#include <utility>


std::string read_file(const std::string& file_name);


class IParadigm {
	int result;
	std::string* text;

public:
	virtual void find_pattern() = 0;
	virtual int number_of_words() { return result; };
	virtual std::string patterned_text() { return *text; };
};


class ParadigmWords : public IParadigm {
	int result = 0;
	const std::string* text;

public:
	ParadigmWords(const std::string& text_) { text = &text_; find_pattern(); }
	void find_pattern();
	int number_of_words() { return result; };
	std::string patterned_text() { return *text; };
};


class ParadigmLongerThan : public IParadigm {
	int result = 0;
	const std::string* text;
	int length;
	std::string patterned_text_ = "";

public:
	ParadigmLongerThan(const std::string& text_, int len) { text = &text_; length = len; find_pattern(); }
	void find_pattern();
	int number_of_words() { return result; };
	std::string patterned_text() { return patterned_text_; };
};


class ParadigmShorterThan : public IParadigm {
	int result = 0;
	const std::string* text;
	int length;
	std::string patterned_text_ = "";

public:
	ParadigmShorterThan(const std::string& text_, int len) { text = &text_; length = len; find_pattern(); }
	void find_pattern();
	int number_of_words() { return result; };
	std::string patterned_text() { return patterned_text_; };
};


class ParadigmEqualLength : public IParadigm {
	int result = 0;
	const std::string* text;
	int length;
	std::string patterned_text_ = "";

public:
	ParadigmEqualLength(const std::string& text_, int len) { text = &text_; length = len; find_pattern(); }
	void find_pattern();
	int number_of_words() { return result; };
	std::string patterned_text() { return patterned_text_; };
};


class ParadigmStartsWithSequence : public IParadigm{
	int result = 0;
	const std::string* text;
	std::string seq_;
	std::string patterned_text_ = "";

public:
	ParadigmStartsWithSequence(const std::string& text_, std::string seq) { text = &text_; seq_ = seq; find_pattern(); }
	void find_pattern();
	int number_of_words() { return result; };
	std::string patterned_text() { return patterned_text_; };
};


class ParadigmEndsOnSequence : public IParadigm {
	int result = 0;
	const std::string* text;
	std::string seq_;
	std::string patterned_text_ = "";

public:
	ParadigmEndsOnSequence(const std::string& text_, std::string seq) { text = &text_; seq_ = seq; find_pattern(); }
	void find_pattern();
	int number_of_words() { return result; };
	std::string patterned_text() { return patterned_text_; };
};

int ParadigmIntersection(std::string text, std::vector< std::pair<char, char> > paradigms);