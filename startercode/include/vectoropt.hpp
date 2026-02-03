#pragma once
#include "vector.hpp"

template <typename T>
class VectorOpt : public Vector<T> {
public:
  VectorOpt() : Vector<T>() {
    // Start with capacity of 128
    delete[] this->arr;
    this->arr = new T[128];
    this->vCapacity = 128;
    this->length = 0;
  }

protected:
  void expand(int newCapacity) override {
    // Increase by factor of 4 instead of 2
    int actualNewCapacity = this->vCapacity * 4;
    if (actualNewCapacity > this->vCapacity) {
      T *temp = new T[actualNewCapacity];
      for (int i = 0; i < this->length; i++) {
        temp[i] = this->arr[i];
      }
      delete[] this->arr;
      this->vCapacity = actualNewCapacity;
      this->arr = temp;
    }
    else {
      std::cerr << "vector::expand: new capacity is less than or equal to current\n";
    }
  }
};