#include <gtest/gtest.h>
#include "../src/map.hpp"

#include <vector>
#include "pair.hpp"

struct A
{
	int a;
};

struct ACompare
{
	bool operator()(const A& lhs, const A& rhs)
	{
		return lhs.a < rhs.a;
	}
};

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
void print(src::details::map_node_t< src::Pair< const int, char > >* node, size_t level)
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

TEST(map_construct, default)
{
	src::Map< int, char > map;
	ASSERT_EQ(map.size(), 0);
}
TEST(map_insert, insert)
{
	src::Map< int, char > map;
	ASSERT_EQ(map.size(), 0);
	map.insert({1, 'a'});
	map.insert({2, 'b'});
	map.insert({-1, 'c'});
	map.insert({-2, 'd'});
	map.insert({1, 'a'});
	ASSERT_EQ(map.size(), 4);
}
TEST(map_construct, compare)
{
	// bug
	ACompare comp;
	src::Map< A, int, ACompare > map(comp);
	ASSERT_EQ(map.size(), 0);
}
TEST(map_construct, input_iterator)
{
	std::vector< src::Pair< const int, char > > vec = {{1, 'a'}, {2, 'b'}, {-1, 'c'}, {-2, 'd'}};
	src::Map< int, char > map(vec.begin(), vec.end());
	ASSERT_EQ(map.size(), 4);
	ASSERT_EQ(map.begin()->first, -2);
	ASSERT_EQ(map.begin()->second, 'd');
	ASSERT_EQ((--(map.end()))->first, 2);
	ASSERT_EQ((--(map.end()))->second, 'b');
}
TEST(map_construct, initializer_list)
{
	src::Map< int, char > map({{1, 'a'}, {2, 'b'}, {-1, 'c'}});
	ASSERT_EQ(map.size(), 3);
}
TEST(map_construct, copy)
{
	src::Map< int, char > map({{1, 'a'}, {2, 'b'}, {-1, 'c'}});
	src::Map< int, char > cMap(map);
	ASSERT_EQ((cMap.begin())->first, (map.begin())->first);
	ASSERT_EQ((cMap.begin())->second, (map.begin())->second);
	ASSERT_EQ(map.size(), cMap.size());
}
TEST(map_construct, move)
{
	src::Map< int, char > map({{1, 'a'}, {2, 'b'}, {-1, 'c'}});
	size_t mapSize = map.size();
	char mapFirst = map.begin()->second;
	src::Map< int, char > mMap(std::move(map));
	ASSERT_EQ(map.size(), 0);
	ASSERT_EQ(mapSize, mMap.size());
	ASSERT_EQ(mMap.begin()->second, mapFirst);
}

TEST(map_access, iterators)
{
	src::Map< int, char > map({{1, 'a'}, {2, 'b'}, {3, 'c'}});
	ASSERT_EQ(map.begin()->first, 1);
	ASSERT_EQ(map.begin()->second, 'a');
	ASSERT_EQ((--map.end())->first, 3);
	ASSERT_EQ((--map.end())->second, 'c');
}
TEST(map_access, reverse_iterators)
{
	src::Map< int, char > map({{1, 'a'}, {2, 'b'}, {3, 'c'}});
	ASSERT_EQ(map.rbegin()->first, 3);
	ASSERT_EQ(map.rbegin()->second, 'c');
	ASSERT_EQ((--map.rend())->first, 1);
	ASSERT_EQ((--map.rend())->second, 'a');
}
TEST(map_access, finds)
{
	src::Map< int, char > map({{1, 'a'}, {2, 'b'}, {3, 'c'}});
	ASSERT_TRUE(map.contains(1));
	ASSERT_FALSE(map.contains(-1));
	ASSERT_THROW(map.at(-1), std::out_of_range);
	ASSERT_NO_THROW(map.at(2));
	ASSERT_EQ(map[1], 'a');
	ASSERT_EQ(map.find(-3), map.end());
	ASSERT_NE(map.find(3), map.end());
	ASSERT_EQ(map.lower_bound(1)->first, 1);
	ASSERT_EQ(map.lower_bound(1)->second, 'a');
	ASSERT_EQ(map.upper_bound(1)->first, 2);
	ASSERT_EQ(map.upper_bound(1)->second, 'b');
}
TEST(map_access, other)
{
	src::Map< int, char > map;
	ASSERT_TRUE(map.empty());
	ASSERT_EQ(map.size(), 0);
	map = {{1, 'a'}, {2, 'b'}, {3, 'c'}};
	ASSERT_FALSE(map.empty());
	ASSERT_EQ(map.size(), 3);
}

TEST(map_modifiers, emplaces)
{
	src::Map< int, char > map;
	ASSERT_TRUE(map.empty());
	map.emplace(1, 'a');
	ASSERT_FALSE(map.empty());
	ASSERT_EQ(map.emplace(1, 'a'), map.end());
	ASSERT_EQ(map.size(), 1);
	ASSERT_TRUE(map.insert({2, 'b'}).second);
	ASSERT_FALSE(map.insert({2, 'b'}).second);
}
TEST(map_modifiers, other)
{
	src::Map< int, char > map = {{0, 'c'}, {3, 'd'}, {-3, 'k'}};
	src::Map< int, char > map1;
	ASSERT_TRUE(map1.empty() && !map.empty());
	map1.swap(map);
	ASSERT_TRUE(map.empty() && !map1.empty());
	ASSERT_EQ(map1.size(), 3);
	std::swap(map, map1);
	ASSERT_TRUE(map1.empty() && !map.empty());
	ASSERT_EQ(map.size(), 3);
	map.clear();
	ASSERT_TRUE(map.empty());
}

TEST(map_modifiers, errase)
{
	src::Map< int, char > map = {{0, 'c'}, {3, 'd'}, {-3, 'k'}};
	ASSERT_EQ(map.erase(0), 1);
	ASSERT_EQ(map.erase(3), 1);
	ASSERT_EQ(map.size(), 1);
	ASSERT_THROW(map.at(3), std::out_of_range);
}
