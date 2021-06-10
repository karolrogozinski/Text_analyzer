#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "paradigm_functions.h"
#include <regex>
#include <utility>
#include <memory>

class IParadigm{
	std::string param;
	std::string _description;
public:
	const std::string& get_param() { return param; }
	const std::string& get_description() { return _description; }

	virtual void find_pattern(std::vector <std::string> &words)=0;
protected:
	IParadigm(std::string given, std::string des) {
		param = given;
		_description = des;
	};
	IParadigm() { param = ""; }
};


class ParadigmWords : public IParadigm {
public:
	void find_pattern(std::vector <std::string> &words) { return; }
	int number_of_words(const std::vector <std::string> &words) { return words.size(); };
};


class ParadigmLongerThan : public IParadigm {
public:
	ParadigmLongerThan(std::string given) :IParadigm(given, "Length bigger than: ") {};
	void find_pattern(std::vector <std::string> &words);
};


class ParadigmShorterThan : public IParadigm {
public:
	ParadigmShorterThan(std::string given) :IParadigm(given, "Length smaller than: ") {};
	void find_pattern(std::vector <std::string> &words);
};


class ParadigmEqualLength : public IParadigm {
public:
	ParadigmEqualLength(std::string given) :IParadigm(given, "Length equal: ") {};
	void find_pattern(std::vector <std::string> &words);
};


class ParadigmStartsWithSequence : public IParadigm {
public:
	ParadigmStartsWithSequence(std::string given) :IParadigm(given, "Start with sequence: ") {};
	void find_pattern(std::vector <std::string> &words);
};


class ParadigmEndsOnSequence : public IParadigm {
public:
	ParadigmEndsOnSequence(std::string given) :IParadigm(given, "End with sequence: ") {};
	void find_pattern(std::vector <std::string> &words);
};


class ParadigmContainSequence : public IParadigm {
public:
	ParadigmContainSequence(std::string given) :IParadigm(given, "Contain sequence: ") {};
	void find_pattern(std::vector <std::string> &words);
};


class ParadigmCustom : public IParadigm {
public:
	ParadigmCustom(std::string given) :IParadigm(given, "Custom word regex: ") {};
	void find_pattern(std::vector <std::string> &words);
};

void erease_paradigm(std::vector <std::shared_ptr<IParadigm>>& paradigms, int index);
void remove_from_vector(std::vector <std::string> &words1, const std::vector <std::string> &words2);
std::vector <std::string> get_intersection(std::vector <std::string> words, const std::vector <std::shared_ptr<IParadigm>> &paradigms);
std::vector <std::string> get_union(std::vector <std::string> &words, const std::vector <std::shared_ptr<IParadigm>> &paradigms);
std::vector <std::string> describe_filters(const std::vector <std::shared_ptr<IParadigm>>& paradigms);
