#pragma once

#include "../include/string.h"
#include <stdio.h>

extern "C" void *memset(void *__b, int __c, size_t __len);

namespace atl {

class ifstream {

public:
  /* Constructor */
  ifstream(const atl::string &filename) {
    filePtr = fopen(filename.c_str(), "r");
  }

  ~ifstream() { fclose(filePtr); }

  bool good() {
    if (filePtr)
      return true;
    else
      return false;
  }

  atl::string readIntoString() {
    atl::string output;

    FILE *file_p = filePtr;
    const int buffer_size = 2048;
    char *fgets_res = nullptr;
    char temp_buffer[buffer_size];
    do {
      memset(temp_buffer, 0, buffer_size);
      fgets_res = fgets(temp_buffer, buffer_size, file_p);
      output += temp_buffer;
    } while (fgets_res != nullptr);

    return output;
  }

private:
  FILE *filePtr;
};

} // namespace atl
