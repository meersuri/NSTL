#include <iostream>

#include "gtest/gtest.h"
#include "vector.h"

TEST(InitTest, DefaultConstructorWorks) {
    nstd::vector<int> v;
    EXPECT_EQ(v.size(), 0);
    EXPECT_EQ(v.capacity(), 1);
}

TEST(InitTest, CopyConstructorWorks) {
    nstd::vector<int> v(7, -2);
    nstd::vector<int> v2(v);
    ASSERT_EQ(v2.size(), v.size());
    ASSERT_EQ(v2.capacity(), v.capacity());
    for (int i = 0; i < 7; ++i)
        ASSERT_EQ(v[i], v2[i]);
    for (int i = 0; i < 7; ++i) {
        v2[i] = i;
        ASSERT_EQ(v2[i], i);
        ASSERT_EQ(v[i], -2);
    }
}

TEST(InitTest, MoveConstructorWorks) {
    nstd::vector<int> v(7, -2);
    nstd::vector<int> v2(std::move(v));
    ASSERT_EQ(v.size(), 0);
    ASSERT_EQ(v.capacity(), 0);
    ASSERT_EQ(v2.size(), 7);
    for (int i = 0; i < 7; ++i)
        ASSERT_EQ(v2[i], -2);
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
