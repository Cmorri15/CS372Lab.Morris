#pragma once
#include <iostream>
#include <vector>

template <typename Thing>
class ReceiptBag {
public:
    // Constructor - start with empty bag
    ReceiptBag() : nextReceipt(1) {}
    
    // Destructor
    ~ReceiptBag() {}
    
    // Insert a thing and return a unique receipt
    int insert(Thing aThing) {
        items.push_back(aThing);
        receipts.push_back(nextReceipt);
        return nextReceipt++;
    }
    
    // Remove the item with the given receipt and return it
    Thing& remove(int receipt) {
        // Find the receipt in the receipts vector
        for (size_t i = 0; i < receipts.size(); i++) {
            if (receipts[i] == receipt) {
                // Found it! Store the item to return
                static Thing removedItem;
                removedItem = items[i];
                
                // Remove from both parallel vectors
                items.erase(items.begin() + i);
                receipts.erase(receipts.begin() + i);
                
                return removedItem;
            }
        }
        
        // Receipt not found
        std::cerr << "ReceiptBag::remove: receipt " << receipt << " not found\n";
        exit(1);
    }
    
    // Return the number of items in the bag
    int size() const {
        return items.size();
    }
    
    // Return how many of a specific thing are in the bag
    int count(Thing aThing) const {
        int cnt = 0;
        for (size_t i = 0; i < items.size(); i++) {
            if (items[i] == aThing) {
                cnt++;
            }
        }
        return cnt;
    }
    
    // Check if bag is empty
    bool empty() const {
        return items.empty();
    }
    
    // Display all items with their receipts (for testing)
    void display() const {
        std::cout << "ReceiptBag contents:\n";
        for (size_t i = 0; i < items.size(); i++) {
            std::cout << "  Receipt #" << receipts[i] 
                      << ": " << items[i] << "\n";
        }
    }

private:
    std::vector<Thing> items;      // The actual items in the bag
    std::vector<int> receipts;     // Parallel vector of receipts
    int nextReceipt;               // Next receipt number to assign
};