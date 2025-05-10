#include <iostream>
#include <string>
#include <cstring>
#include "src/initial_test.hpp"
#include "map.hpp"
#include "set.hpp"

#include <cassert>

template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::size_type
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::black_height(const_iterator iter) const noexcept
{
	if (iter.data_ == nullptr)
	{
		return 0;
	}
	size_type left = black_height({iter.data_->left_, max_});
	size_type right = black_height({iter.data_->right_, max_});
	assert(left == right);
	return left + !iter.data_->isRed_;
}

template< class Key, class Mapped, class Compare, class Value, class ValueCompare >
src::details::map_node_t< typename src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::value_type >*
src::details::MapBase< Key, Mapped, Compare, Value, ValueCompare >::root() const noexcept
{
	return root_;
}

void print(src::details::map_node_t< src::Pair< const int, int > >* node, size_t level)
{
	if (node == nullptr)
	{
		return;
	}
	print(node->left_, level + 1);
	std::cout << std::string("\t\t\t\t", level) << node->value_.first << ' ' << node->value_.second
			<< ": " << (node->isRed_ ? 'R' : 'B') << '\n';
	print(node->right_, level + 1);
}
void print(src::details::map_node_t< int >* node, size_t level)
{
	if (node == nullptr)
	{
		return;
	}
	print(node->left_, level + 1);
	std::cout << std::string("\t\t\t\t", level) << node->value_
	          << ": " << (node->isRed_ ? 'R' : 'B') << '\n';
	print(node->right_, level + 1);
}

void map_base_testing()
{
	src::Map< int, int > map;
	map.insert({1, 0});
	print(map.root(), 0);
	std::cout << "---" << std::endl;
	map.insert({0, 0});
	print(map.root(), 0);
	std::cout << "---" << std::endl;
	map.insert({11, 0});
	print(map.root(), 0);
	std::cout << "---" << std::endl;
	map.insert({-3, 0});
	print(map.root(), 0);
	std::cout << "---" << std::endl;
	map.insert({32, 0});
	print(map.root(), 0);
	std::cout << "---" << std::endl;
	map.insert({22, 0});
	print(map.root(), 0);
	std::cout << "---" << std::endl;
	map.insert({-34, 0});
	print(map.root(), 0);
	std::cout << "---" << std::endl;
	map.insert({-556, 0});
	print(map.root(), 0);
	std::cout << "---" << std::endl;
	map.insert({2, 0});
	print(map.root(), 0);
	std::cout << "---" << std::endl;
	map.insert({3, 0});
	print(map.root(), 0);
	std::cout << "---" << std::endl;
	map.insert({4, 0});
	print(map.root(), 0);
	std::cout << "---" << std::endl;
	map.insert({5, 0});
	print(map.root(), 0);
	std::cout << "---" << std::endl;
	map.insert({6, 0});
	print(map.root(), 0);
	std::cout << "---" << std::endl;
	map.insert({7, 0});
	print(map.root(), 0);
	std::cout << "---" << std::endl;
	map.insert({1, 0});
	print(map.root(), 0);
	std::cout << "---" << std::endl;
	std::cout << "---map---\n";
	for (auto i = map.begin(); i != map.end(); ++i)
	{
		std::cout << i->first << ' ' << i->second << ": " << map.black_height(i) << '\n';
	}
	std::cout << "---------------------------\n";
	print(map.root(), 0);
	src::Set< int > set;
	set.insert(1);
	set.insert(-1);
	set.insert(3);
	set.insert(2);
	std::cout << "---set---\n";
	for (auto i: set)
	{
		std::cout << i << '\n';
	}
	std::cout << "---\n";
	print(set.root(), 0);
	std::cout << "---erase---\n";
	std::cout << set.erase(3) << '\n';
	std::cout << "---\n";
	for (auto i: set)
	{
		std::cout << i << '\n';
	}
	std::cout << "---\n";
	std::cout << set.erase(1) << '\n';
	std::cout << "---\n";
	for (auto i: set)
	{
		std::cout << i << '\n';
	}
	std::cout << "---\n";
	print(set.root(), 0);
}


int main(int argc, char** argv)
{
	if (argc <= 1)
	{
		std::cerr << "File wasn't found\n";
		return 1;
	}
	std::cout << "File was found\n";
	if (std::strcmp(argv[1], "../.github/tests/input/input_3.txt") == 0)
	{
		std::cout << "It was a plan\n";
	}
	return 0;
	map_base_testing();
}
