#include <gtest/gtest.h>
#include <vector.hpp>

TEST(vector_construct, default)
{
	src::Vector< int > vec;
	ASSERT_TRUE(vec.empty());
	ASSERT_EQ(vec.capacity(), 0);
}

TEST(vector_insert, push_rvalue)
{
	src::Vector< int > vec;
	vec.push_back(2);
	vec.push_back(3);
	vec.push_back(4);
	ASSERT_TRUE(vec.capacity() >= vec.size());
	ASSERT_EQ(vec[0], 2);
	ASSERT_EQ(vec[2], 4);
}
