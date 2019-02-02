#pragma once

#ifndef ATL_STRING_H
#define ATL_STRING_H

namespace atl {

class string {

public:
  typedef const char *const_iterator;
  typedef char *iterator;
  enum { npos = -1 };

  /* Constructor */
  string() {
    string_value = new char[1];
    *string_value = '\0';
  }

  /* Constructor */
  string(const int count, const char c) {
    const int string_length = count;
    string_value = new char[string_length + 1];
    char *string_value_ptr = string_value;
    for (int i = 0; i < string_length; ++i) {
      *string_value_ptr = c;
      ++string_value_ptr;
    }
    *string_value_ptr = '\0';
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
  string(const string &&rhs) { *this = rhs; }

  /* Move-Assignment Operator */
  string &operator=(const string &&rhs) {
    *this = rhs;
    return *this;
  }

  /* Destructor */
  ~string() { delete[] string_value; }

  char &operator[](const int index) { return at(index); }

  const char &operator[](const int index) const { return at(index); }

  string operator+(const char rhs) {
    // Calculate the new size.
    const int lhs_len = size();
    const int rhs_len = 1;
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
    *new_string_value_ptr = rhs;
    ++new_string_value_ptr;

    // Null terminate.
    *new_string_value_ptr = '\0';

    string output(new_string_value);
    delete[] new_string_value;
    return output;
  }

  string operator+(const char *rhs) {
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
    const char *rhs_ptr = rhs;
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

  string operator+(const string &rhs) const {
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

  string &operator+=(const char rhs) {
    *this = *this + rhs;
    return *this;
  }

  string &operator+=(const char *rhs) {
    *this = *this + atl::string(rhs);
    return *this;
  }

  string &operator+=(const string &rhs) {
    *this = *this + rhs;
    return *this;
  }

  bool operator<(const char *rhs) const { return *this < string(rhs); }

  bool operator>(const char *rhs) const { return *this > string(rhs); }

  bool operator<=(const char *rhs) const { return *this <= string(rhs); }

  bool operator>=(const char *rhs) const { return *this >= string(rhs); }

  bool operator<(const string &rhs) const {
    const int lhsSize = this->size();
    const int rhsSize = rhs.size();
    if (lhsSize < rhsSize)
      return true;
    if (lhsSize > rhsSize)
      return false;

    char currLhs, currRhs;
    for (int idx = 0; idx < rhsSize; ++idx) {
      currLhs = this->at(idx);
      currRhs = rhs[idx];
      if ((int)currLhs < (int)currRhs) {
        return true;
      }
    }
    return false;
  }

  bool operator>(const string &rhs) const {
    const int lhsSize = this->size();
    const int rhsSize = rhs.size();
    if (lhsSize < rhsSize)
      return false;
    if (lhsSize > rhsSize)
      return true;

    char currLhs, currRhs;
    for (int idx = 0; idx < rhsSize; ++idx) {
      currLhs = this->at(idx);
      currRhs = rhs[idx];
      if ((int)currLhs > (int)currRhs) {
        return true;
      }
    }
    return false;
  }

  bool operator<=(const string &rhs) const {
    const int lhsSize = this->size();
    const int rhsSize = rhs.size();
    if (lhsSize < rhsSize)
      return true;
    if (lhsSize > rhsSize)
      return false;

    char currLhs, currRhs;
    for (int idx = 0; idx < rhsSize; ++idx) {
      currLhs = this->at(idx);
      currRhs = rhs[idx];
      if ((int)currLhs > (int)currRhs) {
        return false;
      }
    }
    return true;
  }

  bool operator>=(const string &rhs) const {
    const int lhsSize = this->size();
    const int rhsSize = rhs.size();
    if (lhsSize < rhsSize)
      return false;
    if (lhsSize > rhsSize)
      return true;

    char currLhs, currRhs;
    for (int idx = 0; idx < rhsSize; ++idx) {
      currLhs = this->at(idx);
      currRhs = rhs[idx];
      if ((int)currLhs < (int)currRhs) {
        return false;
      }
    }
    return true;
  }

  bool operator==(const string &rhs) const {
    if (length() != rhs.length())
      return false;
    const int str_len = length();
    char lhsChar, rhsChar;
    for (int charIdx = 0; charIdx < str_len; ++charIdx) {
      lhsChar = at(charIdx);
      rhsChar = rhs.at(charIdx);
      if (lhsChar != rhsChar)
        return false;
    }
    return true;
  }

  bool operator==(const char *rhs) const {
    if (length() != charBufferLength(rhs))
      return false;
    const int str_len = length();
    char lhsChar, rhsChar;
    for (int charIdx = 0; charIdx < str_len; ++charIdx) {
      lhsChar = at(charIdx);
      rhsChar = rhs[charIdx];
      if (lhsChar != rhsChar)
        return false;
    }
    return true;
  }

  bool operator!=(const string &rhs) const { return !(*this == rhs); }

  bool operator!=(const char *rhs) const { return !(*this == rhs); }

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

  const_iterator begin() const { return &string_value[0]; }

  const_iterator end() const {
    const int len = charBufferLength(string_value);
    return &string_value[len];
  }

  char *c_str() { return string_value; }

  char *c_str() const { return string_value; }

  int find(const char searchChar) const {
    const int len = length();
    char currChar;
    for (int idx = 0; idx < len; ++idx) {
      currChar = at(idx);
      if (currChar == searchChar) {
        return idx;
      }
    }
    return npos;
  }

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

static bool isspace(const char c) {
  return (c == ' ' || c == '\n' || c == '\r' || c == '\t');
}

static bool isalpha(const char c) {
  return ((('a' <= (c)) && ((c) <= 'z')) || (('A' <= (c)) && ((c) <= 'Z')));
}

static bool isdigit(const char c) { return (c >= (int)'0' && c <= (int)'9'); }

/* https://www.geeksforgeeks.org/implement-itoa/ */
static string to_string(int num) {
  int i = 0;
  bool isNegative = false;

  /* Handle 0 explicitely, otherwise empty string is printed for 0 */
  if (num == 0)
    return string("0");

  // In standard itoa(), negative numbers are handled only with
  // base 10. Otherwise numbers are considered unsigned.
  if (num < 0) {
    isNegative = true;
    num = -num;
  }

  // Process individual digits
  string reverseDigits;
  while (num != 0) {
    int rem = num % 10;
    reverseDigits += (rem > 9) ? (rem - 10) + 'a' : rem + '0';
    num = num / 10;
  }

  // If number is negative, append '-'
  if (isNegative)
    reverseDigits += '-';

  // Reverse the string
  string output;
  for (int idx = reverseDigits.size() - 1; idx >= 0; --idx) {
    char currChar = reverseDigits[idx];
    output += currChar;
  }

  return output;
}

} // namespace atl

#endif