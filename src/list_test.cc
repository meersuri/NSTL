#include <iostream>

#include "gtest/gtest.h"
#include "list.h"

TEST(InitTests, SizeWorks) {
    nstd::list<int> list;
    ASSERT_EQ(list.size(), 0);
}

TEST(AddElementTests, AppendToEmptyListWorks) {
    nstd::list<int> list;
    list.append(1);
    ASSERT_EQ(list.size(), 1);
}

TEST(AddElementTests, AppendWorks) {
    nstd::list<int> list;
    list.append(1);
    list.append(2);
    ASSERT_EQ(list.size(), 2);
}

TEST(AddElementTests, FrontBackWorkforSingleElement) {
    nstd::list<int> list;
    list.append(1);
    ASSERT_EQ(list.size(), 1);
    ASSERT_EQ(list.back(), 1);
    ASSERT_EQ(list.front(), 1);
}

TEST(AddElementTests, FrontBackWork) {
    nstd::list<int> list;
    list.append(1);
    list.append(2);
    ASSERT_EQ(list.size(), 2);
    ASSERT_EQ(list.back(), 2);
    ASSERT_EQ(list.front(), 1);
}

TEST(RemoveElementTests, PopWorksForSingleElement) {
    nstd::list<int> list;
    list.append(1);
    auto data = list.pop();
    ASSERT_EQ(list.size(), 0);
    ASSERT_EQ(data, 1);
}

TEST(RemoveElementTests, PopWorks) {
    nstd::list<int> list;
    list.append(1);
    list.append(2);
    auto data = list.pop();
    ASSERT_EQ(list.size(), 1);
    ASSERT_EQ(data, 2);
    data = list.pop();
    ASSERT_EQ(list.size(), 0);
    ASSERT_EQ(data, 1);
}
