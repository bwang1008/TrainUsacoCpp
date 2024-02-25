/*
ID: bwang101
TASK: milk2
LANG: C++14
*/

#include <algorithm>  // std::sort
#include <cstddef>	  // std::size_t
#include <fstream>	  // std::ifstream, std::ofstream
#include <iostream>	  // std::endl
#include <string>	  // std::string
#include <utility>	  // std::pair
#include <vector>	  // std::vector

/**
 * Transform milking_times into intervals where at least one farmer was milking.
 */
auto coalesce_intervals(std::vector<std::pair<int, int>> milking_times)
	-> std::vector<std::pair<int, int>> {
	std::sort(milking_times.begin(), milking_times.end());

	std::vector<std::pair<int, int>> sorted_times;
	sorted_times.push_back(milking_times[0]);

	// add sorted pairs one by one, but if the next interval
	// overlaps, extend the first one instead of making a new interval
	for(std::size_t i = 1; i < milking_times.size(); ++i) {
		if(sorted_times.back().second >= milking_times[i].first) {
			sorted_times.back().second =
				std::max(milking_times[i].second, sorted_times.back().second);
		} else {
			sorted_times.push_back(milking_times[i]);
		}
	}

	return sorted_times;
}

auto calc_max_interval(
	const std::vector<std::pair<int, int>>& sorted_milking_times) -> int {
	int max_time = 0;
	for(const std::pair<int, int> milking_interval : sorted_milking_times) {
		max_time = std::max(milking_interval.second - milking_interval.first,
							max_time);
	}

	return max_time;
}

auto calc_max_no_milking(
	const std::vector<std::pair<int, int>>& sorted_milking_times) -> int {
	int max_time = 0;

	for(std::size_t i = 1; i < sorted_milking_times.size(); ++i) {
		const std::pair<int, int> prev = sorted_milking_times[i - 1];
		const std::pair<int, int> curr = sorted_milking_times[i];
		max_time = std::max(curr.first - prev.second, max_time);
	}

	return max_time;
}

auto main() -> int {
	const std::string file_base_name = "milk2";
	std::ifstream fin(file_base_name + ".in");
	std::ofstream fout(file_base_name + ".out");

	std::size_t N = 0;
	fin >> N;

	std::vector<std::pair<int, int>> milking_times;
	for(std::size_t i = 0; i < N; ++i) {
		int begin_time = 0;
		int end_time = 0;
		fin >> begin_time >> end_time;
		milking_times.emplace_back(begin_time, end_time);
	}

	const std::vector<std::pair<int, int>> sorted_milking_times =
		coalesce_intervals(milking_times);

	fout << calc_max_interval(sorted_milking_times) << " "
		 << calc_max_no_milking(sorted_milking_times) << std::endl;

	return 0;
}
