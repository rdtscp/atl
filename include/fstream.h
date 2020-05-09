#pragma once

#include "../include/string.h"
#include <stdio.h>

namespace atl {

class fstream {
private:
  FILE *filePtr;

public:

  enum class open_mode {
    read,
    write
  };

  /* Constructor */
  fstream(const atl::string &filename, const open_mode mode) {
    switch (mode) {
      case open_mode::read:
        filePtr = fopen(filename.c_str(), "r");
      case open_mode::write:
        filePtr = fopen(filename.c_str(), "w");
    }
  }

  fstream(const fstream &rhs) = delete;
  fstream(fstream &&rhs) {
    filePtr = rhs.filePtr;
    rhs.filePtr = nullptr;
  }

  ~fstream() {
    if (filePtr)
      fclose(filePtr);
  }

  bool good() {
    if (filePtr)
      return true;
    else
      return false;
  }

  void write(const atl::string &contents) { fputs(contents.c_str(), filePtr); }

};

} // namespace atl
