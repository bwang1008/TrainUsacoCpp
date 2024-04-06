/*
ID: bwang101
TASK: packrec
LANG: C++14
*/

#include <algorithm>  // std::sort, std::max, std::min
#include <cstddef>	  // std::size_t
#include <fstream>	  // std::ifstream, std::ofstream
#include <iostream>	  // std::endl
#include <set>		  // std::set
#include <sstream>	  // std::ostringstream
#include <string>	  // std::string
#include <utility>	  // std::pair
#include <vector>	  // std::vector

class Result {
public:
	auto upsert(const int x, const int y) -> void {
		bool should_add = false;

		if(container.empty()) {
			should_add = true;
		} else {
			const std::pair<int, int> some_element = *(container.cbegin());
			const int existing_area = some_element.first * some_element.second;

			if(x * y < existing_area) {
				container.clear();
				should_add = true;
			} else if(x * y == existing_area) {
				should_add = true;
			}
		}

		if(should_add) {
			const int a = std::min(x, y);
			const int b = std::max(x, y);
			container.emplace(a, b);
		}
	}

	auto upsert(const std::pair<int, int> p) -> void {
		upsert(p.first, p.second);
	}

	auto upsert(const Result& other) -> void {
		for(const std::pair<int, int> p : other.get_underlying()) {
			upsert(p.first, p.second);
		}
	}

	auto get_underlying() const -> std::set<std::pair<int, int>> {
		return container;
	}

	auto size() const -> std::size_t {
		return container.size();
	}

	auto str() const -> std::string {
		std::ostringstream os;
		if(!container.empty()) {
			const std::pair<int, int> some_element = *(container.cbegin());
			os << some_element.first * some_element.second << std::endl;
		}

		std::size_t index = 0;
		for(const std::pair<int, int> p : container) {
			os << p.first << " " << p.second;
			if(1 + index < container.size()) {
				os << std::endl;
			}
			index++;
		}

		return os.str();
	}

private:
	std::set<std::pair<int, int>> container;
};

class Rectangle {
public:
	Rectangle(const int height, const int width) {
		_height = height;
		_width = width;
		x_pos = 0;
		y_pos = 0;
	}

	auto width() const -> int {
		return _width;
	}

	auto height() const -> int {
		return _height;
	}

	auto area() const -> int {
		return _height * _width;
	}

	auto get_x_left() const -> int {
		return x_pos;
	}

	auto get_x_right() const -> int {
		return x_pos + _width;
	}

	auto get_y_bottom() const -> int {
		return y_pos;
	}

	auto get_y_upper() const -> int {
		return y_pos + _height;
	}

	auto get_bottom_left() const -> std::pair<int, int> {
		return {x_pos, y_pos};
	}

	auto get_bottom_right() const -> std::pair<int, int> {
		return {x_pos + _width, y_pos};
	}

	auto get_upper_left() const -> std::pair<int, int> {
		return {x_pos, y_pos + _height};
	}

	auto get_upper_right() const -> std::pair<int, int> {
		return {x_pos + _width, y_pos + _height};
	}

	auto set_bottom_left(const int x, const int y) -> void {
		x_pos = x;
		y_pos = y;
	}

	auto set_bottom_left(const std::pair<int, int> coords) -> void {
		set_bottom_left(coords.first, coords.second);
	}

	auto set_bottom_right(const int x, const int y) -> void {
		set_bottom_left(x - _width, y);
	}

	auto set_bottom_right(const std::pair<int, int> coords) -> void {
		set_bottom_right(coords.first, coords.second);
	}

	auto set_upper_left(const int x, const int y) -> void {
		set_bottom_left(x, y - _height);
	}

	auto set_upper_left(const std::pair<int, int> coords) -> void {
		set_upper_left(coords.first, coords.second);
	}

	auto set_upper_right(const int x, const int y) -> void {
		set_bottom_left(x - _width, y - _height);
	}

	auto set_upper_right(const std::pair<int, int> coords) -> void {
		set_upper_right(coords.first, coords.second);
	}

	auto transpose() -> void {
		int temp = _height;
		_height = _width;
		_width = temp;
	}

private:
	int _height;
	int _width;
	int x_pos;
	int y_pos;
};

