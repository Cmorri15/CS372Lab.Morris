#include <iostream>
#include <string>
#include "dictionary.hpp"

using namespace std;

int main() {
    cout << "Testing Dictionary Class\n";
    cout << "========================\n\n";
    
    // Create a dictionary
    Dictionary<string, int> ages;
    
    cout << "Inserting key-value pairs:\n";
    ages.insert("Alice", 30);
    ages.insert("Bob", 25);
    ages.insert("Charlie", 35);
    ages.insert("Diana", 28);
    
    cout << "Dictionary size: " << ages.size() << "\n";
    cout << "Is empty? " << (ages.isEmpty() ? "yes" : "no") << "\n\n";
    
    // Test at() method
    cout << "Testing at() method:\n";
    cout << "Alice's age: " << ages.at("Alice") << "\n";
    cout << "Bob's age: " << ages.at("Bob") << "\n\n";
    
    // Test operator[]
    cout << "Testing operator[]:\n";
    cout << "Charlie's age: " << ages["Charlie"] << "\n";
    cout << "Setting Eve's age to 32...\n";
    ages["Eve"] = 32;
    cout << "Eve's age: " << ages["Eve"] << "\n";
    cout << "Dictionary size after adding Eve: " << ages.size() << "\n\n";
    
    // Test contains
    cout << "Testing contains:\n";
    cout << "Contains 'Alice'? " << (ages.contains("Alice") ? "yes" : "no") << "\n";
    cout << "Contains 'Frank'? " << (ages.contains("Frank") ? "yes" : "no") << "\n\n";
    
    // Get all keys
    cout << "All keys (in sorted order):\n";
    auto keyList = ages.keys();
    for (auto it = keyList.begin(); it != keyList.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\n\n";
    
    // Get all values
    cout << "All values (corresponding to sorted keys):\n";
    auto valueList = ages.values();
    for (auto it = valueList.begin(); it != valueList.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\n\n";
    
    // Test with different types
    cout << "Testing with int keys and string values:\n";
    Dictionary<int, string> names;
    names.insert(101, "Alice");
    names.insert(102, "Bob");
    names.insert(103, "Charlie");
    
    cout << "Student 101: " << names.at(101) << "\n";
    cout << "Student 102: " << names[102] << "\n";
    names[104] = "Diana";
    cout << "Added student 104: " << names[104] << "\n\n";
    
    // Test clear
    cout << "Testing clear:\n";
    cout << "Size before clear: " << names.size() << "\n";
    names.clear();
    cout << "Size after clear: " << names.size() << "\n";
    cout << "Is empty? " << (names.isEmpty() ? "yes" : "no") << "\n\n";
    
    // Test exception handling
    cout << "Testing exception handling:\n";
    try {
        int age = ages.at("NonExistent");
        cout << "Age: " << age << "\n";
    } catch (const out_of_range& e) {
        cout << "Caught exception: " << e.what() << "\n";
    }
    
    cout << "\nDictionary test complete!\n";
    
    return 0;
}