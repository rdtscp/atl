#pragma once
#include "types.h"
#include "vector.h"
#include <iostream>
namespace atl {

template <typename T>
class set {
private:
  atl::vector<T> m_elements;

public:
  /* Constructor */
  set<T>() {}

  /* Initializer-List Constructor */
  set<T>(std::initializer_list<T> list) {
    for (const T &item: list)
      insert(item);
  }

  /* Copy Constructor */
  set<T>(const set<T> &rhs) : m_elements(rhs.m_elements) {}

  /* Assignment Operator */
  set<T> &operator=(set<T> rhs) {
    if (this == &rhs)
      return *this;

    atl::swap(m_elements, rhs.m_elements);
    return *this;
  }

  /* Destructor */
  ~set<T>() {}

  bool operator==(const set<T> &rhs) const {
    if (this == &rhs)
      return true;

    if (size() != rhs.size())
      return false;

    for (uint32_t i = 0; i < rhs.size(); ++i)
      if (m_elements[i] != rhs.m_elements[i])
        return false;

    return true;
  }

  bool operator!=(const set<T> &rhs) const { return !(*this == rhs); }

  bool find(const T &elem) const {
    for (uint32_t idx = 0; idx < size(); ++idx)
      if (m_elements[idx] == elem)
        return true;

    return false;
  }

  void insert(const T &elem) {
    if (!find(elem)) {
      m_elements.push_back(elem);
    }
  }

  uint32_t size() const { return m_elements.size(); }

};

} // namespace atl
