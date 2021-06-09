#pragma once
#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <utility>
#include "paradigms.h"
#include <memory>


std::string read_file(const std::string& file_name);

std::string clean_string(const std::string& text_);

std::vector <std::string> split_string(const std::string& text);

//std::string get_intersection(std::string text, std::vector< std::pair<char, std::string> > paradigms);
//std::string get_union(std::string text, std::vector< std::pair<char, std::string> > paradigms);

std::vector <std::string> get_intersection(std::vector <std::string> words, std::vector <std::shared_ptr<IParadigm>> paradigms);

std::vector <std::pair<char, std::string>> erease_paradigm(std::vector <std::pair<char, std::string>> list, int index);

std::vector <std::string> describe_filters(std::vector <std::pair<char, std::string>> filters);
