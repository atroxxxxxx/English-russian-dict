#include <gtest/gtest.h>
#include "../src/initial_test.hpp"

TEST(init, init_out)
{
	EXPECT_STREQ(init::initialString(), "fail");
}
