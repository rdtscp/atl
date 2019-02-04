#pragma once

#ifndef ATL_SHARED_PTR_H
#define ATL_SHARED_PTR_H

namespace atl {

template <typename T> class shared_ptr {

public:
  /* Constructor */
  shared_ptr<T>() : refCount(nullptr), ptr(nullptr) {}

  /* Constructor */
  shared_ptr<T>(T *ptr) : refCount(new int(1)), ptr(ptr) {}

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

  bool operator==(const shared_ptr<T> &rhs) { return ptr == rhs.ptr; }

  bool operator!=(const shared_ptr<T> &rhs) { return ptr != rhs.ptr; }

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
};

template <typename T> static shared_ptr<T> make_shared(const T &&obj) {
  return shared_ptr<T>(new T(obj));
}

} // namespace atl

#endif