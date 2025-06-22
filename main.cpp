#include <iostream>
#include <iomanip>
#include <string>
#include <iterator>
#include <fstream>
#include <locale>

#include "src/parser.hpp"
#include "src/processor.hpp"
#include "src/dict.hpp"

int main(int argc, char** argv)
{
	std::setlocale(LC_ALL, "en_US.UTF-8");
	src::Dictionary dict;
	src::MainProcessor processor;
	src::Parser< src::MainProcessor >::map_type comands = {
		{L"HELP", &src::MainProcessor::help},
		{L"ADD", &src::MainProcessor::add},
		{L"REMOVE", &src::MainProcessor::remove},
		{L"CLEAR", &src::MainProcessor::clear},
		{L"PRINT", &src::MainProcessor::print},
		{L"SAVE", &src::MainProcessor::save}
	};
	src::Parser< src::MainProcessor > parser({}, {std::wcin, std::wcout, std::wcerr, dict},
			std::move(comands));
	if (!processor.init(parser.context, argc, argv))
	{
		std::wcerr << L"File wasn't found/open. Creating empty dictionary\n";
	}
	else
	{
		std::wcout << L"The file was successfully read. A dictionary was created from: " <<
				parser.context.dict.dictionary.size() << " words\n";
	}
	processor.help(parser.context);
	while (parser.run())
	{}
}
