/*
ID: bwang101
TASK: dualpal
LANG: C++14
*/

#include <algorithm>  // std::reverse
#include <cstddef>	  // std::size_t
#include <fstream>	  // std::ifstream, std::ofstream
#include <iostream>	  // std::endl
#include <string>	  // std::string

const std::size_t BASE_LOWER_BOUND = 2;
const std::size_t BASE_HIGHER_BOUND = 10;

auto is_palindrome(const std::string& s) -> bool {
	for(std::size_t i = 0; i < s.size() / 2; ++i) {
		if(s[i] != s[s.size() - 1 - i]) {
			return false;
		}
	}

	return true;
}

auto to_base_b(std::size_t n, const std::size_t b) -> std::string {
	const std::string BASE_CONVERSION = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZ";
	std::string ans;
	while(n > 0) {
		ans += BASE_CONVERSION[n % b];
		n /= b;
	}

	std::reverse(ans.begin(), ans.end());
	return ans;
}

auto main() -> int {
	const std::string file_base_name = "dualpal";
	std::ifstream fin(file_base_name + ".in");
	std::ofstream fout(file_base_name + ".out");

	int N = 0;
	std::size_t S = 0;

	fin >> N >> S;

	while(N > 0) {
		S++;

		int num_palindromic = 0;
		for(std::size_t base = BASE_LOWER_BOUND; base <= BASE_HIGHER_BOUND;
			++base) {
			if(is_palindrome(to_base_b(S, base))) {
				num_palindromic++;
			}
		}

		if(num_palindromic >= 2) {
			N--;
			fout << S << std::endl;
		}
	}

	return 0;
}