auto get_enclosing_box_from_placed_rectangles(Rectangle rec1,
											  Rectangle rec2,
											  Rectangle rec3,
											  Rectangle rec4)
	-> std::pair<int, int> {
	const int enclosing_width = std::max({rec1.get_x_right(),
										  rec2.get_x_right(),
										  rec3.get_x_right(),
										  rec4.get_x_right()}) -
								std::min({rec1.get_x_left(),
										  rec2.get_x_left(),
										  rec3.get_x_left(),
										  rec4.get_x_left()});
	const int enclosing_height = std::max({rec1.get_y_upper(),
										   rec2.get_y_upper(),
										   rec3.get_y_upper(),
										   rec4.get_y_upper()}) -
								 std::min({rec1.get_y_bottom(),
										   rec2.get_y_bottom(),
										   rec3.get_y_bottom(),
										   rec4.get_y_bottom()});

	return {enclosing_width, enclosing_height};
}

/**
 * 4 rectangles, all placed in a row.
 */
auto case_1_direct(Rectangle rec1,
				   Rectangle rec2,
				   Rectangle rec3,
				   Rectangle rec4) -> Result {
	rec1.set_bottom_left(0, 0);
	rec2.set_bottom_left(rec1.get_bottom_right());
	rec3.set_bottom_left(rec2.get_bottom_right());
	rec4.set_bottom_left(rec3.get_bottom_right());

	Result result;
	result.upsert(
		get_enclosing_box_from_placed_rectangles(rec1, rec2, rec3, rec4));
	return result;
}

/**
 * 1 rectangle on the bottom, 3 on top
 */
auto case_2_direct(Rectangle rec1,
				   Rectangle rec2,
				   Rectangle rec3,
				   Rectangle rec4) -> Result {
	rec1.set_bottom_left(0, 0);
	rec2.set_bottom_left(rec1.get_upper_left());
	rec3.set_bottom_left(rec2.get_bottom_right());
	rec4.set_bottom_left(rec3.get_bottom_right());

	Result result;
	result.upsert(
		get_enclosing_box_from_placed_rectangles(rec1, rec2, rec3, rec4));
	return result;
}

/**
 * 1 rectangle on the right.
 * 1 rectangle to the left of the first, with same lower line.
 * 2 rectangles on top of the 2nd rectangle, to the left of the 1st
 */
auto case_3_direct(Rectangle rec1,
				   Rectangle rec2,
				   Rectangle rec3,
				   Rectangle rec4) -> Result {
	rec1.set_bottom_left(0, 0);
	rec2.set_bottom_right(rec1.get_bottom_left());
	rec3.set_bottom_right(rec2.get_upper_right());
	rec4.set_bottom_right(rec3.get_bottom_left());

	Result result;
	result.upsert(
		get_enclosing_box_from_placed_rectangles(rec1, rec2, rec3, rec4));
	return result;
}

/**
 * 1 rectangle on the left.
 * 1 rectangle on the middle.
 * 2 rectangles on the right, with one atop the other.
 */
auto case_4_direct(Rectangle rec1,
				   Rectangle rec2,
				   Rectangle rec3,
				   Rectangle rec4) -> Result {
	rec1.set_bottom_left(0, 0);
	rec2.set_bottom_left(rec1.get_bottom_right());
	rec3.set_bottom_left(rec2.get_bottom_right());
	rec4.set_bottom_left(rec3.get_upper_left());

	Result result;
	result.upsert(
		get_enclosing_box_from_placed_rectangles(rec1, rec2, rec3, rec4));
	return result;
}

/**
 * 4 rectangles in the classic 2x2 window pane.
 *          -------
 *  -----  |       |
 * |     | |   4   |
 * |  3  |   ------
 *  --------|      |
 * |        |      |
 * |   1    |   2  |
 * |        |      |
 *  ---------------
 *
 * where 1 is connected to 2 and 3, and 2 is connected to 1 and 4.
 *
 * Check if there's overlap from rectangles (1, 4),
 * (2, 3), and (3, 4)
 */
