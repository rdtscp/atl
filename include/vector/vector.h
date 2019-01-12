#pragma once

#ifndef ATL_VECTOR_H
#define ATL_VECTOR_H

#include <memory>

namespace atl {

template <typename T> class vector {

public:
  /* Constructor */
  vector<T>() : elements_size(0), elements_used(0), initialised(false) {}

  /* Constructor */
  vector<T>(const int size)
      : elements_size(size), elements_used(0), initialised(true) {
    allocate(size);
    for (int i = 0; i < size; i++)
      push_back(0);
  }

  /* Copy Constructor */
  vector<T>(const vector<T> &rhs) {}

  /* Assignment Operator */
  vector<T> &operator=(const vector<T> &rhs) {}

  /* Move Constructor */
  vector<T>(const vector<T> &&rhs) {}

  /* Move-Assignment Operator */
  vector<T> &operator=(const vector<T> &&rhs) {}

  /* Destructor */
  ~vector<T>() {
    if (initialised)
      delete[] elements;
  }

  int capacity() const { return elements_size; }

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

  T pop_back() {}

  void reserve(const int size) {
    if (size <= elements_size)
      return;
    if (initialised) {
    }
    allocate(size);
  }

  int size() const { return elements_used; }

private:
  int elements_size;
  int elements_used;
  bool initialised;
  T *elements;

  /* Extend the size of elements[] by num_elems. */
  void extend(const int num_elems) {
    /* Store the current state of the vector. */
    const int temp_elements_size = elements_size;
    const int temp_elements_used = elements_used;
    T *temp_elements = new T[elements_size];
    for (int i = 0; i < elements_size; ++i)
      temp_elements[i] = elements[i];

    /* Clear the vector state. */
    delete[] elements;
    elements_used = 0;

    /* Re-initialise the state of the vector using the extension. */
    allocate(temp_elements_size + num_elems);
    for (elements_used = 0; elements_used < temp_elements_size; ++elements_used)
      elements[elements_used] = temp_elements[elements_used];
  }

  /* Allocate a new array of size num_elems. Set elements_size. */
  void allocate(const int num_elems) {
    elements = new T[num_elems];
    elements_size = num_elems;
  }
};

} // namespace atl

#endif