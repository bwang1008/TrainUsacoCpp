/*
ID: bwang101
TASK: ariprog
LANG: C++14
*/

/**
 * Brute force solution: after generating all bisquares, for each number, treat
 * that number as the start of a potential arithmetic progression. Then for
 * every bisquare above the start, try this second as the second number in the
 * arithmetic progression. Check if all N values in the sequence are bisquares.
 * The important optimization that lets this run in time is when the chosen
 * difference is big enough that the last value of the sequence falls outside
 * the range, then disregard any higher second values, and try the next first
 * value.
 */

#include <algorithm>  // std::sort
#include <cstddef>	  // std::size_t
#include <fstream>	  // std::ifstream, std::ofstream
#include <iostream>	  // std::endl
#include <set>		  // std::set
#include <string>	  // std::string
#include <utility>	  // std::pair
#include <vector>	  // std::vector

auto generate_bisquares(const std::size_t M) -> std::set<int> {
	std::set<int> result;
	for(std::size_t p = 0; p <= M; ++p) {
		for(std::size_t q = 0; q <= M; ++q) {
			result.insert(static_cast<int>(p * p + q * q));
		}
	}

	return result;
}

auto is_arithmetic_sequence_of_length_n(const int start,
										const int diff,
										const std::size_t N,
										const std::vector<bool>& is_bisquare)
	-> bool {
	for(std::size_t i = 0; i < N; ++i) {
		const int number = start + int(i) * diff;
		if(!is_bisquare[number]) {
			return false;
		}
	}

	return true;
}

auto find_arithmetic_progressions(const std::size_t N, const std::size_t M)
	-> std::vector<std::pair<int, int>> {
	std::vector<std::pair<int, int>> result;

	const std::set<int> bisquares = generate_bisquares(M);
	std::vector<bool> is_bisquare(2 * M * M + 1);

	for(const int i : bisquares) {
		is_bisquare[i] = true;
	}

	std::vector<int> bisquares_list(bisquares.begin(), bisquares.end());
	std::sort(bisquares_list.begin(), bisquares_list.end());
	for(std::size_t i = 0; i < bisquares_list.size(); ++i) {
		const int start = bisquares_list[i];

		for(std::size_t j = i + 1; j < bisquares_list.size(); ++j) {
			int next_number = bisquares_list[j];
			const int diff = next_number - start;

			const std::size_t last_number = start + diff * (N - 1);
			if(last_number >= is_bisquare.size()) {
				break;
			}

			if(is_arithmetic_sequence_of_length_n(
				   start, diff, N, is_bisquare)) {
				result.emplace_back(start, diff);
			}
		}
	}

	return result;
}

auto main() -> int {
	const std::string file_base_name = "ariprog";
	std::ifstream fin(file_base_name + ".in");
	std::ofstream fout(file_base_name + ".out");

	std::size_t N = 0;
	std::size_t M = 0;
	fin >> N >> M;

	std::vector<std::pair<int, int>> answer =
		find_arithmetic_progressions(N, M);
	std::sort(
		answer.begin(),
		answer.end(),
		[](const std::pair<int, int>& left, const std::pair<int, int>& right) {
			if(left.second == right.second) {
				return left.first < right.first;
			}

			return left.second < right.second;
		});

	if(answer.empty()) {
		fout << "NONE" << std::endl;
	} else {
		for(const std::pair<int, int> p : answer) {
			fout << p.first << " " << p.second << std::endl;
		}
	}
	return 0;
}
