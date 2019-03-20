#pragma once

#include "string.h"

namespace atl {

static long power(int value, int exponent) {
  long output = value;
  for (int i = 0; i < exponent; ++i)
    output *= output;
  return output;
}

/* https://github.com/jamesroutley/write-a-hash-table */
static int hash(const atl::string &s, const long max, const long prime = 163) {
  long output = 0;
  const int len_s = s.size();
  for (int i = 0; i < len_s; ++i) {
    output += (long)power(prime, len_s - (i + 1)) * s[i];
    output = output % max;
  }
  return (int)output;
}

} // namespace atl
