#include <iostream>

#include "gtest/gtest.h"
#include "vector.h"

TEST(InitTest, DefaultConstructorWorks) {
    nstd::vector<int> v;
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 1);
}

TEST(InitTest, SizeConstructorWorks) {
    nstd::vector<int> v(10);
    ASSERT_EQ(v.size(), 10);
    for (int i = 0; i < 10; ++i)
        EXPECT_EQ(v[i], 0);
}

TEST(VectorTest, AppendToEmptyVectorWorks) {
    nstd::vector<char> v;
    v.append('a');
    ASSERT_EQ(v.size(), 1);
    ASSERT_EQ(v[0], 'a');
}

TEST(VectorTest, AppendWorks) {
    nstd::vector<int> v;
    for (int i = 0; i < 20; ++i) {
        v.append(i);
        ASSERT_EQ(v[i], i);
        ASSERT_EQ(v.size(), i + 1);
    }
}

TEST(VectorTest, CapacityMoreThanSize) {
    nstd::vector<int> v;
    for (int i = 0; i < 10; ++i) {
        v.append(i);
        ASSERT_TRUE(v.capacity() >= v.size());
    }
}
