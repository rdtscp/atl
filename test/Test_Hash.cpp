#include <memory>
#include <string>

#include "gtest/gtest.h"

#include "../include/hash.h"

TEST(HashTest, Usage) {
  const int maxVal = 100;
  int curr;
  int last = -1;
  for (int i = 0; i < 100; ++i) {
    std::string std_str("test string" + std::to_string(i));
    atl::string atl_str(std_str.c_str());
    curr = atl::hash(atl_str, maxVal);
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