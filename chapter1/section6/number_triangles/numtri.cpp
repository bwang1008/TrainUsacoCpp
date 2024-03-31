/*
ID: bwang101
TASK: numtri
LANG: C++14
*/

#include <algorithm>  // std::max
#include <cstddef>	  // std::size_t
#include <fstream>	  // std::ifstream, std::ofstream
#include <iostream>	  // std::endl
#include <string>	  // std::string
#include <vector>	  // std::vector

auto find_max_sum_of_path(const std::size_t R,
						  const std::vector<std::vector<int>>& board) -> int {
	std::vector<std::vector<int>> max_sums(R, std::vector<int>(R + 1));

	// base case
	max_sums[0][0] = board[0][0];

	for(std::size_t row_index = 1; row_index < R; ++row_index) {
		const std::size_t num_integers = 1 + row_index;
		for(std::size_t col_index = 0; col_index < num_integers; ++col_index) {
			if(col_index > 0) {
				max_sums[row_index][col_index] =
					std::max(max_sums[row_index - 1][col_index - 1] +
								 board[row_index][col_index],
							 max_sums[row_index][col_index]);
			}
			if(col_index + 1 < num_integers) {
				max_sums[row_index][col_index] =
					std::max(max_sums[row_index - 1][col_index] +
								 board[row_index][col_index],
							 max_sums[row_index][col_index]);
			}
		}
	}

	int max_sum = max_sums[R - 1][0];
	for(std::size_t i = 1; i <= R; ++i) {
		max_sum = std::max(max_sums[R - 1][i], max_sum);
	}

	return max_sum;
}

auto main() -> int {
	const std::string file_base_name = "numtri";
	std::ifstream fin(file_base_name + ".in");
	std::ofstream fout(file_base_name + ".out");

	std::size_t R = 0;
	fin >> R;

	std::vector<std::vector<int>> board(R, std::vector<int>(R + 1));

	for(std::size_t i = 0; i < R; ++i) {
		const std::size_t num_integers = i + 1;
		for(std::size_t j = 0; j < num_integers; ++j) {
			fin >> board[i][j];
		}
	}

	const int answer = find_max_sum_of_path(R, board);
	fout << answer << std::endl;

	return 0;
}
