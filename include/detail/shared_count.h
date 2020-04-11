#pragma once

namespace atl {

class shared_count {
public:
  shared_count(const int user_count) : m_user_count(user_count) {}

  void decrement_shared() {
    --m_user_count;
  }

  void increment_shared() {
    ++m_user_count;
;
  }

  int use_count() const {
    return m_user_count;
;
  }

private:
  int m_user_count;

};

} // namespace atl
