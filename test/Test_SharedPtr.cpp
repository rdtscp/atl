#include "gtest/gtest.h"

#include "../include/enable_shared_from_this.h"
#include "../include/shared_ptr.h"

#include <memory>

TEST(SharedPtrTest, Construction) {
  atl::shared_ptr<int> atl_sp1;
  std::shared_ptr<int> std_sp1;

  atl_sp1 = nullptr;
  std_sp1 = nullptr;

  atl::shared_ptr<int> atl_sp2(nullptr);
  std::shared_ptr<int> std_sp2(nullptr);

  ASSERT_EQ(atl_sp2, atl_sp1);
  ASSERT_EQ(std_sp2, std_sp1);

  atl::shared_ptr<int> atl_sp3(new int(5));
  std::shared_ptr<int> std_sp3(new int(5));

  ASSERT_NE(atl_sp2, atl_sp3);
  ASSERT_NE(std_sp2, std_sp3);

  atl::shared_ptr<int> atl_sp4(new int(6));
  std::shared_ptr<int> std_sp4(new int(6));

  ASSERT_NE(*atl_sp4, *atl_sp3);
  ASSERT_NE(*std_sp4, *std_sp3);

  *atl_sp3 = 6;
  *std_sp3 = 6;
  
  ASSERT_EQ(*atl_sp4, *atl_sp3);
  ASSERT_EQ(*std_sp4, *std_sp3);
}

TEST(SharedPtrTest, CopyConstruction) {
  atl::shared_ptr<int> atl_sp1(new int(5));
  std::shared_ptr<int> std_sp1(new int(5));

  atl::shared_ptr<int> atl_sp2(atl_sp1);
  std::shared_ptr<int> std_sp2(std_sp1);

  atl::shared_ptr<int> atl_sp3 = atl_sp2;
  std::shared_ptr<int> std_sp3 = std_sp2;

  ASSERT_EQ(*atl_sp3, 5);
  ASSERT_EQ(*std_sp3, 5);

  ASSERT_EQ(atl_sp3.get(), atl_sp1.get());
  ASSERT_EQ(std_sp3.get(), std_sp1.get());
}

TEST(SharedPtrTest, Class) {
  struct Test {
    int m_val;
    Test(int val) : m_val(val + 1) {}
  };

  atl::shared_ptr<Test> atl_sp1(new Test(5));
  std::shared_ptr<Test> std_sp1(new Test(5));

  atl::shared_ptr<Test> atl_sp2(new Test(5));
  std::shared_ptr<Test> std_sp2(new Test(5));

  ASSERT_EQ(atl_sp1->m_val, atl_sp2->m_val);
  ASSERT_EQ(std_sp1->m_val, std_sp2->m_val);

  ASSERT_NE(atl_sp1, nullptr);
  ASSERT_NE(std_sp1, nullptr);

  atl_sp1 = nullptr;
  std_sp1 = nullptr;

  ASSERT_EQ(atl_sp1, nullptr);
  ASSERT_EQ(std_sp1, nullptr);
}

TEST(SharedPtrTest, ClassInheritance) {
  struct Base {
    int b_val;
    Base(int val) : b_val(val + 1) {}
  };
  struct Test : public Base {
    int t_val;
    Test(int val) : Base(val), t_val(val + 2) {}
  };

  atl::shared_ptr<Test> atl_sp1(new Test(5));
  std::shared_ptr<Test> std_sp1(new Test(5));

  atl::shared_ptr<Test> atl_sp2(new Test(5));
  std::shared_ptr<Test> std_sp2(new Test(5));

  ASSERT_EQ(atl_sp1->t_val, atl_sp2->t_val);
  ASSERT_EQ(atl_sp1->b_val, atl_sp2->b_val);
  ASSERT_EQ(std_sp1->t_val, std_sp2->t_val);
  ASSERT_EQ(std_sp1->b_val, std_sp2->b_val);

  ASSERT_NE(atl_sp1, nullptr);
  ASSERT_NE(std_sp1, nullptr);

  atl_sp1 = nullptr;
  std_sp1 = nullptr;

  ASSERT_EQ(atl_sp1, nullptr);
  ASSERT_EQ(std_sp1, nullptr);

  atl_sp1 = atl::shared_ptr<Test>(new Test(5));
  std_sp1 = std::shared_ptr<Test>(new Test(5));
  
  atl::shared_ptr<Base> atl_sp3 = atl::static_pointer_cast<Base>(atl_sp1);
  std::shared_ptr<Base> std_sp3 = std::static_pointer_cast<Base>(std_sp1);

  ASSERT_EQ(atl_sp3.get(), atl_sp1.get());
  ASSERT_EQ(std_sp3.get(), std_sp1.get());

  ASSERT_EQ(atl_sp3->b_val, atl_sp1->b_val);
  ASSERT_EQ(std_sp3->b_val, std_sp1->b_val);
}

