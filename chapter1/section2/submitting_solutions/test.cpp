/*
ID: bwang101
TASK: test
LANG: C++14
*/

#include <fstream>
#include <iostream>

auto main() -> int {
	std::ifstream fin("test.in");
	std::ofstream fout("test.out");

	int a = 0;
	int b = 0;

	fin >> a >> b;
	fout << a + b << std::endl;

	return 0;
}
