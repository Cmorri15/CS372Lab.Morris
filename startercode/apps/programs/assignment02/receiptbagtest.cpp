#include <iostream>
#include <string>
#include "receiptbag.hpp"

int main() {
    std::cout << "Testing ReceiptBag Class\n";
    std::cout << "========================\n\n";
    
    // Create a ReceiptBag of integers
    ReceiptBag<int> intBag;
    
    std::cout << "Initial bag size: " << intBag.size() << "\n\n";
    
    // Insert some items and save receipts
    std::cout << "Inserting items...\n";
    int receipt1 = intBag.insert(100);
    std::cout << "Inserted 100, receipt: " << receipt1 << "\n";
    
    int receipt2 = intBag.insert(200);
    std::cout << "Inserted 200, receipt: " << receipt2 << "\n";
    
    int receipt3 = intBag.insert(300);
    std::cout << "Inserted 300, receipt: " << receipt3 << "\n";
    
    int receipt4 = intBag.insert(100);
    std::cout << "Inserted 100 (duplicate), receipt: " << receipt4 << "\n\n";
    
    std::cout << "Bag size after insertions: " << intBag.size() << "\n";
    std::cout << "Count of 100: " << intBag.count(100) << "\n\n";
    
    intBag.display();
    std::cout << "\n";
    
    std::cout << "Removing item with receipt " << receipt2 << "...\n";
    int removed = intBag.remove(receipt2);
    std::cout << "Removed value: " << removed << "\n\n";
    
    std::cout << "Bag size after removal: " << intBag.size() << "\n";
    intBag.display();
    std::cout << "\n";
    
    std::cout << "Removing item with receipt " << receipt4 << "...\n";
    removed = intBag.remove(receipt4);
    std::cout << "Removed value: " << removed << "\n\n";
    
    std::cout << "Bag size: " << intBag.size() << "\n";
    std::cout << "Count of 100: " << intBag.count(100) << "\n";
    intBag.display();
    std::cout << "\n";
    
    std::cout << "Testing with strings...\n";
    ReceiptBag<std::string> stringBag;
    
    int r1 = stringBag.insert("apple");
    int r2 = stringBag.insert("banana");
    int r3 = stringBag.insert("cherry");
    
    std::cout << "String bag contents:\n";
    stringBag.display();
    std::cout << "\n";
    
    std::cout << "Removing 'banana' with receipt " << r2 << "...\n";
    std::string removedStr = stringBag.remove(r2);
    std::cout << "Removed: " << removedStr << "\n\n";
    
    stringBag.display();
    
    std::cout << "\nReceiptBag class test complete!\n";
    
    return 0;
}