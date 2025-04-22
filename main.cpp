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
	src::Parser parser;
	std::map< std::string, void(src::Parser::*)() > commands = {
		{"HELP", &src::Parser::help},
		{"CREATE_DICT", &src::Parser::create_dict},
		{"SELECT", &src::Parser::select},
		{"EXIT", &src::Parser::exit}
	};

	std::cout << "Enter HELP to show command list\n";
	while (parser.all_ok() && (std::cin >> command) && !std::cin.eof() && !std::cin.bad())
	{
		decltype(commands)::iterator iter = commands.find(command);
		if (iter == commands.end())
		{
			std::cerr << "Wrong command\n";
			continue;
		}
		else
		{
			(parser.*(iter->second))();
		}
	}
}
