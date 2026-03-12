#include <iostream>
#include <string>
#include "list_smartptr.hpp"

using namespace std;

void printInt(int& x) {
    cout << x << " ";
}

int main() {
    cout << "Testing List with Smart Pointers\n";
    cout << "=================================\n\n";
    
    // Basic operations
    cout << "Creating list and adding elements\n";
    ListSmartPtr<int> list1;
    list1.push_back(10);
    list1.push_back(20);
    list1.push_back(30);
    list1.push_front(5);
    
    cout << "List: ";
    list1.traverse(printInt);
    cout << "\n";
    cout << "Size: " << list1.size() << "\n\n";
    
    // Test front and back
    cout << "Front: " << list1.front() << "\n";
    cout << "Back: " << list1.back() << "\n\n";
    
    // Test copy constructor
    cout << "Testing copy constructor\n";
    ListSmartPtr<int> list2(list1);
    cout << "List2 (copy): ";
    list2.traverse(printInt);
    cout << "\n\n";
    
    // Test copy assignment
    cout << "Testing copy assignment\n";
    ListSmartPtr<int> list3;
    list3 = list1;
    cout << "List3 (assigned): ";
    list3.traverse(printInt);
    cout << "\n\n";
    
    // Test move constructor
    cout << "Testing move constructor\n";
    ListSmartPtr<int> list4(std::move(list2));
    cout << "List4 (moved from list2): ";
    list4.traverse(printInt);
    cout << "\n";
    cout << "List2 size after move: " << list2.size() << "\n\n";
    
    // Test pop operations
    cout << "Testing pop operations\n";
    list1.pop_front();
    cout << "After pop_front: ";
    list1.traverse(printInt);
    cout << "\n";
    
    list1.pop_back();
    cout << "After pop_back: ";
    list1.traverse(printInt);
    cout << "\n\n";
    
    // Test iterators
    cout << "Testing iterators\n";
    ListSmartPtr<string> strList;
    strList.push_back("Hello");
    strList.push_back("World");
    strList.push_back("Smart");
    strList.push_back("Pointers");
    
    cout << "Using iterator: ";
    for (auto it = strList.begin(); it != strList.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\n";
    
    cout << "Using range-based for: ";
    for (auto& s : strList) {
        cout << s << " ";
    }
    cout << "\n\n";
    
    // Test insert and erase
    cout << "Testing insert and erase\n";
    auto it = strList.begin();
    ++it;
    strList.insert(it, "Beautiful");
    cout << "After insert: ";
    for (auto& s : strList) {
        cout << s << " ";
    }
    cout << "\n";
    
    it = strList.begin();
    ++it; ++it;
    strList.erase(it);
    cout << "After erase: ";
    for (auto& s : strList) {
        cout << s << " ";
    }
    cout << "\n\n";
    
    cout << "Smart pointer List test complete!\n";
    cout << "Note: No manual memory management needed - smart pointers handle it!\n";
    
    return 0;
}