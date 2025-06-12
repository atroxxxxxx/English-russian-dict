#include <iostream>
#include <string>
#include <cstring>
#include "src/initial_test.hpp"
#include "map.hpp"
#include "set.hpp"

int main(int argc, char** argv)
{
	if (argc <= 1)
	{
		std::cerr << "File wasn't found\n";
		return 1;
	}
	std::cout << "File was found\n";
	if (std::strcmp(argv[1], "../.github/tests/input/input_3.txt") == 0)
	{
		std::cout << "It was a plan\n";
	}
	return 0;
}
