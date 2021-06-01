#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "analyzer.h"
#include <regex>
#include <utility>


std::string read_file(const std::string& file_name);

std::string clean_string(const std::string& text_);

std::vector <std::string> split_string(const std::string& text);


class IParadigm {
	int result;
	std::string* text;
	int index = 0;
	std::string label; //"Words' number {being longer than/starting with/... is .result//
	std::string name_;

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
	std::string label = "";
	std::string name_ = "Number of words ";

public:
	std::string name() { return name_; }
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
	std::string label = "with chars' number being bigger than ";
	std::string patterned_text_ = "";
	std::string name_;

public:
	std::string name() { return name_; }
	void set_name(int len) { name_ = "Words longer than " + std::to_string(len) + " chars "; }
	ParadigmLongerThan(const std::string& text_, int len) { text = &text_; length = len; find_pattern(); set_name(len); }
	void find_pattern();
	int number_of_words() { return result; };
	std::string patterned_text() { return patterned_text_; };
};


class ParadigmShorterThan : public IParadigm {
	int result = 0;
	const std::string* text;
	int index = 2;
	int length;
	std::string label = "with chars' number being smaller than ";
	std::string patterned_text_ = "";
	std::string name_;

public:
	std::string name() { return name_; }
	void set_name(int len) { name_ =  "Words shorther than " + std::to_string(len) + " chars "; }
	ParadigmShorterThan(const std::string& text_, int len) { text = &text_; length = len; find_pattern(); set_name(len); }
	void find_pattern();
	int number_of_words() { return result; };
	std::string patterned_text() { return patterned_text_; };
};


class ParadigmEqualLength : public IParadigm {
	int result = 0;
	const std::string* text;
	int index = 3;
	int length;
	std::string label = "with chars' number being equal to ";
	std::string patterned_text_ = "";
	std::string name_;

public:
	std::string name() { return name_; }
	void set_name(int len) {
		name_ = "Words with chars number equal to" + std::to_string(len) + " ";}
	ParadigmEqualLength(const std::string& text_, int len) {
		text = &text_; length = len; find_pattern(); set_name(len);}
	void find_pattern();
	int number_of_words() { return result; };
	std::string patterned_text() { return patterned_text_; };
};


class ParadigmStartsWithSequence : public IParadigm{
	int result = 0;
	const std::string* text;
	int index = 4;
	std::string seq_;
	std::string label = "starting with ";
	std::string patterned_text_ = "";
	std::string name_;

public:
	std::string name() { return name_; }
	void set_name(std::string seq) { name_ = "Words starting with '" + seq + "' "; }
	ParadigmStartsWithSequence(const std::string& text_, std::string seq) { text = &text_; seq_ = seq; find_pattern(); set_name(seq); }
	void find_pattern();
	int number_of_words() { return result; };
	std::string patterned_text() { return patterned_text_; };
};


class ParadigmEndsOnSequence : public IParadigm {
	int result = 0;
	const std::string* text;
	int index = 5;
	std::string seq_;
	std::string label = "ending with ";
	std::string patterned_text_ = "";
	std::string name_;

public:
	std::string name() { return name_; }
	void set_name(std::string seq) { name_ = "Words ending on '" + seq + "' "; }
	ParadigmEndsOnSequence(const std::string& text_, std::string seq) { text = &text_; seq_ = seq; find_pattern(); set_name(seq); }
	void find_pattern();
	int number_of_words() { return result; };
	std::string patterned_text() { return patterned_text_; };
};


class ParadigmContainSequence : public IParadigm {
	int result = 0;
	const std::string* text;
	int index = 6;
	std::string seq_;
	std::string label = "contain ";
	std::string patterned_text_ = "";
	std::string name_;

public:
	std::string name() { return name_; }
	void set_name(std::string seq) { name_ = "Words contain '" + seq + "' "; }
	ParadigmContainSequence(const std::string& text_, std::string seq) { text = &text_; seq_ = seq; find_pattern(); set_name(seq); }
	void find_pattern();
	int number_of_words() { return result; };
	std::string patterned_text() { return patterned_text_; };
};


class ParadigmCustom : public IParadigm {
	int result = 0;
	const std::string* text;
	int index = 7;
	std::string regex_;
	std::string label = "custom regex ";
	std::string patterned_text_ = "";
	std::string name_;

public:
	std::string name() { return name_; }
	void set_name() { name_ = "Custom regex word: '" + regex_ + "' "; }
	ParadigmCustom(const std::string& text_, std::string regex) { text = &text_; regex_ = regex; find_pattern(); set_name(); }
	void find_pattern();
	int number_of_words() { return result; };
	std::string patterned_text() { return patterned_text_; };
};


std::string get_intersection(std::string text, std::vector< std::pair<char, std::string> > paradigms);
std::string get_union(std::string text, std::vector< std::pair<char, std::string> > paradigms);
int ParadigmIntersection(std::string text, std::vector< std::pair<char, std::string> > paradigms);
int ParadigmUnion(std::string text, std::vector< std::pair<char, std::string> > paradigms);

std::vector <std::pair<char, std::string>> erease_paradigm(std::vector <std::pair<char, std::string>> list, int index);

std::vector <std::string> describe_filters(std::vector <std::pair<char, std::string>> filters);
