#include "gtest/gtest.h"

#include "../include/ifstream.h"
#include "../include/string.h"

// atl::string test_prefix =
// "/Users/alexanderwilson/Documents/GitHub/atl/test/tests/";
atl::string test_prefix = "../../test/tests/";

TEST(IfStreamTest, NoFileConstruction) {
  atl::ifstream fileStream("");
  ASSERT_FALSE(fileStream.good());
}

TEST(IfStreamTest, FileConstruction) {
  atl::ifstream fileStream(test_prefix + "testfile1.txt");
  ASSERT_TRUE(fileStream.good());
  const atl::string expectation("this is testfile1.txt\n");
  ASSERT_EQ(expectation, fileStream.readIntoString());
}

// The fixture for testing class Project1. From google test primer.
class Test_IfStream : public ::testing::Test {
protected:
  Test_IfStream() {
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