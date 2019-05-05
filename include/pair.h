#pragma once

namespace atl {

template <typename F, typename S> class pair {

public:
  F first;
  S second;

  /* Constructor */
  pair<F, S>() : first(), second() {}

  /* Constructor */
  pair<F, S>(const F &first, const S &second) : first(first), second(second) {}

  /* Copy Constructor */
  pair<F, S>(const pair<F, S> &rhs) {
    if (this == &rhs)
      return;
    first = rhs.first;
    second = rhs.second;
  }

  /* Assignment Operator */
  pair<F, S> &operator=(const pair<F, S> &rhs) {
    if (this == &rhs)
      return *this;

    first = rhs.first;
    second = rhs.second;
    return *this;
  }

  bool operator==(const pair<F, S> &rhs) const {
    if (first != rhs.first)
      return false;

    return second == rhs.second;
  }
};

} // namespace atl
