/*
ID: bwang101
TASK: wormhole
LANG: C++14
*/

#include <cstddef>	 // std::size_t
#include <fstream>	 // std::ifstream, std::ofstream
#include <iostream>	 // std::endl
#include <string>	 // std::string
#include <utility>	 // std::pair, std::make_pair
#include <vector>	 // std::vector

auto portal_pairs_has_infinite_loop(const std::vector<int>& portal_links,
									const std::vector<int>& right_portal_index)
	-> bool {
	const std::size_t N = portal_links.size();
	for(std::size_t start = 0; start < N; ++start) {
		// try each portal as a starting point of Bessie
		int current_portal_index = start;
		// attempt to go right through N portals: go through portal first, then
		// move right
		for(std::size_t i = 0; i < N; ++i) {
			if(current_portal_index == -1) {
				break;
			}
			current_portal_index =
				right_portal_index[portal_links[current_portal_index]];
		}

		if(current_portal_index != -1) {
			return true;
		}
	}

	return false;
}

auto find_pair_combinations_helper(std::vector<int> arr,
								   const std::size_t index,
								   std::vector<std::vector<int>>& accumulator)
	-> void {
	if(index == arr.size()) {
		accumulator.push_back(arr);
		return;
	}

	if(arr[index] != -1) {
		find_pair_combinations_helper(arr, 1 + index, accumulator);
		return;
	}

	for(std::size_t i = 1 + index; i < arr.size(); ++i) {
		if(arr[i] == -1) {
			// link portals index and i
			arr[index] = i;
			arr[i] = index;

			find_pair_combinations_helper(arr, 1 + index, accumulator);

			arr[index] = -1;
			arr[i] = -1;
		}
	}
}

auto find_pair_combinations(const std::size_t N)
	-> std::vector<std::vector<int>> {
	std::vector<std::vector<int>> accumulator;
	std::vector<int> arr(N, -1);
	find_pair_combinations_helper(arr, 0, accumulator);

	return accumulator;
}

auto main() -> int {
	const std::string file_base_name = "wormhole";
	std::ifstream fin(file_base_name + ".in");
	std::ofstream fout(file_base_name + ".out");

	std::size_t N = 0;
	fin >> N;

	std::vector<std::pair<int, int>> portal_coords;
	for(std::size_t i = 0; i < N; ++i) {
		int a = 0;
		int b = 0;
		fin >> a >> b;
		portal_coords.emplace_back(a, b);
	}

	// right_portal_index[i] is the index of the portal that is to the immediate
	// right of portal i
	std::vector<int> right_portal_index(N, -1);
	for(std::size_t i = 0; i < N; ++i) {
		for(std::size_t j = 0; j < N; ++j) {
			// update right_portal_index[i], if j has same y-coordinate, and
			// it's either new or is closer than previous candidate
			if(portal_coords[i].first < portal_coords[j].first &&
			   portal_coords[i].second == portal_coords[j].second &&
			   (right_portal_index[i] == -1 ||
				portal_coords[j].first <
					portal_coords[right_portal_index[i]].first)) {
				right_portal_index[i] = j;
			}
		}
	}

	const std::vector<std::vector<int>> combos = find_pair_combinations(N);

	int total = 0;
	for(const std::vector<int>& portal_links : combos) {
		if(portal_pairs_has_infinite_loop(portal_links, right_portal_index)) {
			total++;
		}
	}

	fout << total << std::endl;

	return 0;
}
