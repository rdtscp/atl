#pragma once
#include <initializer_list>
#include <iostream>

#include "swap.h"
#include "types.h"

namespace atl {

template <typename T>
class vector {
private:
  uint32_t m_elements_size = 0;
  uint32_t m_elements_used = 0;
  T *m_elements = nullptr;

public:
  /* Default Constructor */
  vector<T>() {}

  /* Initializer-List Constructor */
  vector<T>(std::initializer_list<T> list) {
    reserve(list.size());
    for (const T &item : list)
      push_back(item);
  }

  /* Size Constructor */
  vector<T>(const uint32_t size) {
    reserve(size);
    for (uint32_t idx = 0; idx < capacity(); ++idx)
      push_back(T());
  }

  /* Copy Constructor */
  vector<T>(const vector<T> &rhs) {
    if (this == &rhs)
      return;

    reserve(rhs.capacity());
    for (m_elements_used = 0; m_elements_used < rhs.size(); ++m_elements_used) {
      m_elements[m_elements_used] = rhs.at(m_elements_used);
    }
  }

  /* Assignment Operator */
  vector<T> &operator=(vector<T> rhs) {
    if (this == &rhs)
      return *this;

    atl::swap(m_elements, rhs.m_elements);
    atl::swap(m_elements_size, rhs.m_elements_size);
    atl::swap(m_elements_used, rhs.m_elements_used);
    return *this;
  }

  /* Move Constructor */
  vector<T>(vector<T> &&rhs) : vector() {
    atl::swap(m_elements, rhs.m_elements);
    atl::swap(m_elements_size, rhs.m_elements_size);
    atl::swap(m_elements_used, rhs.m_elements_used);
  }

  /* Destructor */
  ~vector<T>() { deallocate(); }

  T &operator[](const uint32_t index) { return at(index); }

  const T &operator[](const uint32_t index) const { return at(index); }

  T &at(const uint32_t index) {
    if (index < m_elements_size) {
      return m_elements[index];
    }
    printf("%s\n", "atl::vector::at Out of Bounds Exception");
    throw;
  }

  T &at(const uint32_t index) const {
    if (index < m_elements_size) {
      return m_elements[index];
    }
    printf("%s\n", "atl::vector::at Out of Bounds Exception");
    throw;
  }

  uint32_t capacity() const { return m_elements_size; }

  void clear() { deallocate(); }

  T erase(const uint32_t eraseIndex) {
    if (eraseIndex > m_elements_size) {
      printf("%s\n", "atl::vector::erase Out of Bounds Exception");
      throw;
    }
    /* Store our output value. */
    const T output = at(eraseIndex);
    
    /* Copy all but the erased index. */
    T *new_buffer = new T[m_elements_size  - 1];
    uint32_t new_buffer_idx = 0;
    for (uint32_t idx = 0; idx < m_elements_size; ++idx) {
      if (idx == eraseIndex)
        continue;

      new_buffer[new_buffer_idx] = m_elements[idx];
      ++new_buffer_idx;
    }

    delete[] m_elements;
    m_elements = new_buffer;
    --m_elements_size;
    --m_elements_used;

    return output;
  }

  void push_back(const T &elem) {
    reserve(size() + 1);

    m_elements[m_elements_used] = elem;
    ++m_elements_used;
  }

  void push_front(const T &elem) {
    reserve(size() + 1);

    for (uint32_t idx = m_elements_used; idx > 0; --idx)
      m_elements[idx] = m_elements[idx - 1];

    m_elements[0] = elem;
    ++m_elements_used;
  }

  T pop_back() {
    if (size() == 0) {
      throw "atl::vector::pop_back empty exception";
    }
    return erase(m_elements_used - 1);
  }

  void reserve(const uint32_t reserveSize) {
    if (reserveSize == 0)
      return;

    /* Already have requested space. */
    if (reserveSize <= m_elements_size)
      return;

    /* Store the new size of the vector. */
    m_elements_size = reserveSize;

    /* Allocate for new size */
    T *new_buffer = new T[m_elements_size];

    /* We have existing elements. */
    if (m_elements != nullptr) {
      /* Copy across existing elements. */
      for (uint32_t idx = 0; idx < m_elements_used; ++idx) {
        new_buffer[idx] = m_elements[idx];
      }
    }

    delete[] m_elements;
    m_elements = new_buffer;
  }

  uint32_t size() const { return m_elements_used; }

private:

  void deallocate() {
    delete[] m_elements;
    m_elements = nullptr;
    m_elements_size = 0;
    m_elements_used = 0;
  }
};

} // namespace atl
