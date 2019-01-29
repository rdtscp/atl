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
  ~string() { delete[] string_value; }

  char &operator[](const int index) { return at(index); }

  const char &operator[](const int index) const { return at(index); }

  string operator+(char *const rhs) {
    // Calculate the new size.
    const int lhs_len = size();
    const int rhs_len = charBufferLength(rhs);
    const int string_length = lhs_len + rhs_len;

    // Allocate memory for the new string.
    char *new_string_value = new char[string_length + 1];
    char *new_string_value_ptr = new_string_value;

    // Copy the LHS.
    char *lhs_ptr = string_value;
    for (int i = 0; i < lhs_len; ++i) {
      *new_string_value_ptr = *lhs_ptr;
      ++lhs_ptr;
      ++new_string_value_ptr;
    }

    // Copy the RHS.
    char *rhs_ptr = rhs;
    for (int i = 0; i < rhs_len; ++i) {
      *new_string_value_ptr = *rhs_ptr;
      ++rhs_ptr;
      ++new_string_value_ptr;
    }

    // Null terminate.
    *new_string_value_ptr = '\0';

    string output(new_string_value);
    delete[] new_string_value;
    return output;
  }

  string operator+(const string &rhs) {
    // Calculate the new size.
    const int lhs_len = size();
    const int rhs_len = rhs.size();
    const int string_length = lhs_len + rhs_len;

    // Allocate memory for the new string.
    char *new_string_value = new char[string_length + 1];
    char *new_string_value_ptr = new_string_value;

    // Copy the LHS.
    char *lhs_ptr = string_value;
    for (int i = 0; i < lhs_len; ++i) {
      *new_string_value_ptr = *lhs_ptr;
      ++lhs_ptr;
      ++new_string_value_ptr;
    }

    // Copy the RHS.
    char *rhs_ptr = rhs.c_str();
    for (int i = 0; i < rhs_len; ++i) {
      *new_string_value_ptr = *rhs_ptr;
      ++rhs_ptr;
      ++new_string_value_ptr;
    }

    // Null terminate.
    *new_string_value_ptr = '\0';

    string output(new_string_value);
    delete[] new_string_value;
    return output;
  }

  char &at(const int index) {
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

  char *c_str() { return string_value; }

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