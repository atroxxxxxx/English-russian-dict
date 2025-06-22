#include "processor.hpp"

#include <fstream>
#include <numeric>
#include <limits>
#include <locale>
#include "parser.hpp"

bool src::MainProcessor::init(Context& context, int argc, char** argv)
{
	if (argc != 2)
	{
		return false;
	}
	std::wifstream file(argv[1]);
	if (!file)
	{
		return false;
	}
	file.imbue(std::locale("en_US.UTF-8"));
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
	context.output << L"HELP — help menu\n";
	context.output << L"ADD WORD [word]: [translate], [translate], [...], [translate]; — add new word\n";
	context.output << L"ADD TRANSLATE [word in dictionary]: [translate], [...], [translate];"
			<< L" — add translate(s) to word\n";
	context.output << L"LREMOVE WORD [word] — remove word from dictionary\n";
	context.output << L"REMOVE TRANSLATE [word]: [translate], [...], [translate];"
			<< L" — remove word translate(s) from dictionary\n";
	context.output << L"CLEAR — clear dictionary\n";
	context.output << L"PRINT DICT — print dictionary\n";
	context.output << L"PRINT WORD [word] — print word and translates from dictionary\n";
	context.output << L"SAVE — save dictionary\n";
	context.output << L"CTRL + D on Linux or CTRL + Z on Windows to close dictionary\n";
	return true;
}
bool src::MainProcessor::add(Context& context)
{
	static Parser< AddProcessor >::map_type comands = {
		{L"TRANSLATE", &AddProcessor::add_translate},
		{L"WORD", &AddProcessor::add_word},
	};
	static Parser< AddProcessor > parser({}, context, std::move(comands));
	return parser.run();
}
bool src::MainProcessor::remove(Context& context)
{
	static Parser< RemoveProcessor >::map_type comands = {
		{L"TRANSLATE", &RemoveProcessor::remove_translate},
		{L"WORD", &RemoveProcessor::remove_word},
	};
	static Parser< RemoveProcessor > parser({}, context, std::move(comands));
	return parser.run();
}
bool src::MainProcessor::print(Context& context)
{
	static Parser< PrintProcessor >::map_type comands = {
		{L"WORD", &PrintProcessor::print_word},
		{L"DICT", &PrintProcessor::print_dict},
	};
	static Parser< PrintProcessor > parser({}, context, std::move(comands));
	return parser.run();
}

bool src::AddProcessor::add_word(Context& context)
{
	std::wstring word;
	Translates translates;
	if (!(context.input >> word >> translates) || word.back() != ':')
	{
		return false;
	}
	word.pop_back();
	if (!parse_en_string(word))
	{
		return false;
	}
	if (!(context.dict.dictionary.insert({word, std::move(translates)}).second))
	{
		context.error << L"Word was already added\n";
	}
	else
	{
		context.output << word << L" added\n";
	}
	return true;
}
bool src::AddProcessor::add_translate(Context& context)
{
	std::wstring word;
	if (!(context.input >> word) || word.back() != ':')
	{
		return false;
	}
	word.pop_back();
	if (!parse_en_string(word))
	{
		return false;
	}
	auto it = context.dict.dictionary.find(word);
	if (it != context.dict.dictionary.end())
	{
		size_t sizeBefore = it->second.translates.size();
		if (context.input >> it->second)
		{
			context.output << (it->second.translates.size() - sizeBefore)
					<< L" translate(s) was added to word " << word << '\n';
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
		context.error << word << L" wasn't found\n";
	}
	return true;
}

bool src::RemoveProcessor::remove_word(Context& context)
{
	std::wstring word;
	context.input >> word;
	if (!parse_en_string(word))
	{
		return false;
	}
	auto it = context.dict.dictionary.find(word);
	if (it == context.dict.dictionary.end())
	{
		context.error << word << L" wasn't found\n";
	}
	else
	{
		context.dict.dictionary.erase(it->first);
		context.output << word << L" was removed\n";
	}
	return true;
}
bool src::RemoveProcessor::remove_translate(Context& context)
{
	std::wstring word;
	if (!(context.input >> word) || word.back() != ':')
	{
		return false;
	}
	word.pop_back();
	Translates translates;
	if (!parse_en_string(word) || !(context.input >> translates))
	{
		return false;
	}
	auto it = context.dict.dictionary.find(word);
	if (it == context.dict.dictionary.end())
	{
		context.error << word << L" wasn't found\n";
		return true;
	}
	size_t sizeBefore = it->second.translates.size();
	for (auto i: translates.translates)
	{
		it->second.translates.erase(i);
	}
	if (it->second.translates.empty())
	{
		context.output << L"0 translates to word " << word << ". This word will be delete from dictionary\n";
		context.dict.dictionary.erase(it);
	}
	else
	{
		context.output << (sizeBefore - it->second.translates.size()) << L" translate(s) was deleted\n";
	}
	return true;
}

bool src::PrintProcessor::print_dict(Context& context)
{
	if (context.dict.dictionary.empty())
	{
		context.error << L"Dictionary is empty\n";
		return true;
	}
	context.output << context.dict;
	context.output << L"Total: " << context.dict.dictionary.size() << " words\n";
	return true;
}
bool src::PrintProcessor::print_word(Context& context)
{
	if (context.dict.dictionary.empty())
	{
		context.error << L"Dictionary is empty\n";
		context.input.ignore(std::numeric_limits< std::streamsize >::max(), '\n');
		return true;
	}
	std::wstring word;
	if (!(context.input >> word) || !parse_en_string(word))
	{
		return false;
	}
	auto it = context.dict.dictionary.find(word);
	if (it == context.dict.dictionary.end())
	{
		context.error << word << L" wasn't found\n";
	}
	else
	{
		context.output << word << L": " << it->second << '\n';
	}
	return true;
}

bool src::MainProcessor::clear(Context& context)
{
	if (context.dict.dictionary.empty())
	{
		context.error << L"Dictionary is already empty\n";
	}
	else
	{
		context.dict.dictionary.clear();
		context.output << L"Dictionary has been completely cleaned up\n";
	}
	return true;
}

bool src::MainProcessor::save(Context& context)
{
	if (context.dict.dictionary.empty())
	{
		context.error << L"Dictionary is empty, nothing to save\n";
	}
	else
	{
		std::wofstream out("dictionary.txt");
		out.imbue(std::locale("en_US.UTF-8"));
		out << context.dict;
		out << L"Total: " << context.dict.dictionary.size() << L" words\n";
		out.close();
		context.output << L"Dictionary was successfully saved into current directory with name \"dictionary.txt\"\n";
	}
	return true;
}
