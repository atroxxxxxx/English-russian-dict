#include <iostream>
#include "src/initial_test.hpp"

int main(int argc, char** argv)
{
  if (argc < 2)
  {
    std::cerr << "No file\n";
    return 1;
  }
	std::cout << "hello world\n";
}
