#ifndef DICT_HPP
#define DICT_HPP

#include <iosfwd>
#include <map>
#include <set>
#include <string>

namespace src
{
	struct Translates
	{
		std::set< std::string > translates;
	};
	std::istream& operator>>(std::istream& in, Translates& translates);
	std::ostream& operator<<(std::ostream& out, const Translates& translates);
	struct Dictionary
	{
		std::map< std::string, Translates > dictionary;
	};
	std::istream& operator>>(std::istream& in, Dictionary& dictionary);
	std::ostream& operator<<(std::ostream& out, const Dictionary& dictionary);
}

#endif
