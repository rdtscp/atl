#pragma once

namespace atl {

template <typename T> class shared_ptr;
template <typename TO, typename FROM>
static shared_ptr<TO> static_pointer_cast(const shared_ptr<FROM> &ptr);

template <typename T> class enable_shared_from_this {
protected:
  enable_shared_from_this() {}
  enable_shared_from_this(enable_shared_from_this const &ptr) {
    /* Does nothing, but used for dynamic dispatch. */
    (void)ptr;
  }
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
  shared_ptr<T>() : m_ref(new int(0)), m_ptr(nullptr) {}

  /* Constructor */
  shared_ptr<T>(T *ptr) : m_ref(new int(1)), m_ptr(ptr) {
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

    m_ptr = rhs.m_ptr;
    m_ref = rhs.m_ref;
    *m_ref = *m_ref + 1;
  }

  /* Assignment Operator */
  shared_ptr<T> &operator=(const shared_ptr<T> &rhs) {
    if (&rhs == this)
      return *this;

    m_ptr = rhs.m_ptr;
    m_ref = rhs.m_ref;
    *m_ref = *m_ref + 1;
    return *this;
  }

  /* Assignment Operator */
  template <typename B> shared_ptr<T> &operator=(const shared_ptr<B> &rhs) {
    *this = static_pointer_cast<T>(rhs);
    return *this;
  }

  /* Destructor */
  ~shared_ptr<T>() {
    if (m_ref == nullptr)
      return;
    else if (m_ptr == nullptr)
      return;
    else if (*m_ref == 0) {
      delete m_ref;
      delete m_ptr;
    } else
      *m_ref = *m_ref - 1;
  }

  T *operator->() const { return m_ptr; }

  T &operator*() const { return *m_ptr; }

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

private:
  int *m_ref;
  T *m_ptr;

  void initialiseSharedFromThis(enable_shared_from_this<T> *obj) {
    if (obj != nullptr)
      obj->self_ = *this;
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
  TO *outputPtr = static_cast<TO *>(ptr.get());
  return shared_ptr<TO>(outputPtr);
}

} // namespace atl
