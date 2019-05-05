#include "gtest/gtest.h"

#include "../include/unordered_map.h"

TEST(UnorderedMapTest, DefaultConstructor) {
  atl::unordered_map<int, bool> atlMap;

  atlMap[5] = true;

  ASSERT_EQ(atlMap.find(5).second, true);
}

TEST(UnorderedMapTest, CopyConstructor) {
  atl::unordered_map<int, bool> atlMap;

  atlMap[5] = true;

  atl::unordered_map<int, bool> atlMap2(atlMap);
  ASSERT_EQ(atlMap2.find(5).second, true);
}

TEST(UnorderedMapTest, InsertDuplicateElement) {
  atl::unordered_map<int, bool> atlMap;

  atlMap.insert(5, true);
  atlMap.insert(5, false);

  // atlMap[5] = true;
  // atlMap[5] = false;

  ASSERT_EQ(atlMap.find(5).second, false);
}

TEST(UnorderedMapTest, EqualComparitor) {
  {
    atl::unordered_map<int, bool> atlMap1;
    atlMap1[0] = true;

    atl::unordered_map<int, bool> atlMap2;
    atlMap2[0] = false;

    ASSERT_NE(atlMap1, atlMap2);
  }
  {
    atl::unordered_map<int, bool> atlMap1;
    atlMap1[0] = true;

    atl::unordered_map<int, bool> atlMap2;
    atlMap2[1] = true;

    ASSERT_NE(atlMap1, atlMap2);
  }
  {
    atl::unordered_map<int, bool> atlMap1;
    atlMap1[0] = true;

    atl::unordered_map<int, bool> atlMap2;
    atlMap2[0] = true;

    ASSERT_EQ(atlMap1, atlMap2);
  }
}

// The fixture for testing class Project1. From google test primer.
class Test_UnorderedMap : public ::testing::Test {
protected:
  Test_UnorderedMap() {
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