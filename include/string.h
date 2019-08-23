#pragma once

namespace atl {

class string {

public:
  typedef const char *const_iterator;
  typedef char *iterator;

  /* Constructor */
  string() : m_size(0u) {
    string_value = new char[1u];
    *string_value = '\0';
  }

  /* Constructor */
  string(const unsigned int count, const char c) : m_size(count) {
    string_value = new char[m_size + 1u];
    char *string_value_ptr = string_value;
    for (unsigned int idx = 0u; idx < m_size; ++idx) {
      *string_value_ptr = c;
      ++string_value_ptr;
    }
    *string_value_ptr = '\0';
  }

  /* Constructor */
  string(const char *string_literal) {
    m_size = charBufferLength(string_literal);
    string_value = new char[m_size + 1u];
    char *string_value_ptr = string_value;
    for (unsigned int idx = 0u; idx < m_size; ++idx) {
      *string_value_ptr = *string_literal;
      ++string_value_ptr;
      ++string_literal;
    }
    *string_value_ptr = '\0';
  }

  /* Copy Constructor */
  string(const atl::string &rhs) {
    if (&rhs == this)
      return;

    m_size = rhs.size();
    string_value = new char[m_size + 1u];
    char *string_value_ptr = string_value;
    for (unsigned int idx = 0u; idx < m_size; ++idx) {
      *string_value_ptr = rhs[idx];
      ++string_value_ptr;
    }
    *string_value_ptr = '\0';
  }

  /* Assignment Operator */
  string &operator=(const atl::string &rhs) {
    if (&rhs == this)
      return *this;

    m_size = rhs.size();
    string_value = new char[m_size + 1u];
    char *string_value_ptr = string_value;
    for (unsigned int idx = 0u; idx < m_size; ++idx) {
      *string_value_ptr = rhs[idx];
      ++string_value_ptr;
    }
    *string_value_ptr = '\0';
    return *this;
  }

  /* Move Constructor */
  string(atl::string &&rhs)
      : m_size(rhs.m_size), string_value(rhs.string_value) {
    rhs.string_value = nullptr;
  }

  /* Move-Assignment Operator */
  string &operator=(atl::string &&rhs) {
    m_size = rhs.m_size;
    string_value = rhs.string_value;

    rhs.m_size = 0u;
    rhs.string_value = nullptr;
    return *this;
  }

  /* Destructor */
  ~string() { delete[] string_value; }

  char &operator[](const unsigned int index) { return this->at(index); }

  const char operator[](const unsigned int index) const {
    return this->at(index);
  }

  atl::string operator+(const char rhs) const {
    string output(*this);
    output += rhs;
    return output;
  }

  atl::string operator+(const char *rhs) const {
    string output(*this);
    output += rhs;
    return output;
  }

  atl::string operator+(const atl::string &rhs) const {
    string output(*this);
    output += rhs;
    return output;
  }

  atl::string &operator+=(const char rhs) {
    if (rhs == '\0')
      return *this;

    const unsigned int lhs_size = this->size();
    const unsigned int rhs_size = 1u;
    m_size = lhs_size + rhs_size;

    // Allocate memory for the new string.
    char *new_string_value = new char[m_size + 1u];
    char *new_string_value_ptr = new_string_value;

    // Copy the LHS.
    char *lhs_ptr = string_value;
    for (unsigned int idx = 0u; idx < lhs_size; ++idx) {
      *new_string_value_ptr = *lhs_ptr;
      ++lhs_ptr;
      ++new_string_value_ptr;
    }

    *new_string_value_ptr = rhs;
    ++new_string_value_ptr;

    // Null terminate.
    *new_string_value_ptr = '\0';

    delete[] string_value;
    string_value = new_string_value;
    return *this;
  }

