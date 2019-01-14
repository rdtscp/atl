#pragma once

#ifndef ATL_VECTOR_H
#define ATL_VECTOR_H

namespace atl {

class string {

public:
  /* Constructor */
  string() {
    string_value = new char[1];
    *string_value = '\0';
  }

  /* Constructor */
  string(const char *string_literal) {
    const int string_length = charBufferLength(string_literal);
    string_value = new char[string_length + 1];
    char *string_value_ptr = string_value;
    for (int i = 0; i < string_length; ++i) {
      *string_value_ptr = *string_literal;
      ++string_value_ptr;
      ++string_literal;
    }
    *string_value_ptr = '\0';
  }

  /* Copy Constructor */
  string(const string &rhs) {
    if (&rhs == this)
      return;
    const int string_length = rhs.size();
    string_value = new char[string_length + 1];
    char *string_value_ptr = string_value;
    for (int i = 0; i < string_length; ++i) {
      *string_value_ptr = rhs[i];
      ++string_value_ptr;
    }
    *string_value_ptr = '\0';
  }

  /* Assignment Operator */
  string &operator=(const string &rhs) {
    if (&rhs == this)
      return *this;
    const int string_length = rhs.size();
    string_value = new char[string_length + 1];
    char *string_value_ptr = string_value;
    for (int i = 0; i < string_length; ++i) {
      *string_value_ptr = rhs[i];
      ++string_value_ptr;
    }
    *string_value_ptr = '\0';
    return *this;
  }

  /* Move Constructor */
  string(const string &&rhs) {}

  /* Move-Assignment Operator */
  string &operator=(const string &&rhs) { return *this; }

  /* Destructor */
  ~string() {}

  char &operator[](const int index) { return at(index); }

  const char &operator[](const int index) const { return at(index); }

  char &at(const int index) {
    return at(index);
    // if (index < charBufferLength(string_value)) {
    //   int currIdx = 0;
    //   char *string_value_ptr = string_value;
    //   while (*string_value_ptr != '\0') {
    //     if (currIdx == index)
    //       return *string_value_ptr;
    //     ++currIdx;
    //     ++string_value_ptr;
    //   }
    //   throw "atl::string::at Unexpected NULL Terminator";
    // }
    // throw "atl::string::at Out of Bounds Exception";
  }

  char &at(const int index) const {
    if (index < charBufferLength(string_value)) {
      int currIdx = 0;
      char *string_value_ptr = string_value;
      while (*string_value_ptr != '\0') {
        if (currIdx == index)
          return *string_value_ptr;
        ++currIdx;
        ++string_value_ptr;
      }
      throw "atl::string::at Unexpected NULL Terminator";
    }
    throw "atl::string::at Out of Bounds Exception";
  }

  char *c_str() { return c_str(); }

  char *c_str() const { return string_value; }

  int length() const { return size(); }

  int size() const { return charBufferLength(string_value); }

private:
  char *string_value;

  int charBufferLength(const char *buf) const {
    int length = 0;
    while (*buf != '\0') {
      ++length;
      ++buf;
    }
    return length;
  }
};

} // namespace atl

#endif