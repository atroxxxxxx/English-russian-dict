#ifndef PROCESSOR_HPP
#define PROCESSOR_HPP

#include <algorithm>
#include <iostream>
#include <functional>
#include "parser.hpp"

namespace src
{
	struct MainProcessor
	{
		static bool init(Context& context, int argc, char** argv);
		bool help(Context& context);
		bool add(Context& context);
		bool remove(Context& context);
		bool clear(Context& context);
		bool print(Context& context);
		bool save(Context& context);
	};
	struct AddProcessor
	{
		bool add_translate(Context& context);
		bool add_word(Context& context);
	};
	struct RemoveProcessor
	{
		bool remove_translate(Context& context);
		bool remove_word(Context& context);
	};
	struct PrintProcessor
	{
		bool print_word(Context& context);
		bool print_dict(Context& context);
	};
}

#endif
