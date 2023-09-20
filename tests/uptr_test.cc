#include <iostream>
#include "gtest/gtest.h"
#include "uptr.h"

TEST(InitTests, DefaultConstructorWorks) {
    nstd::uptr<int> p;
    ASSERT_EQ(p.get(), nullptr);
}

TEST(InitTests, CopyAssignWorks) {
    auto p = nstd::make_uptr<int>(3);
    nstd::uptr<int> p2;
    p2 = std::move(p);
    ASSERT_EQ(p, nullptr);
    ASSERT_EQ(p.get(), nullptr);
    ASSERT_EQ(*p2, 3);
}

TEST(InitTests, CopyConstructorWorks) {
    auto p = nstd::make_uptr<int>(3);
    nstd::uptr<int> p2(std::move(p));
    ASSERT_EQ(p, nullptr);
    ASSERT_EQ(p.get(), nullptr);
    ASSERT_EQ(*p2, 3);
}

TEST(InitTests, MakeUptrIntWorks) {
    auto p = nstd::make_uptr<int>(3);
    ASSERT_EQ(*p, 3);
}

TEST(InitTests, MakeUptrIntArrayWorks) {
    auto p = nstd::make_uptr<int[]>(3);
    p[0] = 3;
    p[1] = 4;
    p[2] = 5;
    ASSERT_EQ(*p, 3);
    ASSERT_EQ(p[0], 3);
    ASSERT_EQ(p[1], 4);
    ASSERT_EQ(p[2], 5);
}

struct TestObj {
    int data{7};
    TestObj() = default;
    TestObj(int val): data(val) {}
    int test() { return data; }
};

TEST(InitTests, MakeUptrTArrayWorks) {
    auto p = nstd::make_uptr<TestObj[]>(3);
    ASSERT_EQ(p[0].test(), 7);
    ASSERT_EQ(p[1].test(), 7);
    ASSERT_EQ(p[2].test(), 7);
}

TEST(InitTests, MemberAccessWorks) {
    auto p = nstd::make_uptr<TestObj>(5);
    ASSERT_EQ(p->test(), 5);
}

