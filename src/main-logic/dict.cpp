#include "../dict.hpp"
#include <iostream>

std::istream& src::operator>>(std::istream& in, Dictionary& dictionary)
{
	std::istream::sentry sentry(in);
	if (!sentry)
	{
		return in;
	}
	std::string word;
	if (!(in >> word) || (word[word.size() - 1] != ':'))
	{
		in.setstate(std::ios::failbit);
		return in;
	}
	word.pop_back();
	Translates translates;
	if (!(in >> translates))
	{
		in.setstate(std::ios::failbit);
		return in;
	}
	dictionary.dictionary[word] = std::move(translates);
	return in;
}

std::istream& src::operator>>(std::istream& in, Translates& translates)
{
	std::istream::sentry sentry(in);
	if (!sentry)
	{
		return in;
	}
	std::string translate;
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
		translates.translates.insert(translate);
		count++;
	}
	if (count == 0)
	{
		in.setstate(std::ios::failbit);
	}
	return in;
}

std::ostream& src::operator<<(std::ostream& out, const src::Translates& translates)
{
	size_t count = 1;
	size_t size = translates.translates.size();
	for (auto i = translates.translates.begin(); i != translates.translates.end(); ++i, ++count)
	{
		out << *i << (count == size ? ";" : ", ");
	}
	return out;
}
