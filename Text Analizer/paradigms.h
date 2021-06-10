#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "paradigm_functions.h"
#include <regex>
#include <utility>
#include <memory>

class IParadigm{
	
public:
	std::string param;
	std::string _description;
	IParadigm() { param = ""; }
	IParadigm(std::string given) { param = given; };
	virtual void find_pattern(std::vector <std::string> &words)=0;
};


class ParadigmWords : public IParadigm {
public:
	void find_pattern(std::vector <std::string> &words) { return; }
	int number_of_words(const std::vector <std::string> &words) { return words.size(); };
};


class ParadigmLongerThan : public IParadigm {
public:
	ParadigmLongerThan(std::string given) {
		param = given;
		_description = "Length bigger than: ";};
	void find_pattern(std::vector <std::string> &words);
};


class ParadigmShorterThan : public IParadigm {
public:
	ParadigmShorterThan(std::string given) {
		param = given;
		_description = "Length smaller than: ";
	};
	void find_pattern(std::vector <std::string> &words);
};


class ParadigmEqualLength : public IParadigm {
public:
	ParadigmEqualLength(std::string given) {
		param = given;
		_description = _description = "Length equal: ";
	};
	void find_pattern(std::vector <std::string> &words);
};


class ParadigmStartsWithSequence : public IParadigm {
public:
	ParadigmStartsWithSequence(std::string given) {
		param = given;
		_description = "Start with sequence: ";
	};
	void find_pattern(std::vector <std::string> &words);
};


class ParadigmEndsOnSequence : public IParadigm {
public:
	ParadigmEndsOnSequence(std::string given) {
		param = given;
		_description = "End with sequence: ";
	};
	void find_pattern(std::vector <std::string> &words);
};


class ParadigmContainSequence : public IParadigm {
public:
	ParadigmContainSequence(std::string given) {
		param = given;
		_description = "Contain sequence: ";
	};
	void find_pattern(std::vector <std::string> &words);
};


class ParadigmCustom : public IParadigm {
public:
	ParadigmCustom(std::string given) {
		param = given;
		_description = "Custom word regex: ";
	}
	void find_pattern(std::vector <std::string> &words);
};

void erease_paradigm(std::vector <std::shared_ptr<IParadigm>>& paradigms, int index);
void remove_from_vector(std::vector <std::string> &words1, const std::vector <std::string> &words2);
std::vector <std::string> get_intersection(std::vector <std::string> words, const std::vector <std::shared_ptr<IParadigm>> &paradigms);
std::vector <std::string> get_union(std::vector <std::string> &words, const std::vector <std::shared_ptr<IParadigm>> &paradigms);
std::vector <std::string> describe_filters(const std::vector <std::shared_ptr<IParadigm>>& paradigms);
