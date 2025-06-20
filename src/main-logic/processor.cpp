#include "processor.hpp"

#include <algorithm>
#include <iterator>
#include <fstream>
#include <functional>
#include <numeric>
#include <limits>
#include "parser.hpp"

bool src::MainProcessor::init(Context& context, int argc, char** argv)
{
	if (argc != 2)
	{
		return false;
	}
	std::ifstream file(argv[1]);
	if (!file)
	{
		return false;
	}
	while (file)
	{
		file >> context.dict;
		file.clear(file.rdstate() & ~std::ios::failbit);
		file.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
	}
	return true;
}

bool src::MainProcessor::help(Context& context)
{
	context.output << "HELP — help menu\n";
	context.output << "ADD WORD [word]: [translate], [translate], [...], [translate]; — add new word\n";
	context.output << "ADD TRANSLATE [word in dictionary]: [translate], [...], [translate];"
			<<" — add translate(s) to word\n";
	context.output << "REMOVE WORD [word] — remove word from dictionary\n";
	context.output << "REMOVE TRANSLATE [word]: [translate], [...], [translate]; "
			<< "— remove word translate(s) from dictionary\n";
	context.output << "CLEAR — clear dictionary\n";
	context.output << "PRINT DICT — print dictionary\n";
	context.output << "PRINT WORD [word] — print word and translates from dictionary\n";
	return true;
}
bool src::MainProcessor::add(Context& context)
{
	static Parser< AddProcessor >::map_type comands = {
		{"TRANSLATE", &AddProcessor::add_translate},
		{"WORD", &AddProcessor::add_word},
	};
	static Parser< AddProcessor > parser({}, context, std::move(comands));
	return parser.run();
}
bool src::MainProcessor::remove(Context& context)
{
	static Parser< RemoveProcessor >::map_type comands = {
		{"TRANSLATE", &RemoveProcessor::remove_translate},
		{"WORD", &RemoveProcessor::remove_word},
	};
	static Parser< RemoveProcessor > parser({}, context, std::move(comands));
	return parser.run();
}
bool src::MainProcessor::print(Context& context)
{
	static Parser< PrintProcessor >::map_type comands = {
		{"WORD", &PrintProcessor::print_word},
		{"DICT", &PrintProcessor::print_dict},
	};
	static Parser< PrintProcessor > parser({}, context, std::move(comands));
	return parser.run();
}

bool src::AddProcessor::add_word(Context& context)
{
	std::string word;
	Translates translates;
	if (!(context.input >> word >> translates) || word.back() != ':')
	{
		return false;
	}
	word.pop_back();
	if (!(context.dict.dictionary.insert({word, std::move(translates)}).second))
	{
		context.error << "Word was already added\n";
	}
	else
	{
		context.output << word << " added\n";
	}
	return true;
}
bool src::AddProcessor::add_translate(Context& context)
{
	std::string word;
	if (!(context.input >> word) || word.back() != ':')
	{
		return false;
	}
	word.pop_back();
	auto it = context.dict.dictionary.find(word);
	if (it != context.dict.dictionary.end())
	{
		size_t sizeBefore = it->second.translates.size();
		if (context.input >> it->second)
		{
			context.output << (it->second.translates.size() - sizeBefore)
					<< " translate(s) was added to word " << word << '\n';
		}
		else
		{
			return false;
		}
	}
	else
	{
		context.input.clear(context.input.rdstate() & ~std::ios::failbit);
		context.input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
		context.error << word << " wasn't found\n";
	}
	return true;
}

bool src::RemoveProcessor::remove_word(Context& context)
{
	std::string word;
	context.input >> word;
	auto it = context.dict.dictionary.find(word);
	if (it == context.dict.dictionary.end())
	{
		context.error << word << " wasn't found\n";
	}
	else
	{
		context.dict.dictionary.erase(it->first);
		context.output << word << " was removed\n";
	}
	return true;
}
bool src::RemoveProcessor::remove_translate(Context& context)
{
	std::string word;
	if (!(context.input >> word) || word.back() != ':')
	{
		return false;
	}
	Translates translates;
	if (!(context.input >> translates))
	{
		return false;
	}
	word.pop_back();
	auto it = context.dict.dictionary.find(word);
	if (it == context.dict.dictionary.end())
	{
		context.error << word << " wasn't found\n";
		return true;
	}
	size_t sizeBefore = it->second.translates.size();
	for (auto i: translates.translates)
	{
		it->second.translates.erase(i);
	}
	context.output << (sizeBefore - it->second.translates.size()) << " translate(s) was deleted\n";
	return true;
}

bool src::PrintProcessor::print_dict(Context& context)
{
	if (context.dict.dictionary.empty())
	{
		context.error << "Dictionary is empty\n";
		return true;
	}
	for (auto i: context.dict.dictionary)
	{
		context.output << i.first << ": " << i.second << '\n';
	}
	context.output << "Total: " << context.dict.dictionary.size() << " words\n";
	return true;
}
bool src::PrintProcessor::print_word(Context& context)
{
	if (context.dict.dictionary.empty())
	{
		context.error << "Dictionary is empty\n";
		context.input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
		return true;
	}
	std::string word;
	if (!(context.input >> word))
	{
		return false;
	}
	auto it = context.dict.dictionary.find(word);
	if (it == context.dict.dictionary.end())
	{
		context.error << word << " wasn't found\n";
	}
	else
	{
		context.output << word << ": " << it->second << '\n';
	}
	return true;
}

bool src::MainProcessor::clear(Context& context)
{
	if (context.dict.dictionary.empty())
	{
		context.error << "Dictionary is already empty\n";
	}
	else
	{
		context.dict.dictionary.clear();
		context.output << "Dictionary has been completely cleaned up\n";
	}
	return true;
}
