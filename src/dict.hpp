#ifndef DICT_HPP
#define DICT_HPP

#include <iosfwd>
#include <string>

#include "map.hpp"
#include "set.hpp"

namespace src
{
	struct Translates
	{
		src::Set< std::string > translates;
	};
	std::istream& operator>>(std::istream& in, Translates& translates);
	std::ostream& operator<<(std::ostream& out, const Translates& translates);
	struct Dictionary
	{
		src::Map< std::string, Translates > dictionary;
	};
	std::istream& operator>>(std::istream& in, Dictionary& dictionary);
	std::ostream& operator<<(std::ostream& out, const Dictionary& dictionary);
}

#endif
