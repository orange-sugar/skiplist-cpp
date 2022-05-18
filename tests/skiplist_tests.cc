#include <gtest/gtest.h>

#include "SkipList.h"

TEST(skiplist_test, init)
{
  SkipList<int, std::string> list(INT_MAX);
  EXPECT_EQ(list.size(), 0);
}

TEST(skiplist_test, insert)
{
  SkipList<int, std::string> list(INT_MAX);
  list.insert(-1, "hello");
  EXPECT_EQ(list.size(), 1);
  list.insert(0, "world");
  list.insert(2, "!");
  EXPECT_EQ(list.size(), 3);
  list.print();
}