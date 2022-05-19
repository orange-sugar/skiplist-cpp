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
}

TEST(skiplist_test, remove)
{
  SkipList<int, std::string> list(INT_MAX);
  list.insert(-1, "hello");
  list.insert(0, "world");
  list.insert(1, "!");
  std::string value;
  list.remove(1, &value);
  EXPECT_EQ(list.size(), 2);
  EXPECT_EQ(value, "!");
}

TEST(skiplist_test, loadfile)
{
  SkipList<int, std::string> list(INT_MAX);
  list.loadFromFile("../tests/kv1.txt");
  EXPECT_EQ(list.size(), 3);
  EXPECT_EQ(list.find(-1)->getKey(), -1);
  EXPECT_EQ(list.find(-1)->getValue(), "hello");
  list.print();
}

TEST(skiplist_test, dumpfile)
{
  SkipList<int, std::string> list(INT_MAX);
  list.insert(-1, "hello");
  list.insert(0, "world");
  list.insert(1, "!");
  EXPECT_EQ(list.size(), 3);
  list.print();
  list.dumpToFile("kv.txt");
}