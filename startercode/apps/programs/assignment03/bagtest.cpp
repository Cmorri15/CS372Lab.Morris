#include <iostream>
#include <string>
#include "bag.hpp"

using namespace std;

int main() {
    cout << "Testing Bag Class (with List backing store)\n";
    cout << "============================================\n\n";
    
    // Test basic bag operations
    cout << "Creating bag and adding items...\n";
    Bag<int> bag1;
    bag1.insert(10);
    bag1.insert(20);
    bag1.insert(30);
    bag1.insert(10);  // Duplicate
    
    cout << "Bag size: " << bag1.size() << "\n";
    cout << "Count of 10: " << bag1.count(10) << "\n";
    cout << "Count of 20: " << bag1.count(20) << "\n\n";
    
    // Test pop
    cout << "Popping items...\n";
    int item = bag1.pop();
    cout << "Popped: " << item << "\n";
    cout << "Bag size after pop: " << bag1.size() << "\n\n";
    
    // Test copy constructor
    cout << "Testing copy constructor...\n";
    Bag<int> bag2(bag1);
    cout << "Bag2 size (copy of bag1): " << bag2.size() << "\n";
    cout << "Bag2 count of 10: " << bag2.count(10) << "\n\n";
    
    // Test copy assignment
    cout << "Testing copy assignment...\n";
    Bag<int> bag3;
    bag3 = bag1;
    cout << "Bag3 size (assigned from bag1): " << bag3.size() << "\n\n";
    
    // Test move constructor
    cout << "Testing move constructor...\n";
    Bag<int> bag4(std::move(bag2));
    cout << "Bag4 size (moved from bag2): " << bag4.size() << "\n";
    cout << "Bag2 size after move: " << bag2.size() << "\n\n";
    
    // Test move assignment
    cout << "Testing move assignment...\n";
    Bag<int> bag5;
    bag5 = std::move(bag3);
    cout << "Bag5 size (move assigned from bag3): " << bag5.size() << "\n";
    cout << "Bag3 size after move: " << bag3.size() << "\n\n";
    
    // Test with strings
    cout << "Testing with strings...\n";
    Bag<string> strBag;
    strBag.insert("apple");
    strBag.insert("banana");
    strBag.insert("apple");
    strBag.insert("cherry");
    
    cout << "String bag size: " << strBag.size() << "\n";
    cout << "Count of 'apple': " << strBag.count("apple") << "\n";
    cout << "Count of 'banana': " << strBag.count("banana") << "\n\n";
    
    cout << "Bag class test complete!\n";
    
    return 0;
}