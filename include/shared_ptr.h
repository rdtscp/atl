#pragma once

#ifndef ATL_SHARED_PTR_H
#define ATL_SHARED_PTR_H

namespace atl {

template <typename T> class shared_ptr;
template <typename TO, typename FROM>
static shared_ptr<TO> static_pointer_cast(const shared_ptr<FROM> &ptr);

template <typename T> class enable_shared_from_this {
protected:
  enable_shared_from_this() {}
  enable_shared_from_this(enable_shared_from_this const &ptr) { self_(ptr); }
  enable_shared_from_this &operator=(enable_shared_from_this const &) {
    return *this;
  }

public:
  shared_ptr<T> shared_from_this() { return self_; }
  shared_ptr<T const> shared_from_this() const { return self_; }

  shared_ptr<T> self_;
};

template <typename T> class shared_ptr {

public:
  /* Constructor */
  shared_ptr<T>() : refCount(nullptr), ptr(nullptr) {
    initialiseSharedFromThis(ptr);
  }

  /* Constructor */
  shared_ptr<T>(T *ptr) : refCount(new int(1)), ptr(ptr) {
    initialiseSharedFromThis(ptr);
  }

  /* Constructor */
  template <typename B> shared_ptr<T>(const shared_ptr<B> &rhs) {
    *this = static_pointer_cast<T>(rhs);
  }

  /* Copy Constructor */
  shared_ptr<T>(const shared_ptr<T> &rhs) {
    if (&rhs == this)
      return;

    if (rhs.ptr == nullptr || rhs.refCount == nullptr)
      return;

    ptr = rhs.ptr;
    refCount = rhs.refCount;
    *refCount = *refCount + 1;
  }

  /* Assignment Operator */
  shared_ptr<T> &operator=(const shared_ptr<T> &rhs) {
    if (&rhs == this)
      return *this;

    if (rhs.ptr == nullptr || rhs.refCount == nullptr)
      return *this;

    ptr = rhs.ptr;
    refCount = rhs.refCount;
    *refCount = *refCount + 1;
    return *this;
  }

  /* Assignment Operator */
  template <typename B> shared_ptr<T> &operator=(const shared_ptr<B> &rhs) {
    *this = static_pointer_cast<T>(rhs);
    return *this;
  }

  /* Move Constructor */
  shared_ptr<T>(const shared_ptr<T> &&rhs) {
    if (&rhs == this)
      return;

    if (rhs.ptr == nullptr || rhs.refCount == nullptr)
      return;

    ptr = rhs.ptr;
    refCount = rhs.refCount;
    // *refCount = *refCount + 1;
  }

  /* Move-Assignment Operator */
  shared_ptr<T> &operator=(const shared_ptr<T> &&rhs) {
    if (&rhs == this)
      return *this;

    if (rhs.ptr == nullptr || rhs.refCount == nullptr)
      return *this;

    ptr = rhs.ptr;
    refCount = rhs.refCount;
    // *refCount = *refCount + 1;
    return *this;
  }

  /* Move-Assignment Operator */
  template <typename B> shared_ptr<T> &operator=(const shared_ptr<B> &&rhs) {
    *this = static_pointer_cast<T>(rhs);
    return *this;
  }

  /* Destructor */
  ~shared_ptr<T>() {
    if (refCount == nullptr)
      return;
    else if (*refCount == 0) {
      delete refCount;
      delete ptr;
    } else
      *refCount = *refCount - 1;
  }

  T *operator->() const { return ptr; }

  T &operator*() const { return *ptr; }

  bool operator==(const shared_ptr<T> &rhs) const { return ptr == rhs.ptr; }

  bool operator!=(const shared_ptr<T> &rhs) const { return ptr != rhs.ptr; }

  operator bool() const { return ptr; }

  T *get() const { return ptr; }

  int use_count() const {
    if (refCount == nullptr)
      return 0;
    else
      return *refCount;
  }

private:
  int *refCount;
  T *ptr;

  void initialiseSharedFromThis(enable_shared_from_this<T> *obj) {
    obj->self_ = *this;
  }

  void initialiseSharedFromThis(void *obj) {
    /* Not an enable_shared_from_this object, nothing to construct. */
  }
};

template <typename T> static shared_ptr<T> make_shared() {
  return shared_ptr<T>(new T());
}

template <typename T> static shared_ptr<T> make_shared(const T &&obj) {
  return shared_ptr<T>(new T(obj));
}

template <typename TO, typename FROM>
static shared_ptr<TO> static_pointer_cast(const shared_ptr<FROM> &ptr) {
  return shared_ptr<TO>(static_cast<TO *>(ptr.get()));
}

} // namespace atl

#endif