  atl::string &operator+=(const char *rhs) {
    const unsigned int lhs_size = this->size();
    const unsigned int rhs_size = charBufferLength(rhs);
    m_size = lhs_size + rhs_size;

    // Allocate memory for the new string.
    char *new_string_value = new char[m_size + 1u];
    char *new_string_value_ptr = new_string_value;

    // Copy the LHS.
    const char *lhs_ptr = string_value;
    for (unsigned int idx = 0u; idx < lhs_size; ++idx) {
      *new_string_value_ptr = *lhs_ptr;
      ++lhs_ptr;
      ++new_string_value_ptr;
    }

    // Copy the RHS.
    const char *rhs_ptr = rhs;
    for (unsigned int idx = 0u; idx < rhs_size; ++idx) {
      *new_string_value_ptr = *rhs_ptr;
      ++rhs_ptr;
      ++new_string_value_ptr;
    }

    // Null terminate.
    *new_string_value_ptr = '\0';

    delete[] string_value;
    string_value = new_string_value;
    return *this;
  }

  atl::string &operator+=(const atl::string &rhs) {
    const unsigned int lhs_size = this->size();
    const unsigned int rhs_size = rhs.size();
    m_size = lhs_size + rhs_size;

    // Allocate memory for the new string.
    char *new_string_value = new char[m_size + 1u];
    char *new_string_value_ptr = new_string_value;

    // Copy the LHS.
    const char *lhs_ptr = string_value;
    for (unsigned int idx = 0u; idx < lhs_size; ++idx) {
      *new_string_value_ptr = *lhs_ptr;
      ++lhs_ptr;
      ++new_string_value_ptr;
    }

    // Copy the RHS.
    for (unsigned int idx = 0u; idx < rhs_size; ++idx) {
      *new_string_value_ptr = rhs[idx];
      ++new_string_value_ptr;
    }

    // Null terminate.
    *new_string_value_ptr = '\0';

    delete[] string_value;
    string_value = new_string_value;
    return *this;
  }

  bool operator<(const char *rhs) const { return *this < atl::string(rhs); }

  bool operator>(const char *rhs) const { return *this > atl::string(rhs); }

  bool operator<=(const char *rhs) const { return *this <= atl::string(rhs); }

  bool operator>=(const char *rhs) const { return *this >= atl::string(rhs); }

  bool operator<(const atl::string &rhs) const {
    const unsigned int lhs_size = this->size();
    const unsigned int rhs_size = rhs.size();
    if (lhs_size < rhs_size)
      return true;
    if (lhs_size > rhs_size)
      return false;

    char currLhs;
    char currRhs;
    for (unsigned int idx = 0u; idx < rhs_size; ++idx) {
      currLhs = this->at(idx);
      currRhs = rhs[idx];
      if (static_cast<int>(currLhs) < static_cast<int>(currRhs)) {
        return true;
      }
    }
    return false;
  }

  bool operator>(const atl::string &rhs) const {
    const unsigned int lhs_size = this->size();
    const unsigned int rhs_size = rhs.size();
    if (lhs_size < rhs_size)
      return false;
    if (lhs_size > rhs_size)
      return true;

    char currLhs;
    char currRhs;
    for (unsigned int idx = 0u; idx < rhs_size; ++idx) {
      currLhs = this->at(idx);
      currRhs = rhs[idx];
      if (static_cast<int>(currLhs) > static_cast<int>(currRhs)) {
        return true;
      }
    }
    return false;
  }

  bool operator<=(const atl::string &rhs) const {
    const unsigned int lhs_size = this->size();
    const unsigned int rhs_size = rhs.size();
    if (lhs_size < rhs_size)
      return true;
    if (lhs_size > rhs_size)
      return false;

    char currLhs;
    char currRhs;
    for (unsigned int idx = 0u; idx < rhs_size; ++idx) {
      currLhs = this->at(idx);
      currRhs = rhs[idx];
      if (static_cast<int>(currLhs) > static_cast<int>(currRhs)) {
        return false;
      }
    }
    return true;
  }

  bool operator>=(const atl::string &rhs) const {
    const unsigned int lhs_size = this->size();
    const unsigned int rhs_size = rhs.size();
    if (lhs_size < rhs_size)
      return false;
    if (lhs_size > rhs_size)
      return true;

    char currLhs;
    char currRhs;
    for (unsigned int idx = 0u; idx < rhs_size; ++idx) {
      currLhs = this->at(idx);
      currRhs = rhs[idx];
      if (static_cast<int>(currLhs) < static_cast<int>(currRhs)) {
        return false;
      }
    }
    return true;
  }

