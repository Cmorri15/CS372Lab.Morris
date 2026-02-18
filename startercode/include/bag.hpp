#pragma once
#include "list.hpp"

template <typename Thing>
class Bag {
private:
    List<Thing> items;  // Using List as backing store
    
public:
    // Constructor - create empty bag
    Bag() {}
    
    // Destructor
    ~Bag() {}
    
    // Copy constructor
    Bag(const Bag& other) : items(other.items) {}
    
    // Move constructor
    Bag(Bag&& other) noexcept : items(std::move(other.items)) {}
    
    // Copy assignment operator
    Bag& operator=(const Bag& other) {
        if (this != &other) {
            items = other.items;
        }
        return *this;
    }
    
    // Move assignment operator
    Bag& operator=(Bag&& other) noexcept {
        if (this != &other) {
            items = std::move(other.items);
        }
        return *this;
    }
    
    // Insert a thing into the bag
    void insert(Thing aThing) {
        items.push_back(aThing);
    }
    
    // Remove and return an item from the bag
    // Since it's a bag, order doesn't matter - remove from the back
    Thing pop() {
        if (empty()) {
            std::cerr << "Bag::pop(): Attempt to pop from empty bag\n";
            exit(1);
        }
        Thing item = items.back();
        items.pop_back();
        return item;
    }
    
    // Return the number of items in the bag
    int size() const {
        return items.size();
    }
    
    // Count how many of a specific thing are in the bag
    int count(Thing aThing) const {
        int cnt = 0;
        for (auto it = items.cbegin(); it != items.cend(); ++it) {
            if (*it == aThing) {
                cnt++;
            }
        }
        return cnt;
    }
    
    // Check if bag is empty
    bool empty() const {
        return items.empty();
    }
};