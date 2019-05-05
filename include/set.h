#pragma once

namespace atl {

template <typename T> class set {

public:
  /* Constructor */
  set<T>() : elements_size(0), elements_used(0), initialised(false) {}

  /* Copy Constructor */
  set<T>(const set<T> &rhs) {
    if (this == &rhs)
      return;
    allocate(rhs.capacity());
    elements_used = 0;
    for (unsigned int i = 0; i < rhs.elements_used; ++i)
      push_back(rhs[i]);
  }

  /* Assignment Operator */
  set<T> &operator=(const set<T> &rhs) {
    if (this == &rhs)
      return *this;
    allocate(rhs.capacity());
    elements_used = 0;
    for (unsigned int i = 0; i < rhs.size(); ++i)
      push_back(rhs[i]);
    return *this;
  }

  /* Move Constructor */
  set<T>(const set<T> &&rhs) {
    if (this == &rhs)
      return;
    allocate(rhs.capacity());
    for (unsigned int i = 0; i < rhs.elements_used; ++i)
      push_back(rhs[i]);
  }

  /* Move-Assignment Operator */
  set<T> &operator=(const set<T> &&rhs) {
    if (this == &rhs)
      return *this;
    allocate(rhs.capacity());
    for (unsigned int i = 0; i < rhs.size(); ++i)
      push_back(rhs[i]);
    return *this;
  }

  /* Destructor */
  ~set<T>() {
    if (initialised)
      delete[] elements;
  }

  bool operator==(const set<T> &rhs) const {
    if (this == &rhs)
      return true;

    if (size() != rhs.size())
      return false;

    for (unsigned int i = 0; i < rhs.size(); ++i)
      if (at(i) != rhs.at(i))
        return false;

    return true;
  }

  bool operator!=(const set<T> &rhs) const { return !(*this == rhs); }

  bool find(const T &elem) {
    for (unsigned int idx = 0; idx < size(); ++idx)
      if (elements[idx] == elem)
        return true;

    return false;
  }

  void insert(const T &elem) {
    if (!find(elem)) {
      push_back(elem);
    }
  }

  unsigned int size() const { return elements_used; }

private:
  unsigned int elements_size;
  unsigned int elements_used;
  bool initialised;
  T *elements;

  const T &operator[](const int index) const { return at(index); }

  /* Allocate a new array of size num_elems. Set elements_size. */
  void allocate(const int num_elems) {
    elements = new T[num_elems];
    elements_size = num_elems;
  }

  T &at(const int index) const {
    if (index < elements_size) {
      return elements[index];
    }
    throw "atl::vector::at Out of Bounds Exception";
  }

  int capacity() const { return elements_size; }

  /* Extend the size of elements[] by num_elems. */
  void extend(const int num_elems) {
    /* Store the current state of the set. */
    const int temp_elements_size = elements_size;
    T *temp_elements = new T[elements_size];
    for (unsigned int i = 0; i < elements_size; ++i)
      temp_elements[i] = elements[i];

    /* Clear the set state. */
    delete[] elements;
    elements_used = 0;

    /* Re-initialise the state of the set using the extension. */
    allocate(temp_elements_size + num_elems);
    for (elements_used = 0; elements_used < temp_elements_size; ++elements_used)
      elements[elements_used] = temp_elements[elements_used];
  }

  void push_back(const T &elem) {
    if (!initialised) {
      allocate(1);
      initialised = true;
    }
    if (elements_used >= elements_size)
      extend(1);

    elements[elements_used] = elem;
    ++elements_used;
  }
};

} // namespace atl
