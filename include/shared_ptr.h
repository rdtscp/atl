#pragma once

#include <cstddef>

namespace atl {

template <typename T> class shared_ptr;
template <typename TO, typename FROM>
static shared_ptr<TO> static_pointer_cast(const shared_ptr<FROM> &ptr);

template <typename T> class enable_shared_from_this {
protected:
  enable_shared_from_this() : self_() {}
  enable_shared_from_this(enable_shared_from_this const &ptr) : self_(ptr.self_) {
    /* Does nothing, but used for dynamic dispatch. */
    (void)ptr;
  }
  enable_shared_from_this &operator=(enable_shared_from_this const &) {
    return *this;
  }

public:
  shared_ptr<T> shared_from_this() { return self_; }
  shared_ptr<T const> shared_from_this() const { return self_; }

  shared_ptr<T> self_ = nullptr;
};

template <typename T> class shared_ptr {
public:
  /* Constructor */
  shared_ptr() : m_ref(new int(1)), m_ptr(nullptr) {}

  /* Constructor */
  shared_ptr(std::nullptr_t) : m_ref(new int(1)), m_ptr(nullptr) {}

  /* Constructor */
  explicit shared_ptr(T *ptr) : m_ref(new int(1)), m_ptr(ptr) {
    initialiseSharedFromThis(ptr);
  }

  /* Constructor - `static_pointer_cast` constructor. */
  template <typename Base>
  shared_ptr(T *ptr, shared_ptr<Base> base) : m_ref(base.m_ref), m_ptr(ptr) {
    ++(*m_ref);
  }

  /* Constructor */
  template <typename B> shared_ptr(const shared_ptr<B> &rhs) {
    *this = static_pointer_cast<T>(rhs);
  }

  /* Copy Constructor */
  shared_ptr(const shared_ptr<T> &rhs) {
    if (&rhs == this)
      return;

    m_ptr = rhs.m_ptr;
    m_ref = rhs.m_ref;
     ++(*m_ref); 
  }

  /* Assignment Operator */
  shared_ptr<T> &operator=(const shared_ptr<T> &rhs) {
    if (&rhs == this)
      return *this;

    if (m_ref) {
      --(*m_ref);
      if (*m_ref == 0) {
        delete m_ptr;
        delete m_ref;
      }
    }

    m_ptr = rhs.m_ptr;
    m_ref = rhs.m_ref;
     ++(*m_ref); 
    return *this;
  }

  /* Assignment Operator */
  template <typename B> shared_ptr &operator=(const shared_ptr<B> &rhs) {
    *this = static_pointer_cast<T>(rhs);
    return *this;
  }

  /* Destructor */
  ~shared_ptr<T>() {
      --(*m_ref);
      if (*m_ref == 0) {
        delete m_ptr;
        delete m_ref;
      }
  }

  T *operator->() const { return m_ptr; }

  T &operator*() const { return *m_ptr; }

  bool operator==(std::nullptr_t) const { return m_ptr == nullptr; }
  bool operator!=(std::nullptr_t) const { return m_ptr != nullptr; }

  bool operator==(const shared_ptr<T> &rhs) const { return m_ptr == rhs.m_ptr; }

  bool operator!=(const shared_ptr<T> &rhs) const { return !(*this == rhs); }

  bool operator<(const shared_ptr<T> &rhs) const { return get() < rhs.get(); }

  operator bool() const { return m_ptr; }

  T *get() const { return m_ptr; }

  int use_count() const {
    if (m_ref == nullptr)
      return 0;
    else
      return *m_ref;
  }

  int *m_ref = nullptr;
private:
  T *m_ptr = nullptr;

  void initialiseSharedFromThis(enable_shared_from_this<T> *obj) {
    if (obj != nullptr) {
      /* Explicitly copy the members rather than the object as we don't want to increase the ref-count here
       * otherwise we will never destruct an object deriving from `enable_shared_from_this` */
      delete obj->self_.m_ref;
      obj->self_.m_ptr = m_ptr;
      obj->self_.m_ref = m_ref;
    }
  }

  void initialiseSharedFromThis(void *obj) {
    /* Not an enable_shared_from_this object, nothing to construct. */
    /* Does nothing, but used for dynamic dispatch. */
    (void)obj;
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
  return shared_ptr<TO>(static_cast<TO *>(ptr.get()), ptr);
}

} // namespace atl
