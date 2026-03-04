#include <iostream>
#include <string>
#include "lazylist.hpp"

using namespace std;

void printInt(int& x) {
    cout << x << " ";
}

int main() {
    cout << "Testing LazyList with Lazy Deletion\n";
    cout << "====================================\n\n";
    
    // Start with a simple list
    cout << "Creating list with values: 10, 20, 30, 40, 50\n";
    LazyList<int> list;
    list.push_back(10);
    list.push_back(20);
    list.push_back(30);
    list.push_back(40);
    list.push_back(50);
    
    cout << "List contents: ";
    list.traverse(printInt);
    cout << "\n";
    cout << "Active count: " << list.size() << "\n";
    cout << "Deleted count: " << list.getDeletedCount() << "\n\n";
    
    // Delete the first item
    cout << "Calling pop_front()\n";
    list.pop_front();
    cout << "List after deletion: ";
    list.traverse(printInt);
    cout << "\n";
    cout << "Active count: " << list.size() << "\n";
    cout << "Deleted count: " << list.getDeletedCount() << "\n";
    cout << "The deleted item is still in memory, just marked\n\n";
    
    // Delete another
    cout << "Calling pop_back()\n";
    list.pop_back();
    cout << "List: ";
    list.traverse(printInt);
    cout << "\n";
    cout << "Active count: " << list.size() << "\n";
    cout << "Deleted count: " << list.getDeletedCount() << "\n\n";
    
    // This should trigger the purge
    cout << "Deleting one more...\n";
    cout << "When deletedCount reaches activeCount, purge happens\n";
    list.pop_front();
    cout << "List: ";
    list.traverse(printInt);
    cout << "\n";
    cout << "Active count: " << list.size() << "\n";
    cout << "Deleted count: " << list.getDeletedCount() << "\n";
    cout << "Deleted count went back to 0 because we purged\n\n";
    
    // Check that front/back work correctly
    cout << "Testing front() and back():\n";
    cout << "Front: " << list.front() << "\n";
    cout << "Back: " << list.back() << "\n\n";
    
    // Try with more items
    cout << "Making a new list with 10 items\n";
    LazyList<int> list2;
    for (int i = 1; i <= 10; i++) {
        list2.push_back(i * 10);
    }
    
    cout << "List: ";
    list2.traverse(printInt);
    cout << "\n";
    cout << "Active: " << list2.size() << ", Deleted: " << list2.getDeletedCount() << "\n\n";
    
    // Delete half of them
    cout << "Deleting 5 items:\n";
    for (int i = 0; i < 5; i++) {
        list2.pop_front();
        cout << "  Deletion " << (i+1) << " - Active: " << list2.size() 
             << ", Deleted: " << list2.getDeletedCount() << "\n";
    }
    
    cout << "\nWhat's left: ";
    list2.traverse(printInt);
    cout << "\n";
    cout << "Active: " << list2.size() << ", Deleted: " << list2.getDeletedCount() << "\n";
    cout << "Purge happened when we hit the threshold\n\n";
    
    // See if copying works right
    cout << "Testing copy - should only get the active items:\n";
    LazyList<int> list3 = list2;
    cout << "Copy: ";
    list3.traverse(printInt);
    cout << "\n";
    cout << "Active: " << list3.size() << ", Deleted: " << list3.getDeletedCount() << "\n\n";
    
    cout << "Done testing\n";
    
    return 0;
}