#pragma once

#include <cstddef>

#include "detail/shared_count.h"
#include "enable_shared_from_this.h"
#include "swap.h"

namespace atl {

template <typename T>
class shared_ptr {
public:
  /* Constructors */
  shared_ptr() : m_ptr(nullptr), m_ref(new shared_count(1, 0)) {}

  shared_ptr(std::nullptr_t) : shared_ptr() {}

  explicit shared_ptr(T *ptr) : m_ptr(ptr), m_ref(new shared_count(1, 0)) {
    intialise_shared_from_this(m_ptr, m_ref);
  }

  template <typename Derived>
  shared_ptr(const shared_ptr<Derived> &rhs) : shared_ptr() {
    *this = static_pointer_cast<T>(rhs);
  }

  /* Copy Constructor */
  shared_ptr(const shared_ptr &rhs) : m_ptr(rhs.m_ptr), m_ref(rhs.m_ref) {
    m_ref->increment_shared();
  }

  /* Assignemnt Operator */
  shared_ptr &operator=(shared_ptr rhs) {
    if (this == &rhs)
      return *this;

    atl::swap(m_ptr, rhs.m_ptr);
    atl::swap(m_ref, rhs.m_ref);
    return *this;
  }

  /* Assignemnt Operator */
  template <typename Derived>
  shared_ptr &operator=(const shared_ptr<Derived> &rhs) {
    shared_ptr<T> rhs_upcast = static_pointer_cast<T>(rhs);
    atl::swap(*this, rhs_upcast);
    return *this;
  }

  /* Destructor */
  ~shared_ptr() {
    m_ref->decrement_shared();
    if (m_ref->user_count() == 0) {
      /* We must store the weak count here before deleting `m_ptr` because `m_ptr` may be of
       * type `enable_shared_from_this` which upon destruction will clean up its own weak_ptr.
       * If there is another weak_ptr elsewhere, it'll clean up the `m_ref` when it destructs.
       */
      const int weak_count = m_ref->weak_count();
      delete m_ptr;
      m_ptr = nullptr;
      if (weak_count == 0) {
        delete m_ref;
      }
      m_ref = nullptr;
    }
  }

  /* Accessors */
  T &operator*() const {
    return *m_ptr;
  }

  T *operator->() const {
    return m_ptr;
  }

  T *get() const {
    return m_ptr;
  }

  operator bool() const {
    return m_ptr != nullptr;
  }

  /* Only for use in `static_pointer_cast`. */
  atl::shared_count *get_ref_counter() const {
    return m_ref;
  }

  /* Only for use by `weak_ptr`. */
  shared_ptr(T *ptr, atl::shared_count *ref) : m_ptr(ptr), m_ref(ref) {
    m_ref->increment_shared();
  }

private:
  T *m_ptr;
  atl::shared_count *m_ref;

  template <typename Derived>
  void intialise_shared_from_this(atl::enable_shared_from_this<Derived> *ptr, atl::shared_count *ref) {
    ptr->__create_weak_ptr(static_cast<Derived*>(ptr), ref);
  }

  void intialise_shared_from_this(atl::enable_shared_from_this<T> *ptr, atl::shared_count *ref) {
    ptr->__create_weak_ptr(static_cast<T*>(ptr), ref);
  }

  void intialise_shared_from_this(void *, atl::shared_count *) {
    // Do nothing. Dynamic Dispatch.
  }

};

template <typename T, typename U>
bool operator==(const shared_ptr<T> &lhs, const shared_ptr<U> &rhs) {
  return lhs.get() == rhs.get();
}

template <typename T, typename U>
bool operator!=(const shared_ptr<T> &lhs, const shared_ptr<U> &rhs) {
  return !(lhs == rhs);
}

template <typename T>
bool operator==(const shared_ptr<T> &lhs, const std::nullptr_t) {
  return lhs.get() == nullptr;
}

template <typename T>
bool operator!=(const shared_ptr<T> &lhs, const std::nullptr_t) {
  return !(lhs == nullptr);
}

template<typename TO, class FROM>
atl::shared_ptr<TO> static_pointer_cast(const atl::shared_ptr<FROM> &rhs) {
  return atl::shared_ptr<TO>(static_cast<TO*>(rhs.get()), rhs.get_ref_counter());
}

} // namespace atl