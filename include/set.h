#pragma once
#include "vector.h"
#include <iostream>
namespace atl {

template <typename T> class set {

public:
  /* Constructor */
  set<T>() {}

  /* Initializer-List Constructor */
  set<T>(std::initializer_list<T> list) {
    for (const T &item: list)
      insert(item);
  }

  /* Copy Constructor */
  set<T>(const set<T> &rhs) {
    if (this == &rhs)
      return;

    m_elements.clear();
    m_elements.reserve(rhs.size());
    for (unsigned int i = 0; i < rhs.size(); ++i)
      insert(rhs.m_elements[i]);
  }

  /* Assignment Operator */
  set<T> &operator=(const set<T> &rhs) {
    if (this == &rhs)
      return *this;

    m_elements.clear();
    m_elements.reserve(rhs.size());
    for (unsigned int i = 0; i < rhs.size(); ++i)
      insert(rhs[i]);
    return *this;
  }

  /* Destructor */
  ~set<T>() {}

  bool operator==(const set<T> &rhs) const {
    if (this == &rhs)
      return true;

    if (size() != rhs.size())
      return false;

    for (unsigned int i = 0; i < rhs.size(); ++i)
      if (m_elements[i] != rhs.m_elements[i])
        return false;

    return true;
  }

  bool operator!=(const set<T> &rhs) const { return !(*this == rhs); }

  bool find(const T &elem) const {
    for (unsigned int idx = 0; idx < size(); ++idx)
      if (m_elements[idx] == elem)
        return true;

    return false;
  }

  void insert(const T &elem) {
    if (!find(elem)) {
      m_elements.push_back(elem);
    }
  }

  unsigned int size() const { return m_elements.size(); }

private:
  atl::vector<T> m_elements;

};

} // namespace atl
