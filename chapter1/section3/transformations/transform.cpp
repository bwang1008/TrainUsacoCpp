/*
ID: bwang101
TASK: transform
LANG: C++14
*/

#include <cstddef>	 // std::size_t
#include <fstream>	 // std::ifstream, std::ofstream
#include <iostream>	 // std::endl
#include <string>	 // std::string
#include <vector>	 // std::vector

const int ROTATED_90 = 1;
const int ROTATED_180 = 2;
const int ROTATED_270 = 3;
const int REFLECTION = 4;
const int COMBINATION = 5;
const int NO_CHANGE = 6;
const int INVALID_TRANSFORMATION = 7;

auto rotate_quarter_clockwise(const std::vector<std::vector<char>>& board)
	-> std::vector<std::vector<char>> {
	const std::size_t N = board.size();

	std::vector<std::vector<char>> rotated(N, std::vector<char>(N, ' '));
	for(std::size_t i = 0; i < N; ++i) {
		for(std::size_t j = 0; j < N; ++j) {
			rotated[j][N - 1 - i] = board[i][j];
		}
	}

	return rotated;
}

auto flip_horizontally(const std::vector<std::vector<char>>& board)
	-> std::vector<std::vector<char>> {
	const std::size_t N = board.size();

	std::vector<std::vector<char>> flipped(N, std::vector<char>(N, ' '));
	for(std::size_t i = 0; i < N; ++i) {
		for(std::size_t j = 0; j < N; ++j) {
			flipped[i][N - 1 - j] = board[i][j];
		}
	}

	return flipped;
}

auto equals(const std::vector<std::vector<char>>& board,
			const std::vector<std::vector<char>>& expected) -> bool {
	const std::size_t N = board.size();

	for(std::size_t i = 0; i < N; ++i) {
		for(std::size_t j = 0; j < N; ++j) {
			if(board[i][j] != expected[i][j]) {
				return false;
			}
		}
	}

	return true;
}

auto calc_operation_number(const std::vector<std::vector<char>>& board,
						   const std::vector<std::vector<char>>& expected)
	-> int {
	// check if after each operation, it equals the expected
	const std::vector<std::vector<char>> rotated1 =
		rotate_quarter_clockwise(board);
	if(equals(rotated1, expected)) {
		return ROTATED_90;
	}

	const std::vector<std::vector<char>> rotated2 =
		rotate_quarter_clockwise(rotated1);
	if(equals(rotated2, expected)) {
		return ROTATED_180;
	}

	const std::vector<std::vector<char>> rotated3 =
		rotate_quarter_clockwise(rotated2);
	if(equals(rotated3, expected)) {
		return ROTATED_270;
	}

	const std::vector<std::vector<char>> flipped = flip_horizontally(board);
	if(equals(flipped, expected)) {
		return REFLECTION;
	}

	const std::vector<std::vector<char>> flipped_rotated1 =
		rotate_quarter_clockwise(flipped);
	if(equals(flipped_rotated1, expected)) {
		return COMBINATION;
	}

	const std::vector<std::vector<char>> flipped_rotated2 =
		rotate_quarter_clockwise(flipped_rotated1);
	if(equals(flipped_rotated2, expected)) {
		return COMBINATION;
	}

	const std::vector<std::vector<char>> flipped_rotated3 =
		rotate_quarter_clockwise(flipped_rotated2);
	if(equals(flipped_rotated3, expected)) {
		return COMBINATION;
	}

	if(equals(board, expected)) {
		return NO_CHANGE;
	}

	return INVALID_TRANSFORMATION;
}

auto main() -> int {
	const std::string file_base_name = "transform";
	std::ifstream fin(file_base_name + ".in");
	std::ofstream fout(file_base_name + ".out");

	// reading input
	std::size_t N = 0;
	fin >> N;

	std::vector<std::vector<char>> board(N, std::vector<char>(N, ' '));
	for(std::size_t i = 0; i < N; ++i) {
		std::string line;
		fin >> line;

		for(std::size_t j = 0; j < N; ++j) {
			board[i][j] = line[j];
		}
	}

	std::vector<std::vector<char>> expected(N, std::vector<char>(N, ' '));
	for(std::size_t i = 0; i < N; ++i) {
		std::string line;
		fin >> line;

		for(std::size_t j = 0; j < N; ++j) {
			expected[i][j] = line[j];
		}
	}

	fout << calc_operation_number(board, expected) << std::endl;

	return 0;
}
