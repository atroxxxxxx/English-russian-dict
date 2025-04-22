#include "../parser.hpp"

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
	char c = '\0';
	std::getline(in_ >> std::noskipws >> c >> std::skipws, name, '\n');
	if (!name.empty())
	{
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
	else if (!(in_ >> number) || !check_trailing())
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
