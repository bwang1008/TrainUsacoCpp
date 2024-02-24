/*
ID: bwang101
TASK: gift1
LANG: C++14
*/

#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>

auto main() -> int {
	const std::string file_base_name = "gift1";
	std::ifstream fin(file_base_name + ".in");
	std::ofstream fout(file_base_name + ".out");

	std::vector<std::string> list_of_names;
	std::unordered_map<std::string, int> accounts;

	int num_people = 0;
	fin >> num_people;

	// each person starts with $0
	for(int i = 0; i < num_people; ++i) {
		std::string person_name;
		fin >> person_name;
		list_of_names.push_back(person_name);
		accounts[person_name] = 0;
	}

	for(int i = 0; i < num_people; ++i) {
		std::string giver_name;
		fin >> giver_name;

		int withdraw_amount = 0;
		int num_people_to_share = 0;
		fin >> withdraw_amount >> num_people_to_share;

		// no changes to account if not sharing with anyone
		if(num_people_to_share == 0) {
			continue;
		}

		// withdraw money from account, but keep leftover from sharing
		accounts[giver_name] -= withdraw_amount;
		accounts[giver_name] += (withdraw_amount % num_people_to_share);

		for(int i = 0; i < num_people_to_share; ++i) {
			std::string receiver_name;
			fin >> receiver_name;

			accounts[receiver_name] += withdraw_amount / num_people_to_share;
		}
	}

	for(const std::string& name : list_of_names) {
		fout << name << " " << accounts[name] << std::endl;
	}

	return 0;
}
