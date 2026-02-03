#include <iostream>
#include "array.hpp"

int main() {
    std::cout << "Testing Array Class\n";
    std::cout << "===================\n\n";
    
    // Create an Array of 10 integers
    Array<int, 10> arr1;
    
    std::cout << "Array size: " << arr1.size() << "\n";
    std::cout << "Array capacity: " << arr1.capacity() << "\n\n";
    
    // Fill the array with values
    std::cout << "Filling array with values 0-9...\n";
    for (size_t i = 0; i < arr1.size(); i++) {
        arr1.put(i * 10, i);
    }
    
    // Display using at()
    std::cout << "Values using at():\n";
    for (size_t i = 0; i < arr1.size(); i++) {
        std::cout << "arr1.at(" << i << ") = " << arr1.at(i) << "\n";
    }
    std::cout << "\n";
    
    // Display using operator[]
    std::cout << "Values using operator[]:\n";
    for (size_t i = 0; i < arr1.size(); i++) {
        std::cout << "arr1[" << i << "] = " << arr1[i] << "\n";
    }
    std::cout << "\n";
    
    // Test traverse
    std::cout << "Using traverse():\n";
    arr1.traverse();
    
    // Test copy constructor
    std::cout << "Testing copy constructor...\n";
    Array<int, 10> arr2 = arr1;
    std::cout << "arr2 after copy:\n";
    arr2.traverse();
    
    // Test assignment operator
    std::cout << "Testing assignment operator...\n";
    Array<int, 10> arr3;
    arr3 = arr1;
    std::cout << "arr3 after assignment:\n";
    arr3.traverse();
    
    // Test equality
    std::cout << "Testing equality...\n";
    if (arr1 == arr2) {
        std::cout << "arr1 == arr2: true\n";
    } else {
        std::cout << "arr1 == arr2: false\n";
    }
    
    // Modify arr2 and test inequality
    arr2[0] = 999;
    if (arr1 == arr2) {
        std::cout << "arr1 == arr2 (after modification): true\n";
    } else {
        std::cout << "arr1 == arr2 (after modification): false\n";
    }
    
    std::cout << "\nArray class test complete!\n";
    
    return 0;
}