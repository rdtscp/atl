#pragma once

namespace atl {

class shared_count {
public:
  shared_count(const int user_count, const int weak_count) : m_user_count(user_count), m_weak_count(weak_count) {}

  void decrement_shared() {
    --m_user_count;
  }

  void increment_shared() {
    ++m_user_count;
  }

  void decrement_weak() {
    --m_weak_count;
  }

  void increment_weak() {
    ++m_weak_count;
  }

  int user_count() const {
    return m_user_count;
  }

  int weak_count() const {
    return m_weak_count;
  }

private:
  int m_user_count;
  int m_weak_count;

};

} // namespace atl
