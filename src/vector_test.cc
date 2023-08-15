#include <iostream>

#include "gtest/gtest.h"
#include "vector.h"

TEST(VectorTest, DefaultConstructorWorks) {
    nstd::vector<int> v;
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 1);
}

TEST(VectorTest, SizeConstructorWorks) {
    nstd::vector<int> v(10);
    ASSERT_EQ(v.size(), 10);
    for (int i = 0; i < 10; ++i)
        EXPECT_EQ(v[i], 0);
}
