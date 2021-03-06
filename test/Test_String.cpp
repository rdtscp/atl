#include "gtest/gtest.h"

#include "../include/string.h"
#include <string>

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
  ASSERT_FALSE(atlString1 == "fooo");
  ASSERT_FALSE(atlString1 == "fooo");
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

  atl::string atlString3("my string\n");
  atlString3 += '\0';
  atlString3 += "\n";
  ASSERT_TRUE(atlString3 == "my string\n\n");
}

TEST(StringTest, Find) {
  const atl::string atlString1("hello");

  const int lIndex = atlString1.find('l');
  ASSERT_EQ(lIndex, 2);

  const int xIndex = atlString1.find('x');
  ASSERT_EQ(xIndex, -1);
}

TEST(StringTest, ToString) {
  ASSERT_TRUE(atl::to_string(0) == "0");
  ASSERT_TRUE(atl::to_string(1) == "1");
  ASSERT_TRUE(atl::to_string(100000) == "100000");
  ASSERT_TRUE(atl::to_string(123456) == "123456");
  ASSERT_TRUE(atl::to_string(-100000) == "-100000");
  ASSERT_TRUE(atl::to_string(-123456) == "-123456");
}

TEST(StringTest, Comparitors) {
  ASSERT_TRUE(atl::string("1234") < atl::string("12345"));
  ASSERT_TRUE(atl::string("1234") <= atl::string("12345"));
  ASSERT_FALSE(atl::string("12345") < atl::string("1234"));
  ASSERT_FALSE(atl::string("12345") <= atl::string("1234"));
  ASSERT_FALSE(atl::string("12345") < atl::string("12345"));
  ASSERT_TRUE(atl::string("12345") <= atl::string("12345"));

  ASSERT_TRUE(atl::string("12345") > atl::string("1234"));
  ASSERT_TRUE(atl::string("12345") >= atl::string("1234"));
  ASSERT_FALSE(atl::string("1234") > atl::string("12345"));
  ASSERT_FALSE(atl::string("1234") >= atl::string("12345"));
  ASSERT_FALSE(atl::string("12345") > atl::string("12345"));
  ASSERT_TRUE(atl::string("12345") >= atl::string("12345"));

  ASSERT_TRUE(atl::string("one") == atl::string("one"));
  ASSERT_TRUE(atl::string("one") <= atl::string("one"));
  ASSERT_TRUE(atl::string("one") >= atl::string("one"));
  ASSERT_FALSE(atl::string("one") > atl::string("one"));
  ASSERT_FALSE(atl::string("one") < atl::string("one"));
  ASSERT_FALSE(atl::string("one") != atl::string("one"));

  atl::string one1("one");
  atl::string one2("one");

  ASSERT_TRUE(!(one1 < one2) && !(one2 < one1));
}

TEST(StringTest, BeginEnd) {
  atl::string atlString("test");
  atl::string::const_iterator it_begin = atlString.begin();
  atl::string::const_iterator it_end = atlString.end();
  ASSERT_TRUE(*it_end == '\0');
  ASSERT_TRUE(*it_begin == 't');
  ++it_begin;
  ASSERT_TRUE(*it_begin == 'e');
  ++it_begin;
  ASSERT_TRUE(*it_begin == 's');
  ++it_begin;
  ASSERT_TRUE(*it_begin == 't');
  ++it_begin;
  ASSERT_TRUE(*it_begin == '\0');
  ASSERT_EQ(it_begin, it_end);
}

TEST(StringTest, IsSpace) {
  ASSERT_TRUE(atl::isspace(' '));
  ASSERT_TRUE(atl::isspace('\n'));
  ASSERT_TRUE(atl::isspace('\r'));
  ASSERT_TRUE(atl::isspace('\t'));
  ASSERT_FALSE(atl::isspace('!'));
  ASSERT_FALSE(atl::isspace('a'));
  ASSERT_FALSE(atl::isspace('A'));
  ASSERT_FALSE(atl::isspace('1'));
  ASSERT_FALSE(atl::isspace('9'));
  ASSERT_FALSE(atl::isspace('0'));
  ASSERT_FALSE(atl::isspace('\\'));
  ASSERT_FALSE(atl::isspace('_'));
  ASSERT_FALSE(atl::isspace('Z'));
  ASSERT_FALSE(atl::isspace('z'));
}

TEST(StringTest, IsDigit) {
  ASSERT_FALSE(atl::isdigit(' '));
  ASSERT_FALSE(atl::isdigit('\n'));
  ASSERT_FALSE(atl::isdigit('\r'));
  ASSERT_FALSE(atl::isdigit('\t'));
  ASSERT_FALSE(atl::isdigit('!'));
  ASSERT_FALSE(atl::isdigit('a'));
  ASSERT_FALSE(atl::isdigit('A'));
  ASSERT_TRUE(atl::isdigit('1'));
  ASSERT_TRUE(atl::isdigit('9'));
  ASSERT_TRUE(atl::isdigit('0'));
  ASSERT_FALSE(atl::isdigit('\\'));
  ASSERT_FALSE(atl::isdigit('_'));
  ASSERT_FALSE(atl::isdigit('Z'));
  ASSERT_FALSE(atl::isdigit('z'));
}

TEST(StringTest, IsAlpha) {
  ASSERT_FALSE(atl::isalpha(' '));
  ASSERT_FALSE(atl::isalpha('\n'));
  ASSERT_FALSE(atl::isalpha('\r'));
  ASSERT_FALSE(atl::isalpha('\t'));
  ASSERT_FALSE(atl::isalpha('!'));
  ASSERT_TRUE(atl::isalpha('a'));
  ASSERT_TRUE(atl::isalpha('A'));
  ASSERT_FALSE(atl::isalpha('1'));
  ASSERT_FALSE(atl::isalpha('9'));
  ASSERT_FALSE(atl::isalpha('0'));
  ASSERT_FALSE(atl::isalpha('\\'));
  ASSERT_FALSE(atl::isalpha('_'));
  ASSERT_TRUE(atl::isalpha('Z'));
  ASSERT_TRUE(atl::isalpha('z'));
}

TEST(StringTest, CharConcat) {
  const atl::string rhs = "World!";
  const atl::string expected = "Hello World!";
  ASSERT_EQ(expected, "Hello " + rhs);
}

TEST(StringTest, Stoi) {
  const atl::string positiveint = "193812394";
  ASSERT_EQ(atl::stoi(positiveint), 193812394);

  const atl::string negativeint = "-193812394";
  ASSERT_EQ(atl::stoi(negativeint), -193812394);
}

TEST(StringTest, Size) {
  atl::string foo(atl::string("abc"));
  ASSERT_EQ(foo.size(), 3u);
  foo += "def";
  ASSERT_EQ(foo.size(), 6u);
  foo += 'g';
  ASSERT_EQ(foo.size(), 7u);
  foo += atl::string("hij");
  ASSERT_EQ(foo.size(), 10u);
  ASSERT_EQ((foo + "klm").size(), 13u);
  ASSERT_EQ(foo[0], 'a');
  ASSERT_EQ(foo[9], 'j');
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