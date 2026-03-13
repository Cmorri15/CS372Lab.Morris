#pragma once
#include <stdexcept>
#include <memory>
#include "tree_smartptr.hpp"
#include "list_smartptr.hpp"
#include "pair.hpp"

template <typename Key, typename Value>
class Dictionary {
private:
    // Store pairs with shared pointers to allow mutation
    Tree<Pair<Key, std::shared_ptr<Value>>> data;
    
    // Custom comparator for Pairs - compares only by Key
    struct PairComparator {
        bool operator()(const Pair<Key, std::shared_ptr<Value>>& a, 
                       const Pair<Key, std::shared_ptr<Value>>& b) const {
            return a.first < b.first;
        }
    };

public:
    // Rule of Five
    Dictionary() = default;
    Dictionary(const Dictionary& other) = default;
    Dictionary& operator=(const Dictionary& other) = default;
    Dictionary(Dictionary&& other) noexcept = default;
    Dictionary& operator=(Dictionary&& other) noexcept = default;
    ~Dictionary() = default;
    
    // Access or insert element by key
    Value& operator[](const Key& key) {
        auto defaultVal = std::make_shared<Value>();
        Pair<Key, std::shared_ptr<Value>> searchPair(key, defaultVal);
        Tree<Pair<Key, std::shared_ptr<Value>>> foundTree;
        
        if (data.find(searchPair, foundTree, PairComparator())) {
            // Key exists - return reference to the value
            return *(foundTree.root().second);
        } else {
            // Key doesn't exist - insert new pair with default value
            data = data.insert(searchPair, PairComparator());
            data.find(searchPair, foundTree, PairComparator());
            return *(foundTree.root().second);
        }
    }
    
    // Access element by key (throws if not found)
    Value& at(const Key& key) {
        auto defaultVal = std::make_shared<Value>();
        Pair<Key, std::shared_ptr<Value>> searchPair(key, defaultVal);
        Tree<Pair<Key, std::shared_ptr<Value>>> foundTree;
        
        if (data.find(searchPair, foundTree, PairComparator())) {
            return *(foundTree.root().second);
        } else {
            throw std::out_of_range("Key not found in dictionary");
        }
    }
    
    const Value& at(const Key& key) const {
        auto defaultVal = std::make_shared<Value>();
        Pair<Key, std::shared_ptr<Value>> searchPair(key, defaultVal);
        Tree<Pair<Key, std::shared_ptr<Value>>> foundTree;
        
        if (data.find(searchPair, foundTree, PairComparator())) {
            return *(foundTree.root().second);
        } else {
            throw std::out_of_range("Key not found in dictionary");
        }
    }
    
    // Insert key-value pair
    void insert(const Key& key, const Value& value) {
        auto valPtr = std::make_shared<Value>(value);
        Pair<Key, std::shared_ptr<Value>> newPair(key, valPtr);
        data = data.insert(newPair, PairComparator());
    }
    
    // Remove key-value pair by key
    void erase(const Key& key) {
        // Our immutable tree doesn't have delete
        // Would need to rebuild tree without this key
        throw std::runtime_error("Erase not yet implemented for immutable tree");
    }
    
    // Clear all elements
    void clear() {
        data = Tree<Pair<Key, std::shared_ptr<Value>>>();
    }
    
    // Get all keys
    ListSmartPtr<Key> keys() const {
        ListSmartPtr<Key> keyList;
        data.inorder([&keyList](const Pair<Key, std::shared_ptr<Value>>& p) {
            keyList.push_back(p.first);
        });
        return keyList;
    }
    
    // Get all values
    ListSmartPtr<Value> values() const {
        ListSmartPtr<Value> valueList;
        data.inorder([&valueList](const Pair<Key, std::shared_ptr<Value>>& p) {
            valueList.push_back(*(p.second));
        });
        return valueList;
    }
    
    // Check if empty
    bool isEmpty() const {
        return data.isEmpty();
    }
    
    // Get size
    size_t size() const {
        return data.size();
    }
    
    // Check if key exists
    bool contains(const Key& key) const {
        auto defaultVal = std::make_shared<Value>();
        Pair<Key, std::shared_ptr<Value>> searchPair(key, defaultVal);
        return data.member(searchPair, PairComparator());
    }
};