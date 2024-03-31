/*
ID: bwang101
TASK: milk3
LANG: C++14
*/

#include <algorithm>  // std::min
#include <cstddef>	  // std::size_t
#include <fstream>	  // std::ifstream, std::ofstream
#include <iostream>	  // std::endl
#include <set>		  // std::set
#include <string>	  // std::string
#include <tuple>	  // std::get, std::tuple

/**
 * Given the amounts in the 3 buckets, try all combinations of pouring milk
 * from one bucket to another. Before pouring, if the winning condition is
 * satisfied, append to the answer.
 */
auto recurse(const std::tuple<int, int, int> current_milk,
			 const int A,
			 const int B,
			 const int C,
			 std::set<std::tuple<int, int, int>>& visited,
			 std::set<int>& winning_condition) -> void {
	if(visited.find(current_milk) != visited.end()) {
		return;
	}
	visited.insert(current_milk);

	const int a = std::get<0>(current_milk);
	const int b = std::get<1>(current_milk);
	const int c = std::get<2>(current_milk);

	if(a == 0) {
		winning_condition.insert(c);
	}

	int pour_amount = std::min(B - b, a);
	recurse(std::tuple<int, int, int>(a - pour_amount, b + pour_amount, c),
			A,
			B,
			C,
			visited,
			winning_condition);

	pour_amount = std::min(C - c, a);
	recurse(std::tuple<int, int, int>(a - pour_amount, b, c + pour_amount),
			A,
			B,
			C,
			visited,
			winning_condition);

	pour_amount = std::min(A - a, b);
	recurse(std::tuple<int, int, int>(a + pour_amount, b - pour_amount, c),
			A,
			B,
			C,
			visited,
			winning_condition);
	pour_amount = std::min(C - c, b);
	recurse(std::tuple<int, int, int>(a, b - pour_amount, c + pour_amount),
			A,
			B,
			C,
			visited,
			winning_condition);

	pour_amount = std::min(A - a, c);
	recurse(std::tuple<int, int, int>(a + pour_amount, b, c - pour_amount),
			A,
			B,
			C,
			visited,
			winning_condition);
	pour_amount = std::min(B - b, c);
	recurse(std::tuple<int, int, int>(a, b + pour_amount, c - pour_amount),
			A,
			B,
			C,
			visited,
			winning_condition);
}

auto main() -> int {
	const std::string file_base_name = "milk3";
	std::ifstream fin(file_base_name + ".in");
	std::ofstream fout(file_base_name + ".out");

	int A = 0;
	int B = 0;
	int C = 0;
	fin >> A >> B >> C;

	std::set<std::tuple<int, int, int>> visited;
	std::set<int> winning_condition;

	recurse(std::tuple<int, int, int>(0, 0, C),
			A,
			B,
			C,
			visited,
			winning_condition);

	std::size_t num_printed = 0;
	for(const int c : winning_condition) {
		fout << c;
		if(num_printed + 1 < winning_condition.size()) {
			fout << " ";
		}
		num_printed++;
	}
	fout << std::endl;

	return 0;
}
