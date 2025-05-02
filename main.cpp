#include <iostream>
#include <string>
#include "src/initial_test.hpp"
#include "map.hpp"

int main()
{
	src::Map< std::string, int, std::less< std::string > > temp;
	std::cout << init::initialString() << '\n';
}
