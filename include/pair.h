#pragma once

#include "swap.h"

namespace atl {

template <typename F, typename S>
class pair {
public:
  F first;
  S second;

  /* Constructor */
  pair() : first(), second() {}

  /* Constructor */
  pair(const F &first, const S &second) : first(first), second(second) {}

  /* Copy Constructor */
  pair(const pair<F, S> &rhs) first(rhs.first), second(rhs.second) {}

  /* Assignment Operator */
  pair &operator=(pair rhs) {
    if (this == &rhs)
      return *this;

    atl::swap(first, rhs.first);
    atl::swap(second, rhs.second);
    return *this;
  }

  bool operator==(const pair<F, S> &rhs) const {
    if (first != rhs.first)
      return false;

    return second == rhs.second;
  }
};

} // namespace atl
