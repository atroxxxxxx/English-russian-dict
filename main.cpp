#include <iostream>
#include <iomanip>
#include <string>
#include <iterator>
#include <fstream>

#include "src/parser.hpp"
#include "src/processor.hpp"
#include "src/dict.hpp"

int main(int argc, char** argv)
{
	src::Dictionary dict;
	src::MainProcessor processor;
	src::Parser< src::MainProcessor >::map_type comands = {
		{"HELP", &src::MainProcessor::help},
		{"ADD", &src::MainProcessor::add},
		{"REMOVE", &src::MainProcessor::remove},
		{"CLEAR", &src::MainProcessor::clear},
		{"PRINT", &src::MainProcessor::print}
	};
	src::Parser< src::MainProcessor > parser({}, {std::cin, std::cout, std::cerr, dict},
			std::move(comands));
	if (!processor.init(parser.context, argc, argv))
	{
		std::cerr << "File wasn't found/open. Creating empty dictionary\n";
	}
	else
	{
		std::cout << "The file was successfully read. A dictionary was created from: " <<
				parser.context.dict.dictionary.size() << " words\n";
	}
	processor.help(parser.context);
	while (parser.run())
	{}
}