  bool operator==(const atl::string &rhs) const {
    if (this->length() != rhs.length())
      return false;
    const unsigned int str_len = this->length();
    char lhsChar;
    char rhsChar;
    for (unsigned int charIdx = 0u; charIdx < str_len; ++charIdx) {
      lhsChar = this->at(charIdx);
      rhsChar = rhs.at(charIdx);
      if (lhsChar != rhsChar)
        return false;
    }
    return true;
  }

  bool operator==(const char *rhs) const {
    if (this->length() != charBufferLength(rhs))
      return false;
    const unsigned int str_len = this->length();
    char lhsChar;
    char rhsChar;
    for (unsigned int charIdx = 0u; charIdx < str_len; ++charIdx) {
      lhsChar = this->at(charIdx);
      rhsChar = rhs[charIdx];
      if (lhsChar != rhsChar)
        return false;
    }
    return true;
  }

  bool operator!=(const atl::string &rhs) const { return !(*this == rhs); }

  bool operator!=(const char *rhs) const { return !(*this == rhs); }

  char &at(const unsigned int index) {
    if (index < this->size()) {
      return string_value[index];
    }
    printf("%s\n", "atl::string::at Out of Bounds Exception");
    throw;
  }

  const char &at(const unsigned int index) const {
    if (index < this->size()) {
      return string_value[index];
    }
    printf("%s\n", "atl::string::at Out of Bounds Exception");
    throw;
  }

  const_iterator begin() const { return &string_value[0u]; }

  const_iterator end() const {
    const unsigned int len = this->size();
    return &string_value[len];
  }

  char *c_str() { return string_value; }

  char *c_str() const { return string_value; }

  int find(const char searchChar) const {
    const unsigned int len = this->length();
    char currChar;
    for (unsigned int idx = 0u; idx < len; ++idx) {
      currChar = this->at(idx);
      if (currChar == searchChar) {
        return static_cast<int>(idx);
      }
    }
    return -1;
  }

  unsigned int length() const { return this->size(); }

  unsigned int size() const { return m_size; }

private:
  unsigned int m_size;
  char *string_value;

  static unsigned int charBufferLength(const char *buf) {
    unsigned int length = 0u;
    while (*buf != '\0') {
      ++length;
      ++buf;
    }
    return length;
  }
}; // namespace atl

static atl::string operator+(const char *lhs, const atl::string &rhs) {
  return atl::string(lhs) + rhs;
}

static bool isspace(const char c) {
  return (c == ' ' || c == '\n' || c == '\r' || c == '\t');
}

static bool isalpha(const char c) {
  return ((('a' <= c) && (c <= 'z')) || (('A' <= c) && (c <= 'Z')));
}

static bool isdigit(const char c) { return (c >= '0' && c <= '9'); }

/* https://www.geeksforgeeks.org/write-your-own-atoi/ */
static int stoi(const char *str) {
  int output = 0;              // Initialize result
  int sign = 1;                // Initialize sign as positive
  unsigned int start_idx = 0u; // Initialize index of first digit

  // If number is negative, then update sign
  if (str[0] == '-') {
    sign = -1;
    ++start_idx; // Also update index of first digit
  }

  // Iterate through all digits and update the result
  for (unsigned int idx = start_idx; str[idx] != '\0'; ++idx)
    output = output * 10 + static_cast<int>(str[idx]) - static_cast<int>('0');

  // Return result with sign
  return sign * output;
}

static int stoi(const atl::string &str) { return stoi(str.c_str()); }

/* https://www.geeksforgeeks.org/implement-itoa/ */
static atl::string to_string(int num) {
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
  atl::string reverseDigits;
  while (num != 0) {
    unsigned int rem = num % 10;
    const char next_char =
        (rem > 9u)
            ? static_cast<char>((rem - 10u) + static_cast<unsigned int>('a'))
            : static_cast<char>(rem + static_cast<unsigned int>('0'));
    reverseDigits += next_char;
    num = num / 10;
  }

  // If number is negative, append '-'
  if (isNegative)
    reverseDigits += '-';

  // Reverse the string
  atl::string output;
  for (int idx = static_cast<int>(reverseDigits.size()) - 1; idx >= 0; --idx) {
    const unsigned int index = static_cast<unsigned int>(idx);
    char currChar = reverseDigits[index];
    output += currChar;
  }

  return output;
}

} // namespace atl
