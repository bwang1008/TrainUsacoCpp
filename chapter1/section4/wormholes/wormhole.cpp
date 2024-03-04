/*
ID: bwang101
TASK: wormhole
LANG: C++14
*/

#include <cstddef>	 // std::size_t
#include <fstream>	 // std::ifstream, std::ofstream
#include <iostream>	 // std::endl
#include <set>		 // std::set
#include <string>	 // std::string
#include <utility>	 // std::pair, std::make_pair
#include <vector>	 // std::vector

void print_vec(const std::vector<int>& vec) {
	std::cout << "[";
	for(std::size_t i = 0; i < vec.size(); ++i) {
		std::cout << vec[i];
		if(i + 1 < vec.size()) {
			std::cout << ", ";
		}
	}
	std::cout << "]" << std::endl;
}

auto next_coord(const std::vector<int>& portal_links,
				const std::vector<std::pair<int, int>>& portal_coords,
				const std::pair<int, int> curr_coord,
				const std::set<int>& xs) -> std::pair<int, int> {
	// check if at entrance to portal: if so, go through portal, and move right
	// 1
	for(std::size_t i = 0; i < portal_coords.size(); ++i) {
		const std::pair<int, int> candidate_portal_coord = portal_coords[i];
		if(candidate_portal_coord == curr_coord) {
			const int linked_portal_index = portal_links[i];
			const std::pair<int, int> linked_portal_coord =
				portal_coords[linked_portal_index];
			return {1 + linked_portal_coord.first, linked_portal_coord.second};
		}
	}

	// move to next x coord
	const std::set<int>::iterator next_it = xs.upper_bound(curr_coord.first);
	if(next_it == xs.end()) {
		return {1 + curr_coord.first, curr_coord.second};
	}

	return {*next_it, curr_coord.second};
}

auto portal_pairs_from_start_has_infinite_loop(
	const std::vector<int>& portal_links,
	const std::vector<std::pair<int, int>>& portal_coords,
	const std::pair<int, int> start_coords,
	const std::set<int> xs) -> bool {
	const std::size_t N = portal_coords.size();

	const std::size_t max_num_moves = 2 * N;

	std::set<std::pair<int, int>> visited_coords;
	std::pair<int, int> curr_coords = start_coords;

	for(std::size_t move_index = 0; move_index < max_num_moves; ++move_index) {
		curr_coords = next_coord(portal_links, portal_coords, curr_coords, xs);
		visited_coords.insert(curr_coords);
	}

	return visited_coords.size() < max_num_moves;
}

auto portal_pairs_has_infinite_loop(
	const std::vector<int>& portal_links,
	const std::vector<std::pair<int, int>>& portal_coords,
	const std::set<int> xs) -> bool {
	for(const std::pair<int, int> portal_coord : portal_coords) {
		const bool result = portal_pairs_from_start_has_infinite_loop(
			portal_links, portal_coords, portal_coord, xs);
		if(result) {
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
	std::set<int> xs;
	for(std::size_t i = 0; i < N; ++i) {
		int a = 0;
		int b = 0;
		fin >> a >> b;
		portal_coords.emplace_back(a, b);
		xs.insert(a);
	}

	const std::vector<std::vector<int>> combos = find_pair_combinations(N);

	int total = 0;
	for(const std::vector<int>& portal_links : combos) {
		if(portal_pairs_has_infinite_loop(portal_links, portal_coords, xs)) {
			total++;
		} else {
		}
	}

	fout << total << std::endl;

	return 0;
}
