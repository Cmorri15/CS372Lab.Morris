#pragma once
#include <iostream>
#include <algorithm>

template <typename T>
class Vector {
public:
  Vector()  {
    arr = new T[1];
    vCapacity = 1;
    length = 0;
  }
  
  virtual ~Vector() {
    delete [] arr;
    arr = nullptr;
  }
  
  // Copy constructor
  Vector(const Vector& obj) {
    this->arr = new T[obj.vCapacity];
    this->vCapacity = obj.vCapacity;
    this->length = obj.length;
    for (int i = 0; i < obj.length; i++) {
      this->arr[i] = obj.arr[i];
    }
  }
  
  // Assignment operator
  Vector& operator=(const Vector& source) {
    if (this == &source) {
      return *this;
    }
    delete[] arr;
    arr = new T[source.vCapacity];
    vCapacity = source.vCapacity;
    length = source.length;
    for (int i = 0; i < source.length; i++) {
      arr[i] = source.arr[i];
    }
    return *this;
  }
  
  void push_back(T data) {
    if (length == vCapacity) {
      expand(2 * vCapacity);
    }
    arr[length] = data;
    length++;
  }
  
  void put(T data, int index) {
    if (index == vCapacity) {
      push_back(data);
    }
    else {
      arr[index] = data;
    }
  }
  
  T& at(int index) {
    if (index < 0 || index >= length) {
      std::cerr << "Vector: index out of bounds on access" << std::endl;
      exit(1);
    }
    return arr[index];
  }
  
  T& operator[](int i) {
    if ((i < 0) || (i >= length)) {
      std::cerr << std::endl << "Vector index out of bounds" << std::endl;
      exit(1);
    }
    return at(i);
  }
  
  int size() const {
    return length;
  }
  
  int capacity() const {
    return vCapacity;
  }
  
  void traverse() {
    for (int i = 0; i < length; i++) {
      std::cout << arr[i] << std::endl;
    }
    std::cout << std::endl;
  }
  
  bool operator==(const Vector& other) const {
    if (other.size() != length) {
      return false;
    }
    for (int i = 0; i < length; i++) {
      if (arr[i] != other.arr[i]) {
        return false;
      }
    }
    return true;
  }

protected:
  // Made virtual so derived classes can override
  virtual void expand(int newCapacity) {
    if (newCapacity > vCapacity) {
      T *temp = new T[newCapacity];
      for (int i = 0; i < length; i++) {
        temp[i] = arr[i];
      }
      delete[] arr;
      vCapacity = newCapacity;
      arr = temp;
    }
    else {
      std::cerr << "vector::expand: new capacity is less than or equal to current\n";
    }
  }
  
  T *arr;
  int vCapacity;
  int length;
};