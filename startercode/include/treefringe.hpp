#pragma once
#include <queue>
#include "tree_smartptr.hpp"
#include "list_smartptr.hpp"

// Get the fringe of a tree (leaves in level order, left to right)
template<typename T>
ListSmartPtr<T>& getFringe(const Tree<T>& tree) {
    static ListSmartPtr<T> fringe;
    fringe = ListSmartPtr<T>();  // Clear previous result
    
    if (tree.isEmpty()) {
        return fringe;
    }
    
    // Level order traversal using a queue
    std::queue<Tree<T>> q;
    q.push(tree);
    
    while (!q.empty()) {
        Tree<T> current = q.front();
        q.pop();
        
        // If it's a leaf, add to fringe
        if (current.isLeaf()) {
            fringe.push_back(current.root());
        } else {
            // Not a leaf, add children to queue
            if (!current.left().isEmpty()) {
                q.push(current.left());
            }
            if (!current.right().isEmpty()) {
                q.push(current.right());
            }
        }
    }
    
    return fringe;
}

// Check if two trees have the same fringe
template<typename T>
void collectFringe(const Tree<T>& tree, ListSmartPtr<T>& fringe) {
    if (tree.isEmpty()) return;

    if (tree.isLeaf()) {
        fringe.push_back(tree.root());
        return;
    }

    collectFringe(tree.left(), fringe);
    collectFringe(tree.right(), fringe);
}

template<typename T>
ListSmartPtr<T> getFringe(const Tree<T>& tree) {
    ListSmartPtr<T> fringe;
    collectFringe(tree, fringe);
    return fringe;
}