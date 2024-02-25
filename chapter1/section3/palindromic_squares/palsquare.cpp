/*
ID: bwang101
TASK: palsquare
LANG: C++14
*/

#include <algorithm>  // std::reverse
#include <cstddef>	  // std::size_t
#include <fstream>	  // std::ifstream, std::ofstream
#include <iostream>	  // std::endl
#include <string>	  // std::string
#include <vector>	  // std::vector

const std::size_t UPPER_LIMIT = 300;

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
	const std::string file_base_name = "palsquare";
	std::ifstream fin(file_base_name + ".in");
	std::ofstream fout(file_base_name + ".out");

	std::size_t B = 0;
	fin >> B;

	for(std::size_t i = 1; i <= UPPER_LIMIT; ++i) {
		const std::string square = to_base_b(i * i, B);
		if(is_palindrome(square)) {
			fout << to_base_b(i, B) << " " << square << std::endl;
		}
	}

	return 0;
}
