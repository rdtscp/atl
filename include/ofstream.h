#pragma once

#include "../include/string.h"

/* This will be hardcoded into the compiler im afraid :S */
FILE *fopen(const atl::string &, const atl::string &);
int fputs(const char *s, FILE *fp);

namespace atl {

class ofstream {

public:
  /* Constructor */
  ofstream(const atl::string &filename) {
    filePtr = fopen(filename.c_str(), "w");
  }

  ~ofstream() { fclose(filePtr); }

  bool good() {
    if (filePtr)
      return true;
    else
      return false;
  }

  void write(const atl::string &contents) { fputs(contents.c_str(), filePtr); }

private:
  FILE *filePtr;
};

} // namespace atl
