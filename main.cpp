#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <set>
#include <string>

#include "parser.hpp"

int main()
{
	std::string command;
	std::map< std::string, void(*)(std::istream&) > commands = {
		{"HELP", src::printHelp}
	};

	src::printHelp();
	while ((std::cin >> command) && !std::cin.eof() && !std::cin.bad())
	{
		decltype(commands)::iterator iter = commands.find(command);
		if (iter == commands.end())
		{
			std::cerr << "Wrong command\n";
			continue;
		}
	}
}
