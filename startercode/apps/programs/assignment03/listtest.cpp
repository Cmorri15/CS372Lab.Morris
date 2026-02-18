#include <iostream>
#include <string>
#include "list.hpp"

using namespace std;

void printInt(int& x) {
    cout << x << " ";
}

int main() {
    cout << "Testing List Class\n";
    cout << "==================\n\n";
    
    // Test basic list operations
    cout << "Creating list and adding elements...\n";
    List<int> list1;
    list1.push_back(10);
    list1.push_back(20);
    list1.push_back(30);
    list1.push_front(5);
    
    cout << "List contents: ";
    list1.traverse(printInt);
    cout << "\n";
    cout << "Size: " << list1.size() << "\n\n";
    
    // Test front and back
    cout << "Front: " << list1.front() << "\n";
    cout << "Back: " << list1.back() << "\n\n";
    
    // Test copy constructor
    cout << "Testing copy constructor...\n";
    List<int> list2(list1);
    cout << "List2 (copy of list1): ";
    list2.traverse(printInt);
    cout << "\n\n";
    
    // Test copy assignment
    cout << "Testing copy assignment...\n";
    List<int> list3;
    list3 = list1;
    cout << "List3 (assigned from list1): ";
    list3.traverse(printInt);
    cout << "\n\n";
    
    // Test move constructor
    cout << "Testing move constructor...\n";
    List<int> list4(std::move(list2));
    cout << "List4 (moved from list2): ";
    list4.traverse(printInt);
    cout << "\n";
    cout << "List2 size after move: " << list2.size() << "\n\n";
    
    // Test move assignment
    cout << "Testing move assignment...\n";
    List<int> list5;
    list5 = std::move(list3);
    cout << "List5 (move assigned from list3): ";
    list5.traverse(printInt);
    cout << "\n";
    cout << "List3 size after move: " << list3.size() << "\n\n";
    
    // Test pop operations
    cout << "Testing pop operations on list1...\n";
    list1.pop_front();
    cout << "After pop_front: ";
    list1.traverse(printInt);
    cout << "\n";
    
    list1.pop_back();
    cout << "After pop_back: ";
    list1.traverse(printInt);
    cout << "\n\n";
    
    // Test iterators
    cout << "Testing iterators...\n";
    List<string> strList;
    strList.push_back("Hello");
    strList.push_back("World");
    strList.push_back("From");
    strList.push_back("List");
    
    cout << "Using iterator: ";
    for (auto it = strList.begin(); it != strList.end(); ++it) {
        cout << *it << " ";
    }
    cout << "\n";
    
    cout << "Using range-based for loop: ";
    for (auto& s : strList) {
        cout << s << " ";
    }
    cout << "\n\n";
    
    // Test insert and erase
    cout << "Testing insert and erase...\n";
    auto it = strList.begin();
    ++it; // Move to second position
    strList.insert(it, "Beautiful");
    cout << "After inserting 'Beautiful': ";
    for (auto& s : strList) {
        cout << s << " ";
    }
    cout << "\n";
    
    it = strList.begin();
    ++it; ++it; // Move to third position
    strList.erase(it);
    cout << "After erasing third element: ";
    for (auto& s : strList) {
        cout << s << " ";
    }
    cout << "\n\n";
    
    cout << "List class test complete!\n";
    
    return 0;
}