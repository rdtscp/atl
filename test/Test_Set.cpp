#include "gtest/gtest.h"

#include "../include/set.h"
#include "../include/string.h"

TEST(SetTest, Constructor) {
  atl::set<atl::string> atlSet;
  atl::string elem1("foo");
  atl::string elem2("bar");
  ASSERT_FALSE(atlSet.find(elem1));
  ASSERT_FALSE(atlSet.find(elem2));
  atlSet.insert(elem1);
  ASSERT_TRUE(atlSet.find(elem1));
  ASSERT_FALSE(atlSet.find(elem2));
  atlSet.insert(elem2);
  ASSERT_TRUE(atlSet.find(elem1));
  ASSERT_TRUE(atlSet.find(elem2));
}

TEST(SetTest, Usage) {
  atl::set<atl::string> atlSet;
  atl::string elem1("foo");
  atl::string elem2("bar");
  ASSERT_FALSE(atlSet.find(elem1));
  ASSERT_FALSE(atlSet.find(elem2));
  atlSet.insert(elem1);
  ASSERT_TRUE(atlSet.find(elem1));
  ASSERT_FALSE(atlSet.find(elem2));
  atlSet.insert(elem2);
  ASSERT_TRUE(atlSet.find(elem1));
  ASSERT_TRUE(atlSet.find(elem2));
}

TEST(SetTest, CopyConstructor) {
  atl::set<atl::string> atlSet;
  atl::string elem1("foo");
  atl::string elem2("bar");
  ASSERT_FALSE(atlSet.find(elem1));
  ASSERT_FALSE(atlSet.find(elem2));
  atlSet.insert(elem1);
  ASSERT_TRUE(atlSet.find(elem1));
  ASSERT_FALSE(atlSet.find(elem2));
  atlSet.insert(elem2);
  ASSERT_TRUE(atlSet.find(elem1));
  ASSERT_TRUE(atlSet.find(elem2));

  atl::set<atl::string> atlSet2(atlSet);
  ASSERT_TRUE(atlSet2.find(elem1));
  ASSERT_TRUE(atlSet2.find(elem2));
}

TEST(SetTest, EqualOperator) {
  atl::set<atl::string> atlSet;
  atlSet.insert("elem1");
  atlSet.insert("elem2");
  atlSet.insert("elem3");
  atl::set<atl::string> atlSet2 = atlSet;
  ASSERT_EQ(atlSet, atlSet2);
  atlSet2.insert("elem4");
  ASSERT_NE(atlSet, atlSet2);
}

// The fixture for testing class Project1. From google test primer.
class Test_Set : public ::testing::Test {
protected:
  Test_Set() {
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