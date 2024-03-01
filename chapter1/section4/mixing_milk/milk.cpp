/*
ID: bwang101
TASK: milk
LANG: C++14
*/

/**
 * Greedy algorithm that purchases all of the lowest-priced milk, then
 * the second lower-priced milk, and so on, until the quota is met.
 */

#include <algorithm>  // std::min, std::sort
#include <fstream>	  // std::ifstream, std::ofstream
#include <iostream>	  // std::endl
#include <string>	  // std::string
#include <utility>	  // std::pair
#include <vector>	  // std::vector

auto main() -> int {
	const std::string file_base_name = "milk";
	std::ifstream fin(file_base_name + ".in");
	std::ofstream fout(file_base_name + ".out");

	int N = 0;
	int M = 0;

	fin >> N >> M;

	std::vector<std::pair<int, int>> milk_price_and_amount;
	for(int i = 0; i < M; ++i) {
		int price = 0;
		int amount = 0;
		fin >> price >> amount;
		milk_price_and_amount.emplace_back(price, amount);
	}

	std::sort(milk_price_and_amount.begin(), milk_price_and_amount.end());

	int total_cost = 0;
	for(const std::pair<int, int> farmer : milk_price_and_amount) {
		int amount_to_purchase = std::min(farmer.second, N);
		total_cost += farmer.first * amount_to_purchase;
		N -= amount_to_purchase;
	}

	fout << total_cost << std::endl;

	return 0;
}
