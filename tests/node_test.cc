#include <iostream>
#include "gtest/gtest.h"
#include "node.h"

TEST(InitTests, DefaultConstructorWorks) {
    nstd::list_node<int> node;
    ASSERT_EQ(node.data(), 0);
    ASSERT_EQ(node.next(), nullptr);
    ASSERT_EQ(node.prev(), nullptr);
}

TEST(InitTests, SingleArgConstructorWorks) {
    nstd::list_node<int> node(3);
    ASSERT_EQ(node.data(), 3);
    ASSERT_EQ(node.next(), nullptr);
    ASSERT_EQ(node.prev(), nullptr);
}

TEST(InitTests, SingleArgConstructorWorks2) {
    auto node = std::make_shared<nstd::list_node<int>>(7);
    ASSERT_EQ(node->data(), 7);
    ASSERT_EQ(node->next(), nullptr);
    ASSERT_EQ(node->prev(), nullptr);
}

TEST(InitTests, MultiArgConstructorWorks) {
    auto a = std::make_shared<nstd::list_node<int>>(1);
    auto c = std::make_shared<nstd::list_node<int>>(3);
    auto b = std::make_shared<nstd::list_node<int>>(2, c.get(), a.get());
    ASSERT_EQ(b->next(), c.get());
    ASSERT_EQ(b->prev(), a.get());
    ASSERT_EQ(c->prev(), b.get());
    ASSERT_EQ(a->next(), b.get());
}
