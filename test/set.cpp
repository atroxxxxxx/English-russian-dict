#include <gtest/gtest.h>
#include "set.hpp"

#include <vector>
#include "pair.hpp"

TEST(set_construct, default)
{
	src::Set< int > set;
	ASSERT_EQ(set.size(), 0);
}
TEST(set_insert, insert)
{
	src::Set< int > set;
	ASSERT_EQ(set.size(), 0);
	set.insert(1);
	set.insert(2);
	set.insert(-1);
	set.insert(-2);
	set.insert(1);
	ASSERT_EQ(set.size(), 4);
}
TEST(set_construct, initializer_list)
{
	src::Set< int > set({1, 2, -1});
	ASSERT_EQ(set.size(), 3);
}
TEST(set_construct, copy)
{
	src::Set< int > set({1, 2, -1});
	src::Set< int > cSet(set);
	ASSERT_EQ(*cSet.begin(), *set.begin());
	ASSERT_EQ(set.size(), cSet.size());
}
TEST(set_construct, move)
{
	src::Set< int > set({1, 2, -1});
	size_t setSize = set.size();
	int setFirst = *set.begin();
	src::Set< int > mSet(std::move(set));
	ASSERT_EQ(set.size(), 0);
	ASSERT_EQ(setSize, mSet.size());
	ASSERT_EQ(*mSet.begin(), setFirst);
}

TEST(set_access, iterators)
{
	src::Set< int > set({1, 2, 3});
	ASSERT_EQ(*set.begin(), 1);
	ASSERT_EQ(*(--set.end()), 3);
}
TEST(set_access, reverse_iterators)
{
	src::Set< int > set({1, 2, 3});
	ASSERT_EQ(*set.rbegin(), 3);
	ASSERT_EQ(*(--set.rend()), 1);
}
TEST(set_access, finds)
{
	src::Set< int > set({1, 2, 3});
	ASSERT_TRUE(set.contains(1));
	ASSERT_FALSE(set.contains(-1));;
	ASSERT_NE(set.find(3), set.end());
	ASSERT_EQ(*set.lower_bound(1), 1);
	ASSERT_EQ(*set.upper_bound(1), 2);
}
TEST(set_access, other)
{
	src::Set< int > set;
	ASSERT_TRUE(set.empty());
	ASSERT_EQ(set.size(), 0);
	set = {1, 2, 3};
	ASSERT_FALSE(set.empty());
	ASSERT_EQ(set.size(), 3);
}

TEST(set_modifiers, emplaces)
{
	src::Set< int > set;
	ASSERT_TRUE(set.empty());
	set.emplace(1);
	ASSERT_FALSE(set.empty());
	ASSERT_EQ(set.emplace(1), set.end());
	ASSERT_EQ(set.size(), 1);
	ASSERT_TRUE(set.insert(2).second);
	ASSERT_FALSE(set.insert(2).second);
}
TEST(set_modifiers, other)
{
	src::Set< int > set = {0, 3, -3};
	src::Set< int > set1;
	ASSERT_TRUE(set1.empty() && !set.empty());
	set1.swap(set);
	ASSERT_TRUE(set.empty() && !set1.empty());
	ASSERT_EQ(set1.size(), 3);
	std::swap(set, set1);
	ASSERT_TRUE(set1.empty() && !set.empty());
	ASSERT_EQ(set.size(), 3);
	set.clear();
	ASSERT_TRUE(set.empty());
}

TEST(set_modifiers, errase)
{
	src::Set< int > set = {0, 3, -3};
	ASSERT_EQ(set.erase(0), 1);
	ASSERT_EQ(set.erase(3), 1);
	ASSERT_EQ(set.size(), 1);
	ASSERT_FALSE(set.contains(3));
	ASSERT_TRUE(set.contains(-3));
}
