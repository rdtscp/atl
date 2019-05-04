#include "gtest/gtest.h"

#include "../include/ifstream.h"
#include "../include/ofstream.h"
#include "../include/string.h"

// atl::string test_prefix =
// "/Users/alexanderwilson/Documents/GitHub/atl/test/tests/";
atl::string test_prefix = "../../test/tests/";

TEST(OfStreamTest, WriteFile) {
  {
    // Reset the file.
    atl::ofstream fileStream(test_prefix + "testfile2.txt");
    fileStream.write("");
    // Assert the file is empty.
    atl::ifstream emptyStream(test_prefix + "testfile2.txt");
    ASSERT_EQ(emptyStream.readIntoString(), "");
  }
  {
    // Write to the file.
    atl::ofstream fileStream(test_prefix + "testfile2.txt");
    fileStream.write("this is testfile2.txt\n");
  }
  {
    // Assert the file is correct.
    atl::ifstream emptyStream(test_prefix + "testfile2.txt");
    ASSERT_EQ(emptyStream.readIntoString(), "this is testfile2.txt\n");
    // Reset the file.
    atl::ofstream fileStream(test_prefix + "testfile2.txt");
    fileStream.write("");
  }
}

// The fixture for testing class Project1. From google test primer.
class Test_OfStream : public ::testing::Test {
protected:
  Test_OfStream() {
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