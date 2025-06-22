#include "../dict.hpp"
#include <iostream>

std::wistream& src::operator>>(std::wistream& in, Dictionary& dictionary)
{
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
	if ((word.front() == L'_') || (word.back() == L'_') || !parse_en_string(word) || !(in >> translates))
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

bool src::parse_en_string(std::wstring word)
{
	for (auto i: word)
	{
		if (!(((L'A' <= i) && (i <= L'Z')) || ((L'a' <= i) && (i <= L'z')) || (i == L'_')))
		{
			return false;
		}
	}
	return true;
}

std::wistream& src::operator>>(std::wistream& in, Translates& translates)
{
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
			in.setstate(std::ios::failbit);
			break;
		}
		separator = translate.back();
		if ((separator != ',') && (separator != ';'))
		{
			in.setstate(std::ios::failbit);
			break;
		}
		translate.pop_back();
		if (translate.front() == L'_' || translate.back() == L'_' || !parse_ru_string(translate))
		{
			continue;
		}
		translates.translates.insert(translate);
		count++;
	}
	if (count == 0)
	{
		in.setstate(std::ios::failbit);
	}
	return in;
}

bool src::parse_ru_string(std::wstring word)
{
	for (auto i: word)
	{
		if (!(((L'А' <= i) && (i <= L'Я')) || ((L'а' <= i) && (i <= L'я')) || (L'Ё' == i) || (L'ё' == i) || L'_' == i))
		{
			return false;
		}
	}
	return true;
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
