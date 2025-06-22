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
		src::Set< std::wstring > translates;
	};
	std::wistream& operator>>(std::wistream& in, Translates& translates);
	bool parse_ru_string(std::wstring word);
	std::wostream& operator<<(std::wostream& out, const Translates& translates);
	struct Dictionary
	{
		src::Map< std::wstring, Translates > dictionary;
	};
	std::wistream& operator>>(std::wistream& in, Dictionary& dictionary);
	bool parse_en_string(std::wstring word);
	std::wostream& operator<<(std::wostream& out, const Dictionary& dictionary);
}

#endif
