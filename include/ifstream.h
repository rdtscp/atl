#pragma once

#include "../include/string.h"

#ifndef ACC_COMPILER
#include <stdio.h>
#else
/* This will be hardcoded into the compiler im afraid :S */
FILE *fopen(const atl::string &, const atl::string &);
int getc(FILE *);
#endif

namespace atl {

class ifstream {

public:
  /* Constructor */
  ifstream(const atl::string &filename) : filename(filename) {
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
    FILE *file_p = filePtr;
    atl::string output;
    char currChar;
    currChar = '0';
    while (true) {
      int nextCharInt = getc(file_p);
      if (nextCharInt == -1) {
        output = output + '\0';
        break;
      }
      currChar = (char)nextCharInt;
      output = output + currChar;
    }
    return output;
  }

private:
  const atl::string &filename;
  FILE *filePtr;
};

} // namespace atl
