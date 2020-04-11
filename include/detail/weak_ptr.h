#pragma once

#include "shared_count.h"
#include "../swap.h"

namespace atl {

template <typename T> class shared_ptr;

template <typename T>
class weak_ptr {
public:
  weak_ptr() : m_ptr(nullptr), m_ref(nullptr) {}

  weak_ptr(T *ptr, atl::shared_count *ref) : m_ptr(ptr), m_ref(ref) {}

  shared_ptr<T> lock() const {
    shared_ptr<T> output;
    if (!expired()) {
      output.__set(m_ptr, m_ref);
    }
    return output;
  }

  long use_count() const {
    if (m_ref)
      return m_ref->use_count();
  
    return 0;
  }

  bool expired() const {
    return use_count() == 0;
  }

  /* Only for use by `shared_ptr`. */
  void __set(T *ptr, atl::shared_count *ref) {
    delete m_ref;

    atl::swap(m_ptr, ptr);
    atl::swap(m_ref, ref);
  }

private:
  T *m_ptr;
  atl::shared_count *m_ref;

};

} // namespace atl