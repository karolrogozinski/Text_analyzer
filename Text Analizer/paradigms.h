#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "paradigm_functions.h"
#include <regex>
#include <utility>

class IParadigm {
	int result;
	std::string* text;
	int index = 0;

public:
	//IParadigm() {};
	//friend std::ostream& operator<<(std::ostream& os, IParadigm& para) {
	//	os << "Words' number ";
	//	os << para.label;
	//	os << "is ";
	//	os << std::to_string(para.result);
	//	os << ".";
	//	return os;
	//}

	virtual void find_pattern() = 0;
	virtual int number_of_words() { return result; };
	virtual std::string patterned_text() { return *text; };
};


class ParadigmWords : public IParadigm {
	int result = 0;
	const std::string* text;
	int index = 0;

public:
	void find_pattern();
	ParadigmWords(const std::string& text_) { text = &text_; find_pattern(); }
	int number_of_words() { return result; };
	std::string patterned_text() { return *text; };
};


class ParadigmLongerThan : public IParadigm {
	int result = 0;
	const std::string* text;
	int index = 1;
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
	int index = 2;
	int length;
	std::string patterned_text_ = "";

public:
	ParadigmShorterThan(const std::string& text_, int len) { text = &text_; length = len; find_pattern(); };
	void find_pattern();
	int number_of_words() { return result; };
	std::string patterned_text() { return patterned_text_; };
};


class ParadigmEqualLength : public IParadigm {
	int result = 0;
	const std::string* text;
	int index = 3;
	int length;
	std::string patterned_text_ = "";

public:
	ParadigmEqualLength(const std::string& text_, int len) {
		text = &text_; length = len; find_pattern();
	}
	void find_pattern();
	int number_of_words() { return result; };
	std::string patterned_text() { return patterned_text_; };
};


class ParadigmStartsWithSequence : public IParadigm {
	int result = 0;
	const std::string* text;
	int index = 4;
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
	int index = 5;
	std::string seq_;
	std::string patterned_text_ = "";

public:
	ParadigmEndsOnSequence(const std::string& text_, std::string seq) { text = &text_; seq_ = seq; find_pattern(); }
	void find_pattern();
	int number_of_words() { return result; };
	std::string patterned_text() { return patterned_text_; };
};


class ParadigmContainSequence : public IParadigm {
	int result = 0;
	const std::string* text;
	int index = 6;
	std::string seq_;
	std::string patterned_text_ = "";

public:
	ParadigmContainSequence(const std::string& text_, std::string seq) { text = &text_; seq_ = seq; find_pattern(); }
	void find_pattern();
	int number_of_words() { return result; };
	std::string patterned_text() { return patterned_text_; };
};


class ParadigmCustom : public IParadigm {
	int result = 0;
	const std::string* text;
	int index = 7;
	std::string regex_;
	std::string patterned_text_ = "";

public:
	ParadigmCustom(const std::string& text_, std::string regex) { text = &text_; regex_ = regex; find_pattern(); }
	void find_pattern();
	int number_of_words() { return result; };
	std::string patterned_text() { return patterned_text_; };
};


int ParadigmIntersection(std::string text, std::vector< std::pair<char, std::string> > paradigms);
int ParadigmUnion(std::string text, std::vector< std::pair<char, std::string> > paradigms);