#include "../parser.hpp"
#include "format_guard.hpp"

#include <iterator>

void src::Parser::help()
{

	if (!check_trailing())
	{
		error_ << "this command don't have arguments\n";
		return;
	}
	out_ << "Command list:\n";
	out_ << "\"HELP\": print command list\n";
	out_ << "\"CREATE_DICT [OPTIONAL[dict_name]]\": create a new dictionaty; returns the number of dictionary\n";
	out_ << "\"SELECT [dict_number]\": select current dictionary\n";
	out_ << "\"ADD [english_word]: [russian_word...]\": insert word\\translate to word\n";
	out_ << "\"SEARCH [english_word]\": search word and print translations\n";
	out_ << "\"DELETE [english_word]\": delete word from dictionary\n";
	out_ << "\"DELETE_TRANSLATE [english_word]: [russian_word...]\": delete translation(s) from word\n";
	out_ << "\"DELETE_DICT [dict_number]\": delete dictionary\n";
	out_ << "\"EXIT\": finish session\n";
}

void src::Parser::create_dict()
{
	std::string name;
	std::getline(in_, name, '\n');
	if (!in_ || !name.empty())
	{
		name.erase(0, 1);
		dictionaries_.emplace_back(name, dictionary());
		out_ << "Created \"" << dictionaries_[dictionaries_.size() - 1].first
		     << "\" whith number: " << (dictionaries_.size() - 1) << '\n';
	}
	else
	{
		dictionaries_.emplace_back("<untitled>", dictionary());
		out_ << "Created untiled whith number: " << (dictionaries_.size() - 1) << '\n';
	}
}

void src::Parser::select()
{
	size_t number = 0;
	if (dictionaries_.empty())
	{
		error_ << "There is no dictionaries\n";
		return;
	}
	char c = '\0';
	if (!(in_ >> std::noskipws >> c >> number >> std::skipws) || !check_trailing())
	{
		error_ << "Invalid format\n";
		return;
	}
	else if (number > dictionaries_.size())
	{
		error_ << "Dictionary with this number is not found\n";
		return;
	}
	current_ = &dictionaries_[number];
	out_ << "Selected dictionary number " << number
	     << (current_->first == "<untitled>" ? " without name" : "with name " + current_->first) << '\n';
}

void src::Parser::add()
{
	if (!current_)
	{
		error_ << "No dictionaries selected\n";
		return;
	}
	std::string word;
	if (!(in_ >> word) || (word[word.size() - 1] != ':'))
	{
		error_ << "English word is not entered\n";
		return;
	}
	word.pop_back();
	std::vector< std::string > translates;
	std::string temp;
	while (in_.peek() != '\n')
	{
		in_ >> temp;
		translates.push_back(temp);
	}
	if (translates.empty())
	{
		error_ << "There is no translates entered\n";
		return;
	}
	for (const std::string& i: translates)
	{
		current_->second[word].insert({i, {}});
	}
	out_ << '"' << word << "\" added to the dictionary\n"; // add name to dict
}

void src::Parser::search()
{
	if (!current_ || current_->second.empty())
	{
		error_ << "Dictionary is not found\n";
		return;
	}
	std::string word;
	if (!(in_ >> word) || !check_trailing())
	{
		error_ << "Invalid format\n";
		return;
	}
	auto wordIter = current_->second.find(word);
	if (wordIter == current_->second.end())
	{
		error_ << '"' << word << "\" is not found\n";
		return;
	}
	out_ << '"' << word << "\" found\nTranslates:";
	for (std::pair< std::string, Empty > translate: current_->second[word])
	{
		out_ << ' ' << translate.first;
	}
	out_ << '\n';
}
void src::Parser::delete_word()
{
	if (!current_)
	{
		error_ << "No dictionaries selected\n";
		return;
	}
	std::string word;
	if (!(in_ >> word) || !check_trailing())
	{
		error_ << "Invalid format\n";
		return;
	}
	auto treeIter = current_->second.find(word);
	if (treeIter == current_->second.end())
	{
		error_ << '"' << word << "\" is not found\n";
		return;
	}
	current_->second.erase(treeIter);
	out_ << '"' << word << "\" was deleted";
}
void src::Parser::exit()
{
	if (!check_trailing())
	{
		error_ << "this command don't have arguments\n";
		return;
	}
	allOk_ = false;
}
bool src::Parser::all_ok()
{
	return allOk_;
}
bool src::Parser::check_trailing()
{
	std::string trailing;
	std::getline(in_, trailing);
	return trailing.empty();
}
