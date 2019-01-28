#include <vector>

#include "gtest/gtest.h"

#include "../include/vector.h"

TEST(VectorTest, DefaultConstruction) {
  atl::vector<int> atlVect;
  std::vector<int> stdVect;
  ASSERT_EQ(atlVect.size(), stdVect.size());
}

TEST(VectorTest, SizeConstruction) {
  atl::vector<int> atlVect(5);
  std::vector<int> stdVect(5);
  ASSERT_EQ(atlVect.size(), stdVect.size());
  ASSERT_TRUE(atlVect.capacity() >= 5);
  ASSERT_TRUE(stdVect.capacity() >= 5);
}

TEST(VectorTest, Reserve) {
  atl::vector<int> atlVect;
  std::vector<int> stdVect;
  ASSERT_EQ(atlVect.size(), stdVect.size());
  atlVect.reserve(10);
  stdVect.reserve(10);
  ASSERT_EQ(atlVect.size(), stdVect.size());
  ASSERT_TRUE(atlVect.capacity() >= 10);
  ASSERT_TRUE(stdVect.capacity() >= 10);
}

TEST(VectorTest, PushBack) {
  atl::vector<int> atlVect;
  std::vector<int> stdVect;
  atlVect.push_back(5);
  stdVect.push_back(5);
  ASSERT_TRUE(atlVect.capacity() >= 1);
  ASSERT_TRUE(stdVect.capacity() >= 1);
  atlVect.push_back(6);
  stdVect.push_back(6);
  ASSERT_TRUE(atlVect.capacity() >= 2);
  ASSERT_TRUE(stdVect.capacity() >= 2);
  stdVect.push_back(7);
  atlVect.push_back(7);
  ASSERT_TRUE(atlVect.capacity() >= 3);
  ASSERT_TRUE(stdVect.capacity() >= 3);
  ASSERT_EQ(atlVect.size(), stdVect.size());
  ASSERT_EQ(atlVect[0], stdVect[0]);
  ASSERT_EQ(atlVect.at(0), stdVect.at(0));
  ASSERT_EQ(atlVect[1], stdVect[1]);
  ASSERT_EQ(atlVect.at(1), stdVect.at(1));
  ASSERT_TRUE(atlVect.capacity() >= 3);
  ASSERT_TRUE(stdVect.capacity() >= 3);
}

TEST(VectorTest, ElementsAddress) {
  const int seven = 7;
  std::vector<int> stdVect;
  stdVect.push_back(seven);
  ASSERT_NE(&stdVect[0], &seven);
}

TEST(VectorTest, PointerAddress) {
  int seven = 7;
  int *seven_p = &seven;
  atl::vector<int *> atlVect;
  std::vector<int *> stdVect;
  atlVect.push_back(seven_p);
  stdVect.push_back(seven_p);
  ASSERT_EQ(atlVect[0], stdVect[0]);
}

TEST(VectorTest, CopyConstructor) {
  atl::vector<int> atlVect;
  std::vector<int> stdVect;
  atlVect.push_back(5);
  stdVect.push_back(5);
  atlVect.push_back(6);
  stdVect.push_back(6);
  atlVect.push_back(7);
  stdVect.push_back(7);

  atl::vector<int> atlVect2;
  std::vector<int> stdVect2;
  atlVect2 = atlVect;
  stdVect2 = stdVect;

  ASSERT_EQ(atlVect.size(), atlVect2.size());
  ASSERT_EQ(stdVect.size(), stdVect2.size());

  ASSERT_EQ(atlVect[0], 5);
  ASSERT_EQ(atlVect2[0], 5);

  ASSERT_EQ(atlVect[0], atlVect2[0]);
  ASSERT_EQ(atlVect[1], atlVect2[1]);

  ASSERT_EQ(stdVect[0], stdVect2[0]);
  ASSERT_EQ(stdVect[1], stdVect2[1]);
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