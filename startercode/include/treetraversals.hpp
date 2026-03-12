#pragma once
#include <queue>
#include "tree_smartptr.hpp"

// Level traversal: visits nodes level by level (breadth-first)
// Uses a queue to track which nodes to visit next
template<typename T, typename Func>
void levelTraversal(const Tree<T>& tree, Func visit) {
    if (tree.isEmpty()) {
        return;
    }
    
    // Use a queue to keep track of trees to visit
    std::queue<Tree<T>> nodesToVisit;
    nodesToVisit.push(tree);
    
    while (!nodesToVisit.empty()) {
        // Get the front tree from the queue
        Tree<T> current = nodesToVisit.front();
        nodesToVisit.pop();
        
        // Visit the root of this tree
        visit(current.root());
        
        // Add left child to queue if it exists
        if (!current.left().isEmpty()) {
            nodesToVisit.push(current.left());
        }
        
        // Add right child to queue if it exists
        if (!current.right().isEmpty()) {
            nodesToVisit.push(current.right());
        }
    }
}

// Prune function: returns a new tree without any leaf nodes
// A leaf is a node with no children
template<typename T>
Tree<T> prune(const Tree<T>& tree) {
    // Base case: empty tree
    if (tree.isEmpty()) {
        return Tree<T>();
    }
    
    // Check if this is a leaf node (no children)
    bool leftEmpty = tree.left().isEmpty();
    bool rightEmpty = tree.right().isEmpty();
    
    if (leftEmpty && rightEmpty) {
        // This is a leaf - prune it by returning empty tree
        return Tree<T>();
    }
    
    // Not a leaf - recursively prune left and right subtrees
    Tree<T> prunedLeft = prune(tree.left());
    Tree<T> prunedRight = prune(tree.right());
    
    // Rebuild tree with pruned children
    return Tree<T>(prunedLeft, tree.root(), prunedRight);
}