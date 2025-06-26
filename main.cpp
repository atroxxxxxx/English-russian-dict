#include <iostream>
#include <string>
#include <iterator>
#include <locale>
#include <algorithm>
#include <functional>

#include "src/parser.hpp"
#include "src/processor.hpp"
#include "src/dict.hpp"

// const auto lambda = [](int a) { return a % 2 == 0;};

//using namespace std::placeholders;
//
//static auto mod = std::bind(std::modulus<>(), _1, 2);
//static auto cond = std::bind(std::equal_to<>(), std::bind(mod, _1), 0);

int main(int argc, char** argv)
{
//	std::cout << (2 % 2 == 0) << '\n';
//	std::cout << cond(2) << '\n';
//
//	return 0;
	std::setlocale(LC_ALL, "en_US.UTF-8");
	src::Dictionary dict;
	src::MainProcessor processor;
	static const src::Parser< src::MainProcessor >::map_type comands = {
		{L"HELP", &src::MainProcessor::help},
		{L"ADD", &src::MainProcessor::add},
		{L"REMOVE", &src::MainProcessor::remove},
		{L"CLEAR", &src::MainProcessor::clear},
		{L"PRINT", &src::MainProcessor::print},
		{L"SAVE", &src::MainProcessor::save}
	};
	static src::Parser< src::MainProcessor > parser({}, {std::wcin, std::wcout, std::wcerr, dict},
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
