#include "gtest/gtest.h"

#include "../include/shared_ptr.h"
#include <memory>

/* STL Behaviour */

TEST(SharedPtrTest, DefaultConstruction) {
  atl::shared_ptr<int> atlSP;
  std::shared_ptr<int> stdSP;
  ASSERT_EQ(atlSP.get(), stdSP.get());
}

TEST(SharedPtrTest, NullPtr) {
  class Base : public atl::enable_shared_from_this<Base> {};
  atl::shared_ptr<Base> atlNullSP(nullptr);
  atl::shared_ptr<Base> atlNullSP2;
  atlNullSP2 = atlNullSP;
}

TEST(SharedPtrTest, PtrConstruction) {
  int *myInt = new int(5);
  atl::shared_ptr<int> atlSP(myInt);
  std::shared_ptr<int> stdSP(myInt);
  ASSERT_EQ(atlSP.get(), stdSP.get());
  ASSERT_EQ(*atlSP, *stdSP);
}

TEST(SharedPtrTest, RefCount) {
  int *myInt = new int(5);
  atl::shared_ptr<int> atlSP(myInt);
  atl::shared_ptr<int> atlSP2(atlSP);

  ASSERT_EQ(atlSP.get(), atlSP2.get());
  ASSERT_EQ(*atlSP, *atlSP2);

  std::shared_ptr<int> stdSP(myInt);
  std::shared_ptr<int> stdSP2(stdSP);

  ASSERT_EQ(stdSP.use_count(), atlSP.use_count());
  ASSERT_EQ(*atlSP, *stdSP2);
}

TEST(SharedPtrTest, Equality) {
  int *myInt = new int(5);
  atl::shared_ptr<int> atlSP(myInt);
  atl::shared_ptr<int> atlSP2(atlSP);

  std::shared_ptr<int> stdSP(myInt);
  std::shared_ptr<int> stdSP2(stdSP);

  ASSERT_TRUE(atlSP == atlSP2);
  ASSERT_TRUE(stdSP == stdSP2);
  ASSERT_FALSE(atlSP != atlSP2);
  ASSERT_FALSE(stdSP != stdSP2);
}

TEST(SharedPtrTest, ClassInheritance) {
  class Base {
  public:
    int b_val;
    explicit Base(const int val) : b_val(val + 1) {}
    virtual ~Base() {}
  };
  class Derived : public Base {
  public:
    int d_val;
    explicit Derived(const int val) : Base(val), d_val(val) {}
  };

  Derived *derivedPtr = new Derived(0);
  atl::shared_ptr<Derived> atlSP(derivedPtr);
  ASSERT_TRUE(atlSP->d_val == 0);
  ASSERT_TRUE(atlSP->b_val == 1);

  atl::shared_ptr<Base> atlSP2(derivedPtr);
  ASSERT_TRUE(atlSP2->b_val == 1);

  atl::shared_ptr<Base> atlSP3 = atlSP;
  ASSERT_TRUE(atlSP3->b_val == 1);
}

/* Static Function Tests */

TEST(SharedPtrTest, MakeSharedDefault) {
  atl::shared_ptr<int> atlMSP = atl::make_shared<int>();
  ASSERT_TRUE(atlMSP.get() != nullptr);
  ASSERT_TRUE(*atlMSP == 0);
}

TEST(SharedPtrTest, MakeSharedRVAL) {
  atl::shared_ptr<int> atlMSP = atl::make_shared<int>(5);
  ASSERT_TRUE(atlMSP.get() != nullptr);
  ASSERT_TRUE(*atlMSP == 5);
}

/* Pointer Construction Tests */

TEST(SharedPtrTest, Class) {
  class Base {
  public:
    int b_val;
    explicit Base(const int val) : b_val(val + 1) {}
  };

  Base *classPtr = new Base(0);
  atl::shared_ptr<Base> atlSP(classPtr);
  ASSERT_TRUE(atlSP->b_val == 1);

  atl::shared_ptr<Base> atlSP2(classPtr);
  ASSERT_TRUE(atlSP2->b_val == 1);

  atl::shared_ptr<Base> atlSP3 = atlSP;
  ASSERT_TRUE(atlSP3->b_val == 1);
}

/* MakeShared Construction Tests */

TEST(SharedPtrTest, MakeSharedClass) {
  class Base {
  public:
    int b_val;
    explicit Base(const int val) : b_val(val + 1) {}
  };

  atl::shared_ptr<Base> atlSP = atl::make_shared<Base>(Base(0));
  ASSERT_TRUE(atlSP->b_val == 1);
}

TEST(SharedPtrTest, MakeSharedClassInheritance) {
  class Base {
  public:
    int b_val;
    explicit Base(const int val) : b_val(val + 1) {}
    virtual ~Base() {}
  };
  class Derived : public Base {
  public:
    int d_val;
    explicit Derived(const int val) : Base(val), d_val(val) {}
  };

  atl::shared_ptr<Derived> atlSP = atl::make_shared<Derived>(Derived(0));
  ASSERT_TRUE(atlSP->d_val == 0);
  ASSERT_TRUE(atlSP->b_val == 1);
}

