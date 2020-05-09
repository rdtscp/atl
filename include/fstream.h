#pragma once

#include "../include/string.h"
#include <stdio.h>

namespace atl {

class fstream {
private:
  FILE *filePtr;

public:

  enum class OpenMode {
    READ,
    WRITE
  };

  /* Constructor */
  fstream(const atl::string &filename, const OpenMode mode) {
    switch (mode) {
      case OpenMode::READ:
        filePtr = fopen(filename.c_str(), "r");
      case OpenMode::WRITE:
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
