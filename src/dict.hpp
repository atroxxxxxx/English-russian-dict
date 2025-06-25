#ifndef DICT_HPP
#define DICT_HPP

#include <iosfwd>
#include <string>
#include <map>
#include <set>

namespace src
{
	struct Translates
	{
		std::set< std::wstring > translates;
	};
	std::wistream& operator>>(std::wistream& in, Translates& translates);
	std::wostream& operator<<(std::wostream& out, const Translates& translates);
	struct Dictionary
	{
		std::map< std::wstring, Translates > dictionary;
	};
	std::wistream& operator>>(std::wistream& in, Dictionary& dictionary);
	std::wostream& operator<<(std::wostream& out, const Dictionary& dictionary);
}

#endif
