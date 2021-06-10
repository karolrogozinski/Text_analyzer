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
	IParadigm() { param = ""; }
	IParadigm(std::string given) { param = given; };
	virtual std::vector <std::string> find_pattern(std::vector <std::string> words)=0;
};


class ParadigmWords : public IParadigm {
public:
	std::vector <std::string> find_pattern(std::vector <std::string> words) { return words; } //bulshit
	int number_of_words(std::vector <std::string> words) { return words.size(); };
};


class ParadigmLongerThan : public IParadigm {
public:
	ParadigmLongerThan(std::string given) { param = given; };
	std::vector <std::string> find_pattern(std::vector <std::string> words);
};

class ParadigmShorterThan : public IParadigm {
public:
	ParadigmShorterThan(std::string given) { param = given; };
	std::vector <std::string> find_pattern(std::vector <std::string> words);
};


class ParadigmEqualLength : public IParadigm {
public:
	ParadigmEqualLength(std::string given) { param = given; };
	std::vector <std::string> find_pattern(std::vector <std::string> words);
};


class ParadigmStartsWithSequence : public IParadigm {
public:
	ParadigmStartsWithSequence(std::string given) {param = given;};
	std::vector <std::string> find_pattern(std::vector <std::string> words);
};


class ParadigmEndsOnSequence : public IParadigm {
public:
	ParadigmEndsOnSequence(std::string given) {param = given;};
	std::vector <std::string> find_pattern(std::vector <std::string> words);
};


class ParadigmContainSequence : public IParadigm {
public:
	ParadigmContainSequence(std::string given) {param = given;};
	std::vector <std::string> find_pattern(std::vector <std::string> words);
};


class ParadigmCustom : public IParadigm {
public:
	ParadigmCustom(std::string given) { param = given; }
	std::vector <std::string> find_pattern(std::vector <std::string> words);
	
};

std::vector <std::string> remove_from_vector(std::vector <std::string> words1, std::vector <std::string> words2);

std::vector <std::string> get_intersection(std::vector <std::string> words, std::vector <std::shared_ptr<IParadigm>> paradigms);
std::vector <std::string> get_union(std::vector <std::string> words, std::vector <std::shared_ptr<IParadigm>> paradigms);
//int ParadigmUnion(std::string text, std::vector< std::pair<char, std::string> > paradigms);