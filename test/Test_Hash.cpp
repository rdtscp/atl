#include "gtest/gtest.h"

#include "../include/hash.h"
#include "../include/string.h"

TEST(HashTest, Usage) {
  const int maxVal = 100;
  int last = -1;
  for (int curr, i = 0; i < 100; ++i) {
    atl::string str = atl::string("test string") + atl::to_string(i);
    curr = atl::hash(str, maxVal);
    ASSERT_TRUE(curr >= 0);
    ASSERT_TRUE(curr < maxVal);
    ASSERT_TRUE(curr != last);
    last = curr;
  }
}

// The fixture for testing class Project1. From google test primer.
class Test_Hash : public ::testing::Test {
protected:
  Test_Hash() {
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