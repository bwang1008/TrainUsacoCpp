/*
ID: bwang101
TASK: test
LANG: C++14
*/

#include <fstream>
#include <iostream>

int main()
{
	std::ifstream fin("test.in");
	std::ofstream fout("test.out");

	int a, b;

	fin >> a >> b;
	fout << a + b << std::endl;

	return 0;
}
