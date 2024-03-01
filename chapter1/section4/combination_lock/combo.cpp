/*
ID: bwang101
TASK: combo
LANG: C++14
*/

/**
 * Generate all possible digits in first, second, and third position.
 * For each combo, check if its valid.
 */

#include <algorithm>	  // std::min
#include <cmath>		  // std::abs
#include <cstddef>		  // std::size_t
#include <fstream>		  // std::ifstream, std::ofstream
#include <iostream>		  // std::endl
#include <string>		  // std::string, std::to_string
#include <unordered_set>  // std::unordered_set
#include <vector>		  // std::vector

auto dist(const int a, const int b, const int N) -> int {
	const int dist_1 = std::abs(b - a);
	return std::min(dist_1, N - dist_1);
}

auto close_enough(const std::vector<int>& combo1,
				  const std::vector<int>& combo2,
				  const int N) -> bool {
	return dist(combo1[0], combo2[0], N) <= 2 &&
		   dist(combo1[1], combo2[1], N) <= 2 &&
		   dist(combo1[2], combo2[2], N) <= 2;
}

auto valid_combo(const std::vector<int>& combo,
				 const std::vector<int>& john,
				 const std::vector<int>& master,
				 const int N) -> bool {
	return close_enough(combo, john, N) || close_enough(combo, master, N);
}

auto main() -> int {
	const std::string file_base_name = "combo";
	std::ifstream fin(file_base_name + ".in");
	std::ofstream fout(file_base_name + ".out");

	int N = 0;
	fin >> N;

	int john_a = 0;
	int john_b = 0;
	int john_c = 0;
	fin >> john_a >> john_b >> john_c;

	int master_a = 0;
	int master_b = 0;
	int master_c = 0;
	fin >> master_a >> master_b >> master_c;

	const std::vector<int> john_combo{john_a, john_b, john_c};
	const std::vector<int> master_combo{master_a, master_b, master_c};

	std::vector<std::unordered_set<int>> valid_digits(
		3, std::unordered_set<int>());

	for(std::size_t i = 0; i < 3; ++i) {
		for(int delta = -2; delta <= 2; ++delta) {
			valid_digits[i].insert((john_combo[i] + delta + N) % N);
			valid_digits[i].insert((master_combo[i] + delta + N) % N);
		}
	}

	int total = 0;

	for(int candidate_a : valid_digits[0]) {
		for(int candidate_b : valid_digits[1]) {
			for(int candidate_c : valid_digits[2]) {
				const std::vector<int> candidate_combo{
					candidate_a, candidate_b, candidate_c};
				if(valid_combo(candidate_combo, john_combo, master_combo, N)) {
					total++;
				}
			}
		}
	}

	fout << total << std::endl;

	return 0;
}
