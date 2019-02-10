#pragma once

#ifndef ATL_IFSTREAM_H
#define ATL_IFSTREAM_H

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
  ifstream(const atl::string &filename) : filename(filename) {}

  bool good() {
    if (FILE *file = fopen(filename.c_str(), "r")) {
      fclose(file);
      return true;
    } else {
      return false;
    }
  }

  atl::string readIntoString() {
    FILE *filePtr = fopen(filename.c_str(), "r");
    atl::string output;
    char currChar;
    currChar = '0';
    while (true) {
      int nextCharInt = getc(filePtr);
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
};

} // namespace atl

#endif