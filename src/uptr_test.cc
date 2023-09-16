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

struct TestObj {
    int data;
    TestObj(int val): data(val) {}
    int test() { return data; }
};

TEST(InitTests, MemberAccessWorks) {
    auto p = nstd::make_uptr<TestObj>(5);
    ASSERT_EQ(p->test(), 5);
}

