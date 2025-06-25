#include "../dict.hpp"
#include <iostream>
#include <regex>

std::wistream& src::operator>>(std::wistream& in, Dictionary& dictionary)
{
	static const std::wregex pattern(L"^[A-Za-z_]+$");
	std::wistream::sentry sentry(in);
	if (!sentry)
	{
		return in;
	}
	std::wstring word;
	if (!(in >> word) || (word.back() != ':'))
	{
		in.setstate(std::ios::failbit);
		return in;
	}
	word.pop_back();
	Translates translates;
	if ((word.front() == L'_') || (word.back() == L'_') || !std::regex_match(word, pattern) || !(in >> translates))
	{
		in.setstate(std::ios::failbit);
		return in;
	}
	dictionary.dictionary[word] = std::move(translates);
	return in;
}
std::wostream& src::operator<<(std::wostream& out, const src::Dictionary& dictionary)
{
	for (auto i: dictionary.dictionary)
	{
		out << i.first << L": " << i.second << L'\n';
	}
	return out;
}

std::wistream& src::operator>>(std::wistream& in, Translates& translates)
{
	static const std::wregex pattern(L"^[А-ЯЁа-яё_]+$");
	std::wistream::sentry sentry(in);
	if (!sentry)
	{
		return in;
	}
	std::wstring translate;
	size_t count = 0;
	char separator = '\0';
	while (separator != ';')
	{
		if (!(in >> translate))
		{
			break;
		}
		separator = translate.back();
		if ((separator != ',') && (separator != ';'))
		{
			in.setstate(std::ios::failbit);
			break;
		}
		translate.pop_back();
		if (translate.front() == L'_' || translate.back() == L'_' || !std::regex_match(translate, pattern))
		{
			continue;
		}
		translates.translates.insert(translate);
		++count;
	}
	if (count == 0)
	{
		in.setstate(std::ios::failbit);
	}
	return in;
}
std::wostream& src::operator<<(std::wostream& out, const src::Translates& translates)
{
	size_t count = 1;
	size_t size = translates.translates.size();
	for (auto i = translates.translates.begin(); i != translates.translates.end(); ++i, ++count)
	{
		out << *i << (count == size ? L";" : L", ");
	}
	return out;
}
