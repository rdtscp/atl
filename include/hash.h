#pragma once

#include "string.h"
#include "types.h"

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
  const uint32_t len_s = s.size();
  for (uint32_t i = 0; i < len_s; ++i) {
    output += (long)power(prime, len_s - (i + 1)) * s[i];
    output = output % max;
  }
  return static_cast<int>(output);
}

} // namespace atl