TEST(SharedPtrTest, ClassInheritance2) {
  struct Base {
    int b_val;
    Base(int val) : b_val(val + 1) {}
  };
  struct Test : public Base {
    int t_val;
    Test(int val) : Base(val), t_val(val + 2) {}
  };

  atl::shared_ptr<Test> atl_sp1(new Test(5));
  atl::shared_ptr<Base> atl_sp2(atl_sp1);
  ASSERT_EQ(atl_sp1.get(), atl_sp2.get());
  atl::shared_ptr<Base> atl_sp3 = atl_sp2;
  ASSERT_EQ(atl_sp1.get(), atl_sp3.get());

  ASSERT_EQ(atl_sp1, atl_sp3);

  atl::shared_ptr<Test> atl_sp4(new Test(5));
  ASSERT_NE(atl_sp1, atl_sp4);
}

TEST(SharedPtrTest, SharedFromThis) {
  class Test1 : public atl::enable_shared_from_this<Test1> {
  public:
    int t_val;
    Test1(const int val) : t_val(val + 1) {}
  };

  atl::shared_ptr<Test1> atl_sp(new Test1(5));
  atl::shared_ptr<Test1> atl_sp2 = atl_sp;

  ASSERT_EQ(atl_sp2->t_val, 6);

  atl::shared_ptr<Test1> atl_sp3 = atl_sp2->shared_from_this();
  Test1 &test = *atl_sp3;
  (void)test;
  atl::shared_ptr<Test1> atl_sp4 = test.shared_from_this();
  // atl::shared_ptr<Test const> atl_sp4 = atl_sp2->shared_from_this();

  ASSERT_EQ(atl_sp2->t_val, 6);

  class Test2 : public std::enable_shared_from_this<Test2> {
  public:
    int t_val;
    Test2(const int val) : t_val(val + 1) {}
  };

  std::shared_ptr<Test2> std_sp(new Test2(10));
  std::shared_ptr<Test2> std_sp2 = std_sp;

  ASSERT_EQ(std_sp2->t_val, 11);

  std::shared_ptr<Test2> std_sp3 = std_sp2->shared_from_this();
  Test2 &test2 = *std_sp3;
  std::shared_ptr<Test2> std_sp4 = test2.shared_from_this();
  // std::shared_ptr<Test2 const> std_sp4 = std_sp2->shared_from_this();

  ASSERT_EQ(std_sp2->t_val, 11);

}

TEST(SharedPtrTest, SharedFromThisInheritance) {
  class Base1 : public atl::enable_shared_from_this<Base1> {
  public:
    virtual ~Base1() {}
  };
  class Test1 : public Base1 {
  public:
    int t_val;
    Test1(const int val) : t_val(val + 1) {}
    ~Test1() {}
  };

  atl::shared_ptr<Test1> atl_sp(new Test1(5));
  atl::shared_ptr<Test1> atl_sp2 = atl_sp;

  ASSERT_EQ(atl_sp2->t_val, 6);

  atl::shared_ptr<Base1> atl_sp3 = atl_sp2->shared_from_this();
  Base1 &test = *atl_sp3;
  atl::shared_ptr<Base1> atl_sp4 = test.shared_from_this();

  ASSERT_EQ(atl_sp2->t_val, 6);

  class Base2 : public std::enable_shared_from_this<Base2> {
  public:
    virtual ~Base2() {}
  };
  class Test2 : public Base2 {
  public:
    int t_val;
    Test2(const int val) : t_val(val + 1) {}
    // ~Test2() {}
  };

  std::shared_ptr<Test2> std_sp(new Test2(10));
  std::shared_ptr<Test2> std_sp2 = std_sp;

  ASSERT_EQ(std_sp2->t_val, 11);

  std::shared_ptr<Base2> std_sp3 = std_sp2->shared_from_this();
  Base2 &test2 = *std_sp3;
  std::shared_ptr<Base2> std_sp4 = test2.shared_from_this();

  ASSERT_EQ(std_sp2->t_val, 11);
}

// The fixture for testing class Project1. From google test primer.
class Test_SharedPtr : public ::testing::Test {
protected:
  Test_SharedPtr() {
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