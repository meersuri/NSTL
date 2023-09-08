#include <iostream>

#include "gtest/gtest.h"
#include "sptr.h"

TEST(InitTests, MakeSharedIntWorks) {
    nstd::sptr<int> p = nstd::make_sptr<int>(5);
    ASSERT_EQ(*p, 5);
    *p = 7;
    ASSERT_EQ(*p, 7);
}

