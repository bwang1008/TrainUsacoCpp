/*
ID: bwang101
TASK: skidesign
LANG: C++14
*/

#include <algorithm>  // std::min, std::max
#include <cstddef>	  // std::size_t
#include <fstream>	  // std::ifstream, std::ofstream
#include <iostream>	  // std::endl
#include <string>	  // std::string
#include <vector>	  // std::vector

const int TAX_HEIGHT = 17;

auto cost(const std::vector<int>& heights, const int lower_bound) -> int {
	int total = 0;
	for(const int h : heights) {
		if(h < lower_bound) {
			total += (lower_bound - h) * (lower_bound - h);
		} else if(h > lower_bound + TAX_HEIGHT) {
			total +=
				(lower_bound + TAX_HEIGHT - h) * (lower_bound + TAX_HEIGHT - h);
		}
	}

	return total;
}

auto find_min_cost(const std::vector<int>& heights,
				   const int low,
				   const int high) -> int {
	if(high - low <= 3) {
		int lowest_cost = cost(heights, low);
		for(int i = low + 1; i <= high; ++i) {
			lowest_cost = std::min(cost(heights, i), lowest_cost);
		}

		return lowest_cost;
	}

	int third = (2 * low + high) / 3;
	int third_2 = (low + 2 * high) / 3;
	int cost_1 = cost(heights, third);
	int cost_2 = cost(heights, third_2);

	if(cost_1 < cost_2) {
		return find_min_cost(heights, low, third_2);
	}
	return find_min_cost(heights, third, high);
}

auto main() -> int {
	const std::string file_base_name = "skidesign";
	std::ifstream fin(file_base_name + ".in");
	std::ofstream fout(file_base_name + ".out");

	std::size_t N = 0;
	fin >> N;

	int highest = 0;
	std::vector<int> heights(N, 0);
	for(std::size_t i = 0; i < N; ++i) {
		fin >> heights[i];
		highest = std::max(heights[i], highest);
	}

	int min_cost = find_min_cost(heights, 0, highest);
	fout << min_cost << std::endl;

	return 0;
}
