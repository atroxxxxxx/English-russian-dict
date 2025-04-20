#include <gtest/gtest.h>
#include <initial_test.hpp>

TEST(init, out)
{
	EXPECT_STREQ(init::initialString(), "initial test");
}
