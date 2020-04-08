#include "gtest/gtest.h"

#include "../include/list.h"

TEST(VectorTest, DefaultConstruction) {
  atl::list<int> atlList;
  ASSERT_EQ(atlList.size(), 0);
}

TEST(VectorTest, PushBack) {
  atl::list<int> atlList;
  ASSERT_EQ(atlList.has_head(), false);
  ASSERT_EQ(atlList.has_tail(), false);
  atlList.push_back(5);
  ASSERT_EQ(atlList.has_head(), true);
  ASSERT_EQ(atlList.has_tail(), false);
  ASSERT_EQ(atlList.size(), 1);
  ASSERT_EQ(atlList.head(), 5);
  atlList.push_back(6);
  ASSERT_EQ(atlList.has_head(), true);
  ASSERT_EQ(atlList.has_tail(), true);
  atlList.push_back(7);
  atlList.push_back(8);
  atlList.push_back(9);
  ASSERT_EQ(atlList.size(), 5);
  ASSERT_EQ(atlList.head(), 5);
  atlList = atlList.tail();
  ASSERT_EQ(atlList.has_head(), true);
  ASSERT_EQ(atlList.has_tail(), true);
  ASSERT_EQ(atlList.size(), 4);
  ASSERT_EQ(atlList.head(), 6);
}

TEST(VectorTest, PushFront) {
  atl::list<int> atlList;
  atlList.push_front(5);
  ASSERT_EQ(atlList.size(), 1);
  ASSERT_EQ(atlList.head(), 5);
  atlList.push_front(6);
  atlList.push_front(7);
  atlList.push_front(8);
  atlList.push_front(9);
  ASSERT_EQ(atlList.size(), 5);
  ASSERT_EQ(atlList.head(), 9);
  atlList = atlList.tail();
  ASSERT_EQ(atlList.size(), 4);
  ASSERT_EQ(atlList.head(), 8);
}


// The fixture for testing class Project1. From google test primer.
class Test_List : public ::testing::Test {
protected:
  Test_List() {
    // You can do set-up work for each test here.
  }

  // If the constructor and destructor are not enough for setting up
  // and cleaning up each test, you can define the following methods:
  virtual void SetUp() {
    // Code here will be called immediately after the constructor (right
    // before each test).
  }

  virtual void TearDown() {
    // Code here will be called immediately after each test (right
    // before the destructor).
  }
};