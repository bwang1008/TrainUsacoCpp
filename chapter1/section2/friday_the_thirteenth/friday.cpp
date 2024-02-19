/*
ID: bwang101
TASK: friday
LANG: C++14
*/

#include <fstream>
#include <iostream>
#include <vector>

const int START_YEAR = 1900;
const int LEAP_CONDITION_1 = 4;
const int LEAP_NOT_CONDITION_1 = 100;
const int LEAP_CONDTION_2 = 400;
const int NUM_DAYS_IN_WEEK = 7;
const int SPECIAL_DATE = 13;

auto is_leap_year(const int year) -> bool {
	if(year % LEAP_CONDTION_2 == 0) {
		return true;
	}
	if(year % LEAP_NOT_CONDITION_1 == 0) {
		return false;
	}
	return year % LEAP_CONDITION_1 == 0;
}

auto main() -> int {
	const std::string file_base_name = "friday";
	std::ifstream fin(file_base_name + ".in");
	std::ofstream fout(file_base_name + ".out");

	const std::vector<int> NORMAL_NUM_MONTH_DAYS{
		31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};
	const std::vector<int> LEAP_YEAR_NUM_MONTH_DAYS = {
		31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

	int N = 0;
	fin >> N;

	std::vector<int> count_num_13(NUM_DAYS_IN_WEEK, 0);

	// Monday
	int current_day_of_the_week = 1;

	for(int i = 0; i < N; ++i) {
		int year = START_YEAR + i;

		// check January 13: 12 days away
		count_num_13[(current_day_of_the_week + SPECIAL_DATE - 1) %
					 NUM_DAYS_IN_WEEK]++;

		const std::vector<int> num_days_in_month =
			is_leap_year(year) ? LEAP_YEAR_NUM_MONTH_DAYS
							   : NORMAL_NUM_MONTH_DAYS;

		for(std::size_t j = 0; j < num_days_in_month.size(); ++j) {
			current_day_of_the_week =
				(current_day_of_the_week + num_days_in_month[j]) %
				NUM_DAYS_IN_WEEK;
			// only count for February through December; leave next year's
			// January for next loop
			if(j + 1 < num_days_in_month.size()) {
				count_num_13[(current_day_of_the_week + SPECIAL_DATE - 1) %
							 NUM_DAYS_IN_WEEK]++;
			}
		}
	}

	// report starting from Saturday: 6
	const int SATURDAY = 6;
	for(std::size_t i = 0; i < count_num_13.size(); ++i) {
		fout << count_num_13[(i + SATURDAY) % NUM_DAYS_IN_WEEK];
		if(i + 1 < count_num_13.size()) {
			fout << " ";
		} else {
			fout << std::endl;
		}
	}

	return 0;
}
