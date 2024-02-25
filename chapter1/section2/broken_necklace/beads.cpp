/*
ID: bwang101
TASK: beads
LANG: C++14
*/

#include <cstddef>
#include <fstream>
#include <iostream>
#include <string>

auto calc_max_beads(std::size_t N, std::string beads) -> std::size_t {
	char prev_left = ' ';
	char prev_right = ' ';

	std::size_t max_beads = 0;

	for(std::size_t i = 0; i < N; ++i) {
		char curr_left = beads[(i + N - 1) % N];
		char curr_right = beads[i];

		if(curr_left == prev_left && curr_right == prev_right) {
			continue;
		}

		prev_left = curr_left;
		prev_right = curr_right;

		std::size_t count_left_beads = 0;
		for(std::size_t j = 0; j < N; ++j) {
			char candidate_bead = beads[(i + N - 1 - j + N) % N];
			if(candidate_bead == curr_left || candidate_bead == 'w' ||
			   curr_left == 'w') {
				count_left_beads++;
				curr_left = (curr_left == 'w') ? candidate_bead : curr_left;
			} else {
				break;
			}
		}

		std::size_t count_right_beads = 0;
		for(std::size_t j = 0; j < N; ++j) {
			char candidate_bead = beads[(i + j) % N];
			if(candidate_bead == curr_right || candidate_bead == 'w' ||
			   curr_right == 'w') {
				count_right_beads++;
				curr_right = (curr_right == 'w') ? candidate_bead : curr_right;
			} else {
				break;
			}
		}

		max_beads = std::max(std::min(count_left_beads + count_right_beads, N),
							 max_beads);
	}

	return max_beads;
}

auto main() -> int {
	const std::string file_base_name = "beads";
	std::ifstream fin(file_base_name + ".in");
	std::ofstream fout(file_base_name + ".out");

	std::size_t N = 0;
	std::string beads;

	fin >> N >> beads;

	fout << calc_max_beads(N, beads) << std::endl;

	return 0;
}
