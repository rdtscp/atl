#include <vector>

#include "gtest/gtest.h"

#include "../include/vector/vector.h"

TEST(VectorTest, DefaultConstruction) {
  atl::vector<int> atlVect;
  std::vector<int> stdVect;
  ASSERT_EQ(atlVect.capacity(), stdVect.capacity());
  ASSERT_EQ(atlVect.size(), stdVect.size());
}

TEST(VectorTest, SizeConstruction) {
  atl::vector<int> atlVect(5);
  std::vector<int> stdVect(5);
  ASSERT_EQ(atlVect.capacity(), stdVect.capacity());
  ASSERT_EQ(atlVect.size(), stdVect.size());
}

TEST(VectorTest, Reserve) {
  atl::vector<int> atlVect;
  std::vector<int> stdVect;
  ASSERT_EQ(atlVect.capacity(), stdVect.capacity());
  ASSERT_EQ(atlVect.size(), stdVect.size());
  atlVect.reserve(10);
  stdVect.reserve(10);
  ASSERT_EQ(atlVect.capacity(), stdVect.capacity());
  ASSERT_EQ(atlVect.size(), stdVect.size());
}

// The fixture for testing class Project1. From google test primer.
class Test_Vector : public ::testing::Test {
protected:
  Test_Vector() {
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