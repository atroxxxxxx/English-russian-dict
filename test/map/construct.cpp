#include <gtest/gtest.h>
#include "../../src/map.hpp"

#include <vector>
#include "../../src/pair.hpp"

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

TEST(map, default_construct)
{
	src::Map< int, char > map;
	ASSERT_EQ(map.size(), 0);
}
TEST(map, insert)
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
TEST(map, compare_construct)
{
	// bug
	ACompare comp;
	src::Map< A, int, ACompare > map(comp);
	ASSERT_EQ(map.size(), 0);
}
TEST(map, input_iterator_construct)
{
	std::vector< src::Pair< const int, char > > vec = {{1, 'a'}, {2, 'b'}, {-1, 'c'}, {-2, 'd'}};
	src::Map< int, char > map(vec.begin(), vec.end());
	ASSERT_EQ(map.size(), 4);
	ASSERT_EQ(map.begin()->first, -2);
	ASSERT_EQ(map.begin()->second, 'd');
	ASSERT_EQ((--(map.end()))->first, 2);
	ASSERT_EQ((--(map.end()))->second, 'b');
}
TEST(map, initializer_list_construct)
{
	src::Map< int, char > map({{1, 'a'}, {2, 'b'}, {-1, 'c'}});
	ASSERT_EQ(map.size(), 3);
}
TEST(map, copy_construct)
{
	src::Map< int, char > map({{1, 'a'}, {2, 'b'}, {-1, 'c'}});
	src::Map< int, char > cMap(map);
	ASSERT_EQ((cMap.begin())->first, (map.begin())->first);
	ASSERT_EQ((cMap.begin())->second, (map.begin())->second);
	ASSERT_EQ(map.size(), cMap.size());
}
TEST(map, move_construct)
{
	src::Map< int, char > map({{1, 'a'}, {2, 'b'}, {-1, 'c'}});
	size_t mapSize = map.size();
	char mapFirst = map.begin()->second;
	src::Map< int, char > mMap(std::move(map));
	ASSERT_EQ(map.size(), 0);
	ASSERT_EQ(mapSize, mMap.size());
	ASSERT_EQ(mMap.begin()->second, mapFirst);
}
