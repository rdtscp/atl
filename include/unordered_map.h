#pragma once
#include "pair.h"
#include "vector.h"
#include <iostream>

namespace atl {

template <typename K, typename V>
class unordered_map {
private:
  atl::vector<atl::pair<K, V>> elements;

public:
  /* Constructor */
  unordered_map<K, V>() {}

  /* Copy Constructor */
  unordered_map<K, V>(const unordered_map<K, V> &rhs) {
    elements = rhs.elements;
  }

  /* Assignment Operator */
  unordered_map<K, V> &operator=(const unordered_map<K, V> &rhs) {
    elements = rhs.elements;
  }

  /* Destructor */
  ~unordered_map<K, V>() {}

  atl::vector<K> keys() const {
    atl::vector<K> output;
    const unsigned int num_keys = elements.size();
    for (unsigned int idx = 0; idx < num_keys; ++idx) {
      output.push_back(elements[idx].first);
    }
    return output;
  }

  bool operator==(const unordered_map<K, V> &rhs) const {
    // Check size.
    const unsigned int num_elems = elements.size();
    if (num_elems != rhs.elements.size())
      return false;

    for (unsigned int lhs_idx = 0; lhs_idx < num_elems; ++lhs_idx) {
      // Get the current element.
      const atl::pair<K, V> &lhs_curr_elem = elements[lhs_idx];

      // Search for it in the RHS.
      bool rhs_contains = false;
      for (unsigned int rhs_idx = 0; rhs_idx < num_elems; ++rhs_idx) {
        const atl::pair<K, V> &rhs_curr_elem = rhs.elements[rhs_idx];
        if (lhs_curr_elem == rhs_curr_elem) {
          rhs_contains = true;
          break;
        }
      }
      if (!rhs_contains)
        return false;
    }

    return true;
  }

  bool operator!=(const unordered_map<K, V> &rhs) const {
    return !(*this == rhs);
  }

  V &operator[](const K &key) {
    for (unsigned int idx = 0; idx < elements.size(); ++idx) {
      atl::pair<K, V> &curr_elem = elements[idx];
      if (curr_elem.first == key)
        return curr_elem.second;
    }
    insert(key, V());
    return find(key).second;
  }

  V at(const K &key) {
    for (unsigned int idx = 0; idx < elements.size(); ++idx) {
      atl::pair<K, V> &curr_elem = elements[idx];
      if (curr_elem.first == key)
        return curr_elem;
    }
    printf("%s\n", "atl::unordered_map::at Key does not exist.");
    throw;
  }

  void insert(const K &key, const V &value) {
    insert(atl::pair<K, V>(key, value));
  }

  void insert(const atl::pair<K, V> &new_elem) { insert_unique(new_elem); }

  atl::pair<K, V> &find(const K &key) {
    for (unsigned int idx = 0; idx < elements.size(); ++idx) {
      atl::pair<K, V> &curr_elem = elements[idx];
      if (curr_elem.first == key)
        return curr_elem;
    }
    printf("%s\n", "atl::unordered_map::at Out of Bounds Exception");
    throw;
  }

  const atl::pair<K, V> &find(const K &key) const {
    for (unsigned int idx = 0; idx < elements.size(); ++idx) {
      atl::pair<K, V> &curr_elem = elements[idx];
      if (curr_elem.first == key)
        return curr_elem;
    }
    printf("%s\n", "atl::unordered_map::at Out of Bounds Exception");
  }

private:
  void insert_unique(const atl::pair<K, V> &new_elem) {
    /* Check if this key exists already */
    const unsigned int num_elems = elements.size();
    for (unsigned int idx = 0; idx < num_elems; ++idx) {
      atl::pair<K, V> &curr_elem = elements[idx];
      if (curr_elem.first == new_elem.first) {
        curr_elem.second = new_elem.second;
        return;
      }
    }

    /* Key does not exist already */
    elements.push_back(new_elem);
  }
}; // namespace atl

} // namespace atl
