#pragma once

#include "shared_ptr.h"

namespace atl {

template <typename T>
class list {
private:
  struct list_node {
    list_node(const T &p_value) : value(p_value) {}

    T value;
    atl::shared_ptr<list_node> next;
  };

  atl::shared_ptr<list_node> head_node;

  list<T>(atl::shared_ptr<list_node> p_head) : head_node(p_head) {}
public:

  list<T>() : head_node(nullptr) {}

  list<T>(const list<T> &rhs) = default;
  list<T>(list<T> &&rhs) = default;
  list<T>& operator=(const list<T> &rhs) = default;
  list<T>& operator=(list<T> &&rhs) = default;

  const bool operator==(const list<T> &rhs) const {
    if (size() != rhs.size())
      return false;

    atl::shared_ptr<list_node> lhs_curr = head_node;
    atl::shared_ptr<list_node> rhs_curr = rhs.head_node;

    while (lhs_curr != nullptr && rhs_curr != nullptr) {
      if (lhs_curr->value != rhs_curr->value)
        return false;

      lhs_curr = lhs_curr->next;
      rhs_curr = rhs_curr->next;
    }

    return true;
  }

  const bool operator!=(const list<T> &rhs) const {
    return !(*this == rhs);
  }

  void push_back(const T& p_value) {
    const atl::shared_ptr<list_node> new_node(new list_node(p_value));
    if (head_node == nullptr) {
      head_node = new_node;
      return;
    }

    atl::shared_ptr<list_node> curr = head_node;
    while (curr->next)
      curr = curr->next;

    curr->next = new_node;
  }

  void push_front(const T& p_value) {
    const atl::shared_ptr<list_node> new_node(new list_node(p_value));
    if (head_node == nullptr) {
      head_node = new_node;
      return;
    }

    new_node->next = head_node;
    head_node = new_node;
  }

  const bool has_head() const {
    return head_node != nullptr;
  }

  const bool has_tail() const {
   if (head_node != nullptr)
      return head_node->next != nullptr;

    return false;
  }

  const T &head() const {
    if (head_node) {
      return head_node->value;
    }
    throw "atl::list::head No head exception."; 
  }

  const list<T> tail() const {
    if (head_node->next) {
      return list<T>(head_node->next);
    }
    throw "atl::list::tail No tail exception."; 
  }

  const unsigned int size() const {
    unsigned int output = 0;
    atl::shared_ptr<list_node> curr = head_node;
    while (curr) {
      ++output;
      curr = curr->next;
    }
    return output;
  }

};

} // namespace atl
