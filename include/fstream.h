#pragma once

#include "../include/string.h"
#include <stdio.h>

namespace atl {

class fstream {
public:
  enum class open_mode {
    read,
    write
  };

private:
  FILE *filePtr;
  open_mode m_mode;

public:

  /* Constructor */
  fstream(const atl::string &filename, const open_mode mode) : m_mode(mode) {
    switch (m_mode) {
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

  atl::string read() const {
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

  void write(const atl::string &contents) {
    if (m_mode != open_mode::write) {
      throw "Cannot write to a read handle";
    }
    fputs(contents.c_str(), filePtr);
  }

};

} // namespace atl
