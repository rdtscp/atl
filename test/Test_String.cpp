#include <string.h>
#include <string>

#include "gtest/gtest.h"

#include "../include/string.h"

TEST(StringTest, DefaultConstruction) {
  atl::string atlString;
  std::string stdString;
  ASSERT_EQ(atlString.size(), stdString.size());
}

TEST(StringTest, CharConstruction) {
  atl::string atlString(1, 'h');
  std::string stdString(1, 'h');
  ASSERT_EQ(atlString.size(), stdString.size());
}

TEST(StringTest, StringLiteralConstruction) {
  atl::string atlString("Hello World");
  std::string stdString("Hello World");
  ASSERT_EQ(atlString.size(), stdString.size());
}

TEST(StringTest, CSTREqual) {
  atl::string atlString("Hello World");
  std::string stdString("Hello World");
  ASSERT_EQ(0, strcmp(atlString.c_str(), stdString.c_str()));
}

TEST(StringTest, CopyConstructor) {
  atl::string atlString("Hello World");
  atl::string atlString2(atlString);
  std::string stdString("Hello World");
  std::string stdString2(stdString);

  ASSERT_EQ(0, strcmp(atlString.c_str(), atlString2.c_str()));
  ASSERT_EQ(0, strcmp(stdString.c_str(), stdString2.c_str()));
}

TEST(StringTest, SelfAssign) {
  atl::string atlString("Hello World");
  atl::string atlString2(atlString);
  std::string stdString("Hello World");
  std::string stdString2(stdString);
  ASSERT_EQ(0, strcmp(atlString.c_str(), atlString2.c_str()));
  ASSERT_EQ(0, strcmp(stdString.c_str(), stdString2.c_str()));
}

TEST(StringTest, Concat) {
  atl::string atlString1("hello ");
  std::string stdString1("hello ");
  atl::string atlString2("world");
  std::string stdString2("world");

  atl::string atlConcat = atlString1 + atlString2;
  std::string stdConcat = stdString1 + stdString2;

  ASSERT_EQ(0, strcmp(atlConcat.c_str(), stdConcat.c_str()));

  atlConcat = atlConcat + '!';
  stdConcat = stdConcat + '!';

  ASSERT_EQ(0, strcmp(atlConcat.c_str(), stdConcat.c_str()));
}

TEST(StringTest, EqualsOperator) {
  atl::string atlString1("foo");
  atl::string atlString2("foo");
  atl::string atlString3("bars");
  atl::string atlString4("bars");
  ASSERT_TRUE(atlString1 == atlString2);
  ASSERT_FALSE(atlString2 == atlString3);
  ASSERT_TRUE(atlString3 == atlString4);
  ASSERT_TRUE(atlString1 == "foo");
  ASSERT_FALSE(atlString1 == "bar");
  ASSERT_FALSE(atlString1 == "foo ");
}

TEST(StringTest, NotEqualsOperator) {
  const atl::string atlString1("foo");
  atl::string atlString2("foo");

  const atl::string atlString3("bars");
  atl::string atlString4("bars");
  ASSERT_FALSE(atlString1 != atlString2);
  ASSERT_TRUE(atlString2 != atlString3);
  ASSERT_FALSE(atlString3 != atlString4);
  ASSERT_FALSE(atlString1 != "foo");
  ASSERT_TRUE(atlString1 != "bar");
  ASSERT_TRUE(atlString1 != "foo ");
}

TEST(StringTest, PlusEqualsOperator) {
  atl::string atlString1("hello");
  atlString1 += " world";
  ASSERT_TRUE(atlString1 == "hello world");

  atl::string atlString2("hello");
  atlString2 += atl::string(" world");
  ASSERT_TRUE(atlString2 == "hello world");

  atlString2 += '!';
  ASSERT_TRUE(atlString2 == "hello world!");
}

TEST(StringTest, Find) {
  const atl::string atlString1("hello");

  const int lIndex = atlString1.find('l');
  ASSERT_EQ(lIndex, 2);

  const int xIndex = atlString1.find('x');
  ASSERT_EQ(xIndex, atl::string::npos);
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