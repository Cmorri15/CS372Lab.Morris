#include <iostream>
#include <string>
#include "circularlist.hpp"

using namespace std;

void printInt(int& x) {
    cout << x << " ";
}

void printString(string& x) {
    cout << x << " ";
}

int main() {
    cout << "Testing CircularList Class\n";
    cout << "==========================\n\n";
    
    // Create a circular list with integers
    cout << "Creating circular list: 10, 20, 30, 40, 50\n";
    CircularList<int> clist;
    clist.push_back(10);
    clist.push_back(20);
    clist.push_back(30);
    clist.push_back(40);
    clist.push_back(50);
    
    cout << "Regular traverse (from beginning): ";
    clist.List<int>::traverse(printInt);
    cout << "\n\n";
    
    // Test circular traverse starting from beginning
    cout << "Circular traverse starting from beginning:\n";
    auto start = clist.begin();
    cout << "Starting at first element (10): ";
    clist.traverse(start, printInt);
    cout << "\n\n";
    
    // Test circular traverse starting from middle
    cout << "Circular traverse starting from middle:\n";
    auto middle = clist.begin();
    ++middle; ++middle;  // Move to third element (30)
    cout << "Starting at third element (30): ";
    clist.traverse(middle, printInt);
    cout << "\n";
    cout << "Expected order: 30 40 50 10 20\n\n";
    
    // Test circular traverse starting from end
    auto almostEnd = clist.begin();
    ++almostEnd; ++almostEnd; ++almostEnd; ++almostEnd;  // Move to last element (50)
    cout << "Starting at last element (50): ";
    clist.traverse(almostEnd, printInt);
    cout << "\n";
    cout << "Expected order: 50 10 20 30 40\n\n";
    
    // Test with strings
    cout << "Testing with strings...\n";
    CircularList<string> strList;
    strList.push_back("Monday");
    strList.push_back("Tuesday");
    strList.push_back("Wednesday");
    strList.push_back("Thursday");
    strList.push_back("Friday");
    
    cout << "Days of week: ";
    strList.List<string>::traverse(printString);
    cout << "\n\n";
    
    auto wednesday = strList.begin();
    ++wednesday; ++wednesday;  // Move to Wednesday
    cout << "Starting from Wednesday (circular): ";
    strList.traverse(wednesday, printString);
    cout << "\n";
    cout << "Expected: Wednesday Thursday Friday Monday Tuesday\n\n";
    
    // Test copy constructor
    cout << "Testing copy constructor...\n";
    CircularList<int> clist2(clist);
    cout << "Copied list (regular traverse): ";
    clist2.List<int>::traverse(printInt);
    cout << "\n\n";
    
    // Test that it still works as a regular list
    cout << "Testing that CircularList still works as regular List...\n";
    cout << "Front: " << clist.front() << "\n";
    cout << "Back: " << clist.back() << "\n";
    cout << "Size: " << clist.size() << "\n";
    
    clist.pop_front();
    cout << "After pop_front: ";
    clist.List<int>::traverse(printInt);
    cout << "\n\n";
    
    cout << "CircularList test complete!\n";
    
    return 0;
}