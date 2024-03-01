/*
ID: bwang101
TASK: barn1
LANG: C++14
*/

/**
 * Greedy algorithm that removes the (M - 1) largest gaps
 */

#include <algorithm>   // std::sort
#include <cstddef>	   // std::size_t
#include <fstream>	   // std::ifstream, std::ofstream
#include <functional>  // std::greater
#include <iostream>	   // std::endl
#include <string>	   // std::string
#include <vector>	   // std::vector

auto main() -> int {
	const std::string file_base_name = "barn1";
	std::ifstream fin(file_base_name + ".in");
	std::ofstream fout(file_base_name + ".out");

	std::size_t M = 0;
	std::size_t S = 0;
	std::size_t C = 0;

	fin >> M >> S >> C;

	// get all cow positions sorted
	std::vector<int> cow_positions;
	for(std::size_t i = 0; i < C; ++i) {
		std::size_t cow_position = 0;
		fin >> cow_position;
		cow_positions.push_back(cow_position);
	}

	std::sort(cow_positions.begin(), cow_positions.end());

	int total_stalls_covered = cow_positions.back() - cow_positions.front() + 1;

	// find all non-zero gaps between cow stalls
	std::vector<int> gap_sizes;
	for(std::size_t i = 0; i + 1 < cow_positions.size(); ++i) {
		int gap_size = cow_positions[i + 1] - cow_positions[i] - 1;
		if(gap_size > 0) {
			gap_sizes.push_back(gap_size);
		}
	}

	// sort in descending order to get M - 1 largest gaps:
	// remove these to use M boards
	std::sort(gap_sizes.begin(), gap_sizes.end(), std::greater<>());

	for(std::size_t i = 0; i < std::min(M - 1, gap_sizes.size()); ++i) {
		total_stalls_covered -= gap_sizes[i];
	}

	fout << total_stalls_covered << std::endl;

	return 0;
}
