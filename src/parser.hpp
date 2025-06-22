#ifndef PARSER_HPP
#define PARSER_HPP

#include <iostream>
#include <limits>
#include <string>

#include "map.hpp"
#include "set.hpp"
#include "dict.hpp"

namespace src
{
	struct Context
	{
		using dict_type = Dictionary;
		std::wistream& input;
		std::wostream& output;
		std::wostream& error;
		dict_type& dict;
		bool eol();
	};
	template< class Processor >
	class Parser
	{
	public:
		using processor = Processor;
		using call_signature = bool(processor::*)(Context&);
		using map_type = src::Map< std::wstring, call_signature >;

		Context context;

		template< class P = processor, class M = map_type >
		Parser(P&& proc, Context context, M&& comands):
			context(context),
			proccessor_(std::forward< P >(proc)),
			comands_(std::forward< M >(comands))
		{}
		bool run()
		{
			std::wstring command;
			if (context.input >> command)
			{
				typename map_type::iterator current = comands_.find(command);
				if (current != comands_.end())
				{
					if ((proccessor_.*(current->second))(context))
					{
						return context.input.good();
					}
				}
				parseAsError();
			}
			return context.input.good();
		}
		void parseAsError()
		{
			context.input.clear(context.input.rdstate() & ~std::ios::failbit);
			context.input.ignore(std::numeric_limits< std::streamsize >::max(), L'\n');
			context.error << L"Invalid comand\\input. Please check your input for the correct format. ";
			context.error << L"Words should not contain extra characters (*, _, =, etc.), ";
			context.error << L"as well as translations should consist of one word\n";
		}
	private:
		processor proccessor_;
		map_type comands_;
	};
}

#endif
