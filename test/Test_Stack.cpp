#include <vector>

#include "gtest/gtest.h"

#include "../include/stack.h"

TEST(StackTest, DefaultConstruction) {
  atl::stack<int> atlStack;
  ASSERT_EQ(atlStack.size(), 0);
}

TEST(StackTest, TopElement) {
  atl::stack<int> atlStack;
  atlStack.push_back(1);
  atlStack.push_back(2);
  atlStack.push_back(3);
  ASSERT_EQ(atlStack.size(), 3);
  ASSERT_EQ(atlStack.top(), 3);
  ASSERT_NE(atlStack.top(), 2);
}

// The fixture for testing class Project1. From google test primer.
class Test_Stack : public ::testing::Test {
protected:
  Test_Stack() {
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