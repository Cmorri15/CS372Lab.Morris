#pragma once
#include "vector.hpp"
#include <algorithm>

template <typename T>
class VectorCopy : public Vector<T> {
protected:
  void expand(int newCapacity) override {
    if (newCapacity > this->vCapacity) {
      T *temp = new T[newCapacity];
      // Use STL copy instead of for-loop
      std::copy(this->arr, this->arr + this->length, temp);
      delete[] this->arr;
      this->vCapacity = newCapacity;
      this->arr = temp;
    }
    else {
      std::cerr << "vector::expand: new capacity is less than or equal to current\n";
    }
  }
};