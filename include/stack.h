#pragma once

#include "vector.h"

namespace atl {

template <typename T> class stack : public vector<T> {
public:
  T &top() { return vector<T>::at(vector<T>::size() - 1); }

  const T &top() const { return vector<T>::at(vector<T>::size() - 1); }
};

// template <typename T> class stack {

// public:
//   /* Default Constructor */
//   stack<T>() {}

//   /* Initializer-List Constructor */
//   stack<T>(std::initializer_list<T> list) {
//     reserve(list.size());
//     for (const T &item : list)
//       push_back(item);
//   }

//   /* Size Constructor */
//   stack<T>(const int size) {
//     allocate(size);
//     for (int idx = 0; idx < capacity(); ++idx)
//       push_back(T());
//   }

//   /* Copy Constructor */
//   stack<T>(const stack<T> &rhs) {
//     if (this == &rhs)
//       return;

//     reserve(rhs.capacity());
//     for (int idx = 0; idx < rhs.size(); ++idx)
//       push_back(rhs.at(idx));
//   }

//   /* Assignment Operator */
//   stack<T> &operator=(const stack<T> &rhs) {
//     if (this == &rhs)
//       return *this;

//     deallocate();
//     reserve(rhs.capacity());
//     for (int idx = 0; idx < rhs.size(); ++idx)
//       push_back(rhs.at(idx));
//     return *this;
//   }

//   /* Move Constructor */
//   stack<T>(const stack<T> &&rhs) {
//     if (this == &rhs)
//       return;

//     deallocate();
//     reserve(rhs.capacity());
//     for (int idx = 0; idx < rhs.size(); ++idx)
//       push_back(rhs.at(idx));
//   }

//   /* Move-Assignment Operator */
//   stack<T> &operator=(const stack<T> &&rhs) {
//     if (this == &rhs)
//       return *this;

//     deallocate();
//     reserve(rhs.capacity());
//     for (int idx = 0; idx < rhs.size(); ++idx)
//       push_back(rhs.at(idx));

//     return *this;
//   }

//   /* Destructor */
//   ~stack<T>() { deallocate(); }

//   T &operator[](const int index) { return at(index); }

//   const T &operator[](const int index) const { return at(index); }

//   T &at(const int index) {
//     if (index < elements_size) {
//       return elements[index];
//     }
//     throw "atl::stack::at Out of Bounds Exception";
//   }

//   T &at(const int index) const {
//     if (index < elements_size) {
//       return elements[index];
//     }
//     throw "atl::stack::at Out of Bounds Exception";
//   }

//   int capacity() const { return elements_size; }

//   void clear() { deallocate(); }

//   T erase(const int eraseIndex) {
//     if (eraseIndex > size())
//       throw "atl::stack::erase Out of Bounds Exception";
//     const T output = at(eraseIndex);
//     const int vect_size = size();
//     const int vect_capacity = capacity();

//     /* Backup existing elements. */
//     T *tempBuffer = new T[vect_size];
//     for (int idx = 0; idx < vect_size; ++idx)
//       tempBuffer[idx] = elements[idx];

//     deallocate();
//     allocate(vect_capacity - 1);
//     for (int idx = 0; idx < vect_size; ++idx)
//       if (idx != eraseIndex)
//         push_back(tempBuffer[idx]);

//     return output;
//   }

//   void push(const T &elem) {
//     if (capacity() == 0)
//       reserve(1);

//     if (size() >= capacity())
//       reserve(1 + capacity());

//     elements[elements_used] = elem;
//     ++elements_used;
//   }

//   T pop() {
//     --elements_used;
//     return erase(elements_used);
//   }

//   T &top() { return at(size() - 1); }

//   void reserve(const int reserveSize) {
//     /* Already have requested space. */
//     if (reserveSize <= elements_size)
//       return;

//     /* Buffer not allocated. */
//     else if (elements_size <= 0) {
//       elements_size = reserveSize;
//       elements = new T[elements_size];
//     }

//     /* Buffer already allocated. */
//     else if (elements_size > 0) {
//       /* Backup existing elements. */
//       const int tempBufferLen = elements_size;
//       T *tempBuffer = new T[tempBufferLen];
//       for (int idx = 0; idx < elements_size; ++idx)
//         tempBuffer[idx] = elements[idx];

//       deallocate();
//       elements_size = reserveSize;
//       elements = new T[elements_size];
//       for (int idx = 0; idx < tempBufferLen; ++idx)
//         push_back(tempBuffer[idx]);
//     }
//   }

//   int size() const { return elements_used; }

// private:
//   int elements_size = 0;
//   int elements_used = 0;
//   T *elements;

//   void allocate(const int num_elems) {
//     elements_size = num_elems;
//     elements = new T[elements_size];
//   }

//   void deallocate() {
//     if (elements_size > 0)
//       delete[] elements;
//     elements_size = 0;
//     elements_used = 0;
//   }

//   /* Extend the size of elements[] by num_elems. */
//   void extend(const int num_elems) {
//     const int new_capacity = capacity() + num_elems;
//     reserve(new_capacity);
//   }

//   void print() const {
//     for (int idx = 0; idx < size(); ++idx)
//       std::cout << at(idx) << std::endl;
//   }
// };

} // namespace atl
