#pragma once
#include <iostream>

template <typename T, size_t N>
class Array {
public:
  // Constructor
  Array() {
    for (size_t i = 0; i < N; i++) {
      arr[i] = T();
    }
  }
  
  // Constructor with size parameter (for compatibility)
  Array(size_t size) {
    if (size != N) {
      std::cerr << "Array: size mismatch in constructor\n";
    }
    for (size_t i = 0; i < N; i++) {
      arr[i] = T();
    }
  }
  
  // Destructor (not much to do since arr is not dynamically allocated)
  ~Array() {}
  
  // Copy constructor
  Array(const Array& obj) {
    for (size_t i = 0; i < N; i++) {
      arr[i] = obj.arr[i];
    }
  }
  
  // Assignment operator
  Array& operator=(const Array& source) {
    if (this == &source) {
      return *this;
    }
    for (size_t i = 0; i < N; i++) {
      arr[i] = source.arr[i];
    }
    return *this;
  }
  
  // put: Place data at specified index
  void put(T data, size_t index) {
    if (index >= N) {
      std::cerr << "Array: index out of bounds on put\n";
      exit(1);
    }
    arr[index] = data;
  }
  
  // at: Get element at index
  T& at(size_t index) {
    if (index >= N) {
      std::cerr << "Array: index out of bounds on access\n";
      exit(1);
    }
    return arr[index];
  }
  
  // Const version of at
  const T& at(size_t index) const {
    if (index >= N) {
      std::cerr << "Array: index out of bounds on access\n";
      exit(1);
    }
    return arr[index];
  }
  
  // Array index operator
  T& operator[](size_t i) {
    if (i >= N) {
      std::cerr << "Array: index out of bounds\n";
      exit(1);
    }
    return arr[i];
  }
  
  // Const version of array index operator
  const T& operator[](size_t i) const {
    if (i >= N) {
      std::cerr << "Array: index out of bounds\n";
      exit(1);
    }
    return arr[i];
  }
  
  // size: Return the size of the array
  size_t size() const {
    return N;
  }
  
  // capacity: Return the capacity (same as size for Array)
  size_t capacity() const {
    return N;
  }
  
  // traverse: Print all elements
  void traverse() const {
    for (size_t i = 0; i < N; i++) {
      std::cout << arr[i] << std::endl;
    }
    std::cout << std::endl;
  }
  
  // Equality operator
  bool operator==(const Array& other) const {
    for (size_t i = 0; i < N; i++) {
      if (arr[i] != other.arr[i]) {
        return false;
      }
    }
    return true;
  }

private:
  T arr[N];  // Fixed-size array
};