#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>

namespace src
{
	class Parser
	{
	public:
		Parser() = default;
		Parser(const Parser& rhs) = delete;

		void print_help();
		void create_dict();
		void select();
		void add();
		void search();
		void delete_word();
		void delete_translate();
		void delete_dict();
		void exit();

	private:
		using dictionary = std::map< std::string, std::set< std::string > >;
		using named_dictionary = std::pair< std::string, dictionary >;
		std::vector< named_dictionary > dictionaries_;
		named_dictionary current_;
		std::istream& in_ = std::cin;
		std::ostream& out_ = std::cout;
		std::ostream& error_ = std::cerr;
	};
	inline void printHelp(std::istream& = std::cin)
	{
		std::cout << "Command list:\n";
		std::cout << "\"HELP\": print command list\n";
		std::cout << "\"CREATE_DICT [OPTIONAL[dict_name]]\": create a new dictionaty; returns the number of dictionary\n";
		std::cout << "\"SELECT [dict_number]\": select current dictionary\n";
		std::cout << "\"ADD [english_word]: [russian_word...]\": insert word\\translate to word\n";
		std::cout << "\"SEARCH [english_word]\": search word and print translations\n";
		std::cout << "\"DELETE [english_word]\": delete word from dictionary\n";
		std::cout << "\"DELETE_TRANSLATE [english_word]: [russian_word...]\": delete translation(s) from word\n";
		std::cout << "\"DELETE_DICT [dict_number]\": delete dictionary\n";
		std::cout << "\"EXIT\": finish session\n";
	}

}

#endif
