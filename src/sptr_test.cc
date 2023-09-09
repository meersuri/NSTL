#include <iostream>

#include "gtest/gtest.h"
#include "sptr.h"

TEST(InitTests, MakeSharedIntWorks) {
    nstd::sptr<int> p = nstd::make_sptr<int>(5);
    ASSERT_EQ(*p, 5);
    *p = 7;
    ASSERT_EQ(*p, 7);
    ASSERT_EQ(p.ref_count(), 1);
}

TEST(InitTests, CopyConstructorWorks) {
    nstd::sptr<int> p = nstd::make_sptr<int>(5);
    nstd::sptr<int> p2(p);
    ASSERT_EQ(*p, 5);
    *p = 7;
    ASSERT_EQ(*p, 7);
    ASSERT_EQ(*p2, *p);
    ASSERT_EQ(p.ref_count(), 2);
    ASSERT_EQ(p2.ref_count(), 2);
}

TEST(InitTests, CopyAssignmentWorks) {
    auto p = nstd::make_sptr<int>(5);
    auto p2 = nstd::make_sptr<int>(1);
    auto p3 = p2;
    ASSERT_EQ(*p3, *p2);
    *p2 = 4;
    ASSERT_EQ(*p3, *p2);
    ASSERT_EQ(p.ref_count(), 1);
    ASSERT_EQ(p2.ref_count(), 2);
    ASSERT_EQ(p3.ref_count(), 2);
}

