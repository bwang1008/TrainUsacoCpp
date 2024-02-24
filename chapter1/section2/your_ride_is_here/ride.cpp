/*
ID: bwang101
TASK: ride
LANG: C++14
*/

#include <fstream>
#include <iostream>
#include <string>

const int MOD = 47;

auto convert_name_to_int(const std::string& s) -> int {
	int product = 1;
	for(const char c : s) {
		product = (product * (c - 'A' + 1)) % MOD;
	}

	return product;
}

auto main() -> int {
	const std::string file_base_name = "ride";
	std::ifstream fin(file_base_name + ".in");
	std::ofstream fout(file_base_name + ".out");

	std::string comet_name;
	std::string group_name;

	fin >> comet_name >> group_name;

	const std::string output_message =
		(convert_name_to_int(comet_name) == convert_name_to_int(group_name))
			? "GO"
			: "STAY";

	fout << output_message << std::endl;

	return 0;
}
