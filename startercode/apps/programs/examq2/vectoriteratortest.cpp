#include <iostream>
#include <string>
#include "vectorwithiterators.hpp"

using namespace std;

int main() {
    cout << "Testing Vector with Iterators\n";
    cout << "==============================\n\n";
    
    // Create a vector with some integers
    cout << "Creating vector with values: 10, 20, 30, 40, 50\n";
    Vector<int> vec;
    vec.push_back(10);
    vec.push_back(20);
    vec.push_back(30);
    vec.push_back(40);
    vec.push_back(50);
    
    // Test iterator with dereference and increment
    cout << "\nUsing iterator with dereference (*) and increment (++):\n";
    cout << "Values: ";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\n\n";
    
    // Test range-based for loop (uses iterators behind the scenes)
    cout << "Using range-based for loop:\n";
    cout << "Values: ";
    for (auto& value : vec) {
        cout << value << " ";
    }
    cout << "\n\n";
    
    // Modify values through iterator
    cout << "Modifying values through iterator (multiply by 2):\n";
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        *it = *it * 2;
    }
    cout << "New values: ";
    for (auto& value : vec) {
        cout << value << " ";
    }
    cout << "\n\n";
    
    // Test const_iterator
    cout << "Using const_iterator:\n";
    cout << "Values: ";
    for (auto it = vec.cbegin(); it != vec.cend(); ++it) {
        cout << *it << " ";
    }
    cout << "\n\n";
    
    // Test with strings
    cout << "Testing with strings:\n";
    Vector<string> strVec;
    strVec.push_back("apple");
    strVec.push_back("banana");
    strVec.push_back("cherry");
    strVec.push_back("date");
    
    cout << "String vector: ";
    for (auto it = strVec.begin(); it != strVec.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\n\n";
    
    // Test iterator equality
    cout << "Testing iterator equality:\n";
    auto it1 = vec.begin();
    auto it2 = vec.begin();
    auto it3 = vec.end();
    
    cout << "it1 == it2? " << (it1 == it2 ? "true" : "false") << "\n";
    cout << "it1 != it3? " << (it1 != it3 ? "true" : "false") << "\n\n";
    
    // Test postfix increment
    cout << "Testing postfix increment:\n";
    auto it = vec.begin();
    cout << "First value: " << *it << "\n";
    it++;
    cout << "After it++: " << *it << "\n";
    ++it;
    cout << "After ++it: " << *it << "\n\n";
    
    // Manually iterate through vector
    cout << "Manual iteration from begin to end:\n";
    int position = 0;
    for (auto it = vec.begin(); it != vec.end(); ++it) {
        cout << "Position " << position++ << ": " << *it << "\n";
    }
    
    cout << "\nVector iterator test complete!\n";
    
    return 0;
}