auto case_5_direct(Rectangle rec1,
				   Rectangle rec2,
				   Rectangle rec3,
				   Rectangle rec4) -> Result {
	rec1.set_bottom_left(0, 0);
	rec2.set_bottom_left(rec1.get_bottom_right());
	rec3.set_bottom_left(rec1.get_upper_left());
	rec4.set_bottom_right(rec2.get_upper_right());

	Result result;

	// invalid if it overlaps
	// Check 1 with 4
	if(rec4.get_y_bottom() < rec1.get_y_upper() &&
	   rec4.get_x_left() < rec1.get_x_right()) {
		return result;
	}

	// Check 2 with 3
	if(rec3.get_y_bottom() < rec2.get_y_upper() &&
	   rec3.get_x_right() > rec2.get_x_left()) {
		return result;
	}

	// Check 3 with 4
	if(rec3.get_x_right() > rec4.get_x_left() &&
	   ((rec3.get_y_bottom() <= rec4.get_y_bottom() &&
		 rec4.get_y_bottom() < rec3.get_y_upper()) ||
		(rec4.get_y_bottom() <= rec3.get_y_bottom() &&
		 rec3.get_y_bottom() < rec4.get_y_upper()))) {
		return result;
	}

	result.upsert(
		get_enclosing_box_from_placed_rectangles(rec1, rec2, rec3, rec4));
	return result;
}

auto calc_smallest_enclosing_box(Rectangle rec1,
								 Rectangle rec2,
								 Rectangle rec3,
								 Rectangle rec4) -> Result {
	const std::vector<std::vector<int>> permutations{
		{0, 1, 2, 3}, {0, 1, 3, 2}, {0, 2, 1, 3}, {0, 2, 3, 1}, {0, 3, 1, 2},
		{0, 3, 2, 1}, {1, 0, 2, 3}, {1, 0, 3, 2}, {1, 2, 0, 3}, {1, 2, 3, 0},
		{1, 3, 0, 2}, {1, 3, 2, 0}, {2, 0, 1, 3}, {2, 0, 3, 1}, {2, 1, 0, 3},
		{2, 1, 3, 0}, {2, 3, 0, 1}, {2, 3, 1, 0}, {3, 0, 1, 2}, {3, 0, 2, 1},
		{3, 1, 0, 2}, {3, 1, 2, 0}, {3, 2, 0, 1}, {3, 2, 1, 0},
	};

	Result result;

	std::vector<Rectangle> recs{rec1, rec2, rec3, rec4};

	for(const std::vector<int>& perm : permutations) {
		Rectangle r1 = recs[perm[0]];
		Rectangle r2 = recs[perm[1]];
		Rectangle r3 = recs[perm[2]];
		Rectangle r4 = recs[perm[3]];

		for(int i1 = 0; i1 < 2; ++i1) {
			r1.transpose();
			for(int i2 = 0; i2 < 2; ++i2) {
				r2.transpose();
				for(int i3 = 0; i3 < 2; ++i3) {
					r3.transpose();
					for(int i4 = 0; i4 < 2; ++i4) {
						r4.transpose();

						result.upsert(case_1_direct(r1, r2, r3, r4));
						result.upsert(case_2_direct(r1, r2, r3, r4));
						result.upsert(case_3_direct(r1, r2, r3, r4));
						result.upsert(case_4_direct(r1, r2, r3, r4));
						result.upsert(case_5_direct(r1, r2, r3, r4));
					}
				}
			}
		}
	}

	return result;
}

auto main() -> int {
	const std::string file_base_name = "packrec";
	std::ifstream fin(file_base_name + ".in");
	std::ofstream fout(file_base_name + ".out");

	int height1 = 0;
	int width1 = 0;
	int height2 = 0;
	int width2 = 0;
	int height3 = 0;
	int width3 = 0;
	int height4 = 0;
	int width4 = 0;

	fin >> height1 >> width1 >> height2 >> width2 >> height3 >> width3 >>
		height4 >> width4;

	Rectangle rec1{height1, width1};
	Rectangle rec2{height2, width2};
	Rectangle rec3{height3, width3};
	Rectangle rec4{height4, width4};

	const Result result = calc_smallest_enclosing_box(rec1, rec2, rec3, rec4);
	fout << result.str() << std::endl;

	return 0;
}
