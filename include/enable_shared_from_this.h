#pragma once

#include "detail/weak_ptr.h"

namespace atl {

template<typename TO, class FROM>
atl::shared_ptr<TO> static_pointer_cast(const atl::shared_ptr<FROM> &rhs);

template<class T>
class enable_shared_from_this {
protected:
    enable_shared_from_this() {}

    enable_shared_from_this(const enable_shared_from_this &) {}

    enable_shared_from_this &operator=(const enable_shared_from_this &) {
      return *this;
    }

    ~enable_shared_from_this() {}

public:
    shared_ptr<T> shared_from_this() {
      return shared_ptr<T>(m_weak_this.lock());
      // return shared_ptr<T>(m_weak_this);
    }

    shared_ptr<T const> shared_from_this() const {
      return shared_ptr<T const>(m_weak_this.lock());
      // return shared_ptr<T const>(m_weak_this);
    }

    void __set_weak_ptr(atl::shared_count *ref) {
      if (m_weak_this.expired()) {
        m_weak_this.__set(static_cast<T*>(this), ref);
      }
    }

private:
    mutable weak_ptr<T> m_weak_this;
};

} // namespace atl