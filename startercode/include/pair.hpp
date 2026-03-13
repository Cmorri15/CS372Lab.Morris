#pragma once
#include <compare>

template <typename Key, typename Value>
struct Pair {
    Key first;
    Value second;
    
    // Default constructor
    Pair() = default;
    
    // Parameterized constructor
    Pair(const Key& k, const Value& v) : first(k), second(v) {}
    
    // Spaceship operator - generates all comparison operators based on Key
    auto operator<=>(const Pair& other) const = default;
    
    // Equality operator (also generated, but explicitly declared for clarity)
    bool operator==(const Pair& other) const = default;
};