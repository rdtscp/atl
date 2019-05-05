#pragma once

#include "vector.h"

namespace atl {

template <typename T> class stack : public vector<T> {
public:
  T &top() { return vector<T>::at(vector<T>::size() - 1); }

  const T &top() const { return vector<T>::at(vector<T>::size() - 1); }
};

} // namespace atl
