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

std::string to_str(const std::vector <std::string>& text);
