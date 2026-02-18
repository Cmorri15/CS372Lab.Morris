#pragma once
#include "list.hpp"

template <typename T>
class CircularList : public List<T> {
public:
    // Default constructor
    CircularList() : List<T>() {}
    
    // Constructor with initial data
    CircularList(T newData) : List<T>(newData) {}
    
    // Copy constructor
    CircularList(const CircularList& rhs) : List<T>(rhs) {}
    
    // Move constructor
    CircularList(CircularList&& rhs) noexcept : List<T>(std::move(rhs)) {}
    
    // Copy assignment
    CircularList& operator=(const CircularList& rhs) {
        List<T>::operator=(rhs);
        return *this;
    }
    
    // Move assignment
    CircularList& operator=(CircularList&& rhs) noexcept {
        List<T>::operator=(std::move(rhs));
        return *this;
    }
    
    // Circular traverse: starts at a given position and wraps around
    // Stops when it returns to the starting position
    void traverse(typename CircularList<T>::iterator start, std::function<void(T&)> doIt) {
        if (this->empty()) {
            return;  // Nothing to traverse
        }
        
        typename CircularList<T>::iterator current = start;
        typename CircularList<T>::iterator startPos = start;
        bool firstIteration = true;
        
        // Loop until we return to the starting position
        do {
            // Skip the first check since we haven't moved yet
            if (!firstIteration && current == startPos) {
                break;
            }
            firstIteration = false;
            
            doIt(*current);
            ++current;
            
            // Wrap around: if we hit the end, go back to the beginning
            if (current == this->end()) {
                current = this->begin();
            }
            
        } while (current != startPos);
    }
    
    // Regular traverse (non-circular) - inherits from List
    // This allows CircularList to still work like a regular List when needed
    using List<T>::traverse;
};