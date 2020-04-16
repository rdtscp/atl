#pragma once

#include "shared_count.h"
#include "../swap.h"

namespace atl {

template <typename T> class shared_ptr;

template <typename T>
class weak_ptr {
public:
  weak_ptr() : m_ptr(nullptr), m_ref(new shared_count(0, 1)) {}

  weak_ptr(std::nullptr_t) : weak_ptr() {}

  weak_ptr(const atl::shared_ptr<T> &rhs) : m_ptr(rhs.get()), m_ref(rhs.get_ref_counter()) {
    m_ref->increment_weak();
  }

  weak_ptr(const weak_ptr &rhs) : m_ptr(rhs.m_ptr), m_ref(rhs.m_ref) {
    m_ref->increment_weak();
  }

  weak_ptr &operator=(weak_ptr rhs) {
    if (this == &rhs)
      return *this;

    atl::swap(m_ptr, rhs.m_ptr);
    atl::swap(m_ref, rhs.m_ref);
    return *this;
  }

  template <typename Derived>
  weak_ptr &operator=(const shared_ptr<Derived> &rhs) {
    weak_ptr<T> rhs_upcast(static_cast<T*>(rhs.get()), rhs.get_ref_counter());
    atl::swap(*this, rhs_upcast);
    return *this;
  }

  ~weak_ptr() {
    m_ref->decrement_weak();
    if (m_ref->weak_count() == 0 && expired()) {
      delete m_ref;
      m_ref = nullptr;
    }
  }

  shared_ptr<T> lock() const {
    if (!expired()) {
      return shared_ptr<T>(m_ptr, m_ref);
    }
    return shared_ptr<T>();
  }

  long use_count() const {
    if (m_ref)
      return m_ref->user_count();
  
    return 0;
  }

  bool expired() const {
    return use_count() == 0;
  }

  /* Only for use by `shared_ptr`. */
  weak_ptr(T *ptr, atl::shared_count *ref) : m_ptr(ptr), m_ref(ref) {
    m_ref->increment_weak();
  }

private:
  T *m_ptr;
  atl::shared_count *m_ref;

};

} // namespace atl