/* SharedFromThis Tests */

TEST(SharedPtrTest, SharedFromThis) {
  class Base : public atl::enable_shared_from_this<Base> {
  public:
    int b_val;
    explicit Base(const int val) : b_val(val) {}
    atl::shared_ptr<Base> get_ptr() { return shared_from_this(); }
  };

  Base testClass(5);

  atl::shared_ptr<Base> testClassPtr1(&testClass);
  atl::shared_ptr<Base> testClassPtr2 = testClass.get_ptr();

  ASSERT_TRUE(testClassPtr1 == testClassPtr2);

  atl::shared_ptr<Base> testClassPtr3(testClassPtr1);
  atl::shared_ptr<Base> testClassPtr4(testClassPtr2);
  atl::shared_ptr<Base> testClassPtr5 = testClass.get_ptr();

  ASSERT_TRUE(testClassPtr3 == testClassPtr4);
  ASSERT_TRUE(testClassPtr4 == testClassPtr5);
}

TEST(SharedPtrTest, StaticPointerCast) {
  class Base {
  public:
    int b_val;
    explicit Base(const int val) : b_val(val + 1) {}
    virtual ~Base() {}
  };
  class Derived : public Base {
  public:
    int d_val;
    explicit Derived(const int val) : Base(val), d_val(val) {}
  };

  atl::shared_ptr<Base> spBaseBase(new Base(0));
  ASSERT_EQ(1, spBaseBase->b_val);
  atl::shared_ptr<Base> spBaseDerived(new Derived(0));
  ASSERT_EQ(1, spBaseDerived->b_val);

  atl::shared_ptr<Derived> spDerivedDerived =
      atl::static_pointer_cast<Derived>(spBaseDerived);

  ASSERT_EQ(0, spDerivedDerived->d_val);
  ASSERT_EQ(1, spDerivedDerived->b_val);
}

TEST(SharedPtrTest, SharedPtrInheritence) {
  class Base {
  public:
    virtual int val() { return 0; }
  };
  class Derived : public Base {
  public:
    int val() override { return 1; }
  };

  atl::shared_ptr<Derived> spDerived(new Derived());

  atl::shared_ptr<Base> spBase(spDerived);

  ASSERT_EQ(spDerived->val(), spBase->val());
}

class TestInt : public atl::enable_shared_from_this<TestInt> {
public:
  int val;
  explicit TestInt(const int val) : val(val) {}
  atl::shared_ptr<TestInt> get_ptr() { return shared_from_this(); }
};

atl::shared_ptr<TestInt> getTestIntSP2() {
  return atl::make_shared<TestInt>(TestInt(5));
}

atl::shared_ptr<TestInt> getTestIntSP() { return getTestIntSP2(); }
TestInt getTestInt() { return TestInt(5); }

TEST(SharedPtrTest, SharedFromThisCopyConstructor) {
  atl::shared_ptr<TestInt> myTestIntPtr1 = getTestIntSP();
  atl::shared_ptr<TestInt> myTestIntPtr2 = myTestIntPtr1;
  atl::shared_ptr<TestInt> myTestIntPtr3 =
      atl::make_shared<TestInt>(getTestInt());

  ASSERT_TRUE(myTestIntPtr1 == myTestIntPtr2);
  ASSERT_TRUE(5 == myTestIntPtr2->val);
  ASSERT_TRUE(5 == myTestIntPtr3->val);
}

class Base {
public:
  virtual ~Base() {}
};

class Derived : public Base, public atl::enable_shared_from_this<Base> {
public:
  atl::shared_ptr<Derived> getptr() { return shared_from_this(); }
};

atl::shared_ptr<Derived> getDerivedBaseImpl() {
  atl::shared_ptr<Derived> output = atl::make_shared<Derived>(Derived());
  return output;
}
atl::shared_ptr<Base> getDerivedBase() {
  atl::shared_ptr<Derived> temp = getDerivedBaseImpl();
  atl::shared_ptr<Base> output = getDerivedBaseImpl();
  return output;
}

atl::shared_ptr<Base> getBasePoly() {
  atl::shared_ptr<Base> output;
  output = getDerivedBase();
  return output;
}

TEST(SharedPtrTest, TBDTest) {
  atl::shared_ptr<Base> derivedPtr = getBasePoly();
}

TEST(SharedPtrTest, OperatorBool) {
  atl::shared_ptr<int> nullPtr;
  atl::shared_ptr<int> intPtr(new int(5));

  if (nullPtr) {
    ASSERT_TRUE(false);
  } else if (intPtr) {
    ASSERT_TRUE(true);
  } else {
    ASSERT_TRUE(false);
  }
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