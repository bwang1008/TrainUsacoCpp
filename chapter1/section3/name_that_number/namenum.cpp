/*
ID: bwang101
TASK: namenum
LANG: C++14
*/

#include <algorithm>	  // std::sort
#include <fstream>		  // std::ifstream, std::ofstream
#include <iostream>		  // std::endl
#include <string>		  // std::string, std::getline
#include <unordered_map>  // std::unordered_map
#include <vector>		  // std::vector

auto convert_name_to_serial_number(
	const std::string& name,
	const std::unordered_map<char, char>& letter_to_digit) -> std::string {
	std::string serial_number;
	for(const char c : name) {
		if(letter_to_digit.find(c) == letter_to_digit.end()) {
			return "-1";
		}
		serial_number += letter_to_digit.at(c);
	}

	return serial_number;
}

auto main() -> int {
	const std::string file_base_name = "namenum";
	std::ifstream fin(file_base_name + ".in");
	std::ofstream fout(file_base_name + ".out");

	// reading input
	std::string serial_number;
	fin >> serial_number;

	const std::unordered_map<char, char> touch_tone_letter_to_digit = {
		{'A', '2'}, {'B', '2'}, {'C', '2'}, {'D', '3'}, {'E', '3'}, {'F', '3'},
		{'G', '4'}, {'H', '4'}, {'I', '4'}, {'J', '5'}, {'K', '5'}, {'L', '5'},
		{'M', '6'}, {'N', '6'}, {'O', '6'}, {'P', '7'}, {'R', '7'}, {'S', '7'},
		{'T', '8'}, {'U', '8'}, {'V', '8'}, {'W', '9'}, {'X', '9'}, {'Y', '9'},
	};

	std::vector<std::string> valid_names;

	std::ifstream fdict("dict.txt");
	std::string dictline;
	while(std::getline(fdict, dictline)) {
		if(convert_name_to_serial_number(
			   dictline, touch_tone_letter_to_digit) == serial_number) {
			valid_names.push_back(dictline);
		}
	}

	// print sorted names
	std::sort(valid_names.begin(), valid_names.end());
	for(const std::string& name : valid_names) {
		fout << name << std::endl;
	}

	if(valid_names.empty()) {
		fout << "NONE" << std::endl;
	}

	return 0;
}
