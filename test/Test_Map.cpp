#include "gtest/gtest.h"

#include "../include/map.h"

TEST(MapTest, DefaultConstructor) {
  atl::map<int, bool> atlMap;

  atlMap[5] = true;

  ASSERT_EQ(atlMap.find(5), true);
}

// The fixture for testing class Project1. From google test primer.
class Test_Map : public ::testing::Test {
protected:
  Test_Map() {
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