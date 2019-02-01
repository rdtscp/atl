#include "gtest/gtest.h"

#include "../include/pair.h"
#include <string>
#include <utility>

TEST(PairTest, DefaultConstructor) {
  std::pair<int, std::string> stdPair;
  atl::pair<int, std::string> atlPair;
  ASSERT_EQ(stdPair.first, atlPair.first);
  ASSERT_EQ(stdPair.second, atlPair.second);
}

TEST(PairTest, ValueConstructor) {
  std::pair<int, std::string> stdPair(5, "foo");
  atl::pair<int, std::string> atlPair(5, "foo");
  ASSERT_EQ(stdPair.first, atlPair.first);
  ASSERT_EQ(stdPair.second, atlPair.second);
}

TEST(PairTest, ValueAssign) {
  std::pair<int, std::string> stdPair(5, "foo");
  atl::pair<int, std::string> atlPair(5, "foo");
  stdPair.first = 6;
  stdPair.second = "bar";
  atlPair.first = 6;
  atlPair.second = "bar";
  ASSERT_EQ(stdPair.first, atlPair.first);
  ASSERT_EQ(stdPair.second, atlPair.second);
}

// The fixture for testing class Project1. From google test primer.
class Test_Pair : public ::testing::Test {
protected:
  Test_Pair() {
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