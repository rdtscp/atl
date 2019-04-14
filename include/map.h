#pragma once

#include "pair.h"
#include "vector.h"

namespace atl {

template <typename K, typename V> class map {

public:
  /* Constructor */
  map<K, V>() {}

  /* Copy Constructor */
  map<K, V>(const map<K, V> &rhs) {}

  /* Assignment Operator */
  map<K, V> &operator=(const map<K, V> &rhs) { elements = rhs.elements; }

  /* Destructor */
  ~map<K, V>() {}

  V &operator[](const K &key) {
    for (int idx = 0; idx < elements.size(); ++idx) {
      atl::pair<K, V> &curr_elem = elements[idx];
      if (curr_elem.first == key)
        return curr_elem.second;
    }
    insert(key, V());
    return find(key);
  }

  V at(const K &key) {
    for (int idx = 0; idx < elements.size(); ++idx) {
      atl::pair<K, V> &curr_elem = elements[idx];
      if (curr_elem.first == key)
        return curr_elem;
    }
    throw "atl::map::at Key does not exist.";
  }

  void insert(const K &key, const V &value) {
    atl::pair<K, V> new_elem(key, value);
    insert(new_elem);
  }

  void insert(const atl::pair<K, V> &new_elem) { elements.push_back(new_elem); }

  atl::pair<K, V> &find(const K &key) {
    for (int idx = 0; idx < elements.size(); ++idx) {
      atl::pair<K, V> &curr_elem = elements[idx];
      if (curr_elem.first == key)
        return curr_elem;
    }
    throw "atl::vector::at Out of Bounds Exception";
  }

  const atl::pair<K, V> &find(const K &key) const {
    for (int idx = 0; idx < elements.size(); ++idx) {
      atl::pair<K, V> &curr_elem = elements[idx];
      if (curr_elem.first == key)
        return curr_elem;
    }
    throw "atl::vector::at Out of Bounds Exception";
  }

private:
  atl::vector<atl::pair<K, V>> elements;
};

} // namespace atl
