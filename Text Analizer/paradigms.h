#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "paradigm_functions.h"
#include <regex>
#include <utility>

class IParadigm {
	int result;
	//std::string* text;
	int index;
	int length;
	std::string seq_;
	std::string regex;

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

	virtual std::vector <std::string> find_pattern(std::vector <std::string> words)=0;
	//virtual int number_of_words() { return result; };
	//virtual std::string patterned_text() { return *text; };
};


class ParadigmWords : public IParadigm {
	int result;
	//const std::string* text;
	int index;

public:
	ParadigmWords() { result = 0; index = 0; };
	std::vector <std::string> find_pattern(std::vector <std::string> words) {
		std::vector <std::string> v = { words[0] }; return v; } //bulshit
	int number_of_words(std::vector <std::string> words) { return words.size(); };
	//std::string patterned_text() { return *text; };
};


class ParadigmLongerThan : public IParadigm {
	int result = 0;
	//const std::string* text;
	int index = 1;
	int length;
	//std::string patterned_text_ = "";

public:
	ParadigmLongerThan(int given) { length = given; };
	std::vector <std::string> find_pattern(std::vector <std::string> words);
	//int number_of_words() { return result; };
	//std::string patterned_text() { return patterned_text_; };
};


class ParadigmShorterThan : public IParadigm {
	int result = 0;
	//const std::string* text;
	int index = 2;
	int length;
	//std::string patterned_text_ = "";

public:
	ParadigmShorterThan(int given) { length = given; };
	std::vector <std::string> find_pattern(std::vector <std::string> words);
	//int number_of_words() { return result; };
	//std::string patterned_text() { return patterned_text_; };
};


class ParadigmEqualLength : public IParadigm {
	int result = 0;
	const std::string* text;
	int index = 3;
	int length;
	//std::string patterned_text_ = "";

public:
	ParadigmEqualLength(int given) {length = given;};
	std::vector <std::string> find_pattern(std::vector <std::string> words);
	//int number_of_words() { return result; };
	//std::string patterned_text() { return patterned_text_; };
};


class ParadigmStartsWithSequence : public IParadigm {
	int result = 0;
	//const std::string* text;
	int index = 4;
	std::string seq_;
	//std::string patterned_text_ = "";

public:
	ParadigmStartsWithSequence(std::string given) {
		seq_ = given;
	};
	std::vector <std::string> find_pattern(std::vector <std::string> words);
	//int number_of_words() { return result; };
	//std::string patterned_text() { return patterned_text_; };
};


class ParadigmEndsOnSequence : public IParadigm {
	int result = 0;
	//const std::string* text;
	int index = 5;
	std::string seq_;
	//std::string patterned_text_ = "";

public:
	ParadigmEndsOnSequence(std::string given) {
		seq_ = given;
	};
	std::vector <std::string> find_pattern(std::vector <std::string> words);
	//int number_of_words() { return result; };
	//std::string patterned_text() { return patterned_text_; };
};


class ParadigmContainSequence : public IParadigm {
	int result = 0;
	const std::string* text;
	int index = 6;
	std::string seq_;
	//std::string patterned_text_ = "";

public:
	ParadigmContainSequence(std::string given) {
		seq_ = given;
	};
	std::vector <std::string> find_pattern(std::vector <std::string> words);
	//int number_of_words() { return result; };
	//std::string patterned_text() { return patterned_text_; };
};


class ParadigmCustom : public IParadigm {
	int result = 0;
	std::string* text;
	int index = 7;
	std::string regex_;
	//std::string patterned_text_ = "";

public:
	ParadigmCustom( std::string reg) { regex_ = reg;}
	std::vector <std::string> find_pattern(std::vector <std::string> words);
	

	//int number_of_words() { return result; };
	//std::string patterned_text() { return patterned_text_; };
};


//int ParadigmIntersection(std::string text, std::vector< std::pair<char, std::string> > paradigms);
//int ParadigmUnion(std::string text, std::vector< std::pair<char, std::string> > paradigms);