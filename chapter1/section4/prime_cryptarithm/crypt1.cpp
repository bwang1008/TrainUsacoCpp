/*
ID: bwang101
TASK: crypt1
LANG: C++14
*/

/**
 * Brute force all 3-digit numbers by 2-digit numbers, and check if it follow
 * the constraints.
 */

#include <cstddef>		  // std::size_t
#include <fstream>		  // std::ifstream, std::ofstream
#include <iostream>		  // std::endl
#include <string>		  // std::string, std::to_string
#include <unordered_set>  // std::unordered_set

const int STANDARD_BASE = 10;
const int MIN_TWO_DIGITS = 10;
const int MAX_TWO_DIGITS = 100;
const int MIN_THREE_DIGITS = 100;
const int MAX_THREE_DIGITS = 1000;
const int MIN_FOUR_DIGITS = 1000;
const int MAX_FOUR_DIGITS = 10000;

auto has_digits(int num, const std::unordered_set<int>& digits) -> bool {
	while(num > 0) {
		if(digits.find(num % STANDARD_BASE) == digits.end()) {
			return false;
		}
		num /= STANDARD_BASE;
	}

	return true;
}

auto is_valid(const int top,
			  const int bottom,
			  const std::unordered_set<int>& digits) -> bool {
	if(!(MIN_THREE_DIGITS <= top && top < MAX_THREE_DIGITS)) {
		return false;
	}
	if(!(MIN_TWO_DIGITS <= bottom && bottom < MAX_TWO_DIGITS)) {
		return false;
	}
	if(!(MIN_FOUR_DIGITS <= top * bottom && top * bottom < MAX_FOUR_DIGITS)) {
		return false;
	}
	if(!(MIN_THREE_DIGITS <= top * (bottom % STANDARD_BASE) &&
		 top * (bottom % STANDARD_BASE) < MAX_THREE_DIGITS)) {
		return false;
	}
	if(!(MIN_THREE_DIGITS <= top * (bottom / STANDARD_BASE) &&
		 top * (bottom / STANDARD_BASE) < MAX_THREE_DIGITS)) {
		return false;
	}

	return has_digits(top, digits) && has_digits(bottom, digits) &&
		   has_digits(top * (bottom % STANDARD_BASE), digits) &&
		   has_digits(top * (bottom / STANDARD_BASE), digits) &&
		   has_digits(top * bottom, digits);
}

auto main() -> int {
	const std::string file_base_name = "crypt1";
	std::ifstream fin(file_base_name + ".in");
	std::ofstream fout(file_base_name + ".out");

	std::size_t N = 0;
	fin >> N;

	std::unordered_set<int> digits;
	for(std::size_t i = 0; i < N; ++i) {
		int digit = 0;
		fin >> digit;
		digits.insert(digit);
	}

	int total = 0;
	for(int i = MIN_THREE_DIGITS; i < MAX_THREE_DIGITS; ++i) {
		for(int j = MIN_TWO_DIGITS; j < MAX_TWO_DIGITS; ++j) {
			if(is_valid(i, j, digits)) {
				total++;
			}
		}
	}

	fout << total << std::endl;

	return 0;
}
