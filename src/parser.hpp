#ifndef FUNCTIONS_HPP
#define FUNCTIONS_HPP

#include <iostream>
#include <vector>
#include <utility>
#include <map>
#include <set>
#include <string>

namespace src
{
	class Parser
	{
	public:
		Parser() = default;
		Parser(const Parser& rhs) = delete;

		void help();
		void create_dict();
		void select();
		void add();
		void search();
		void delete_word();
		void delete_translate();
		void delete_dict();
		void exit();

		bool all_ok();
	private:
		using dictionary = std::map< std::string, std::set< std::string > >;
		using named_dictionary = std::pair< std::string, dictionary >;
		std::vector< named_dictionary > dictionaries_;
		named_dictionary* current_ = nullptr;
		bool allOk_ = true;
		std::istream& in_ = std::cin;
		std::ostream& out_ = std::cout;
		std::ostream& error_ = std::cerr;

		bool check_trailing();
	};

}

#endif
