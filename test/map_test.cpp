#include <gtest/gtest.h>
#include "../src/map.hpp"

TEST(map_construct, default)
{
	src::RBTree< int, char > tree;
	ASSERT_TRUE(tree.empty());
	ASSERT_EQ(tree.size(), 0);
}

TEST(map_insert, root_insert)
{
	src::RBTree< int, char > tree;
	ASSERT_TRUE(tree.insert(1, 'a'));
	ASSERT_EQ(tree.size(), 1);
}
TEST(map_insert, red_insert)
{
	src::RBTree< int, char > tree;
	ASSERT_TRUE(tree.insert(1, 'a'));
	ASSERT_TRUE(tree.insert(2, 'b'));
	ASSERT_EQ(tree.size(), 2);
}

TEST(map_search, i_dont_know)
{
	src::RBTree< int, char > tree;
	ASSERT_TRUE(tree.insert(1, 'a'));
	ASSERT_TRUE(tree.insert(2, 'b'));
	ASSERT_EQ(*(tree.search(1).second), 'a');
}
