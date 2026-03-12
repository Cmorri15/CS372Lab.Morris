#include <iostream>
#include "tree_smartptr.hpp"

using namespace std;

void printInt(int x) {
    cout << x << " ";
}

int main() {
    cout << "Testing Tree with Smart Pointers and Parent Pointers\n";
    cout << "====================================================\n\n";
    
    // Create a tree using initializer list
    cout << "Creating tree with values: 50, 30, 70, 20, 40, 60, 80\n";
    Tree<int> tree{50, 30, 70, 20, 40, 60, 80};
    
    cout << "Tree size: " << tree.size() << "\n\n";
    
    // Test traversals
    cout << "Inorder traversal (should be sorted): ";
    tree.inorder(printInt);
    cout << "\n";
    
    cout << "Preorder traversal: ";
    tree.preorder(printInt);
    cout << "\n";
    
    cout << "Postorder traversal: ";
    tree.postorder(printInt);
    cout << "\n\n";
    
    // Test member function
    cout << "Testing member function:\n";
    cout << "Is 40 in tree? " << (tree.member(40) ? "yes" : "no") << "\n";
    cout << "Is 100 in tree? " << (tree.member(100) ? "yes" : "no") << "\n\n";
    
    // Test find function
    cout << "Testing find function:\n";
    Tree<int> subtree;
    if (tree.find(30, subtree)) {
        cout << "Found 30, subtree root: " << subtree.root() << "\n";
        cout << "Subtree size: " << subtree.size() << "\n";
        cout << "Subtree inorder: ";
        subtree.inorder(printInt);
        cout << "\n";
    }
    cout << "\n";
    
    // Test parent pointer functionality
    cout << "Testing parent pointers:\n";
    cout << "Is main tree root? " << (tree.isRoot() ? "yes" : "no") << "\n";
    
    Tree<int> leftChild = tree.left();
    cout << "Left child root value: " << leftChild.root() << "\n";
    cout << "Is left child root? " << (leftChild.isRoot() ? "yes" : "no") << "\n";
    
    Tree<int> parentOfLeft = leftChild.parent();
    if (!parentOfLeft.isEmpty()) {
        cout << "Parent of left child: " << parentOfLeft.root() << "\n";
    }
    cout << "\n";
    
    // Build a simple tree manually to test parent pointers more clearly
    cout << "Building manual tree to test parent relationships:\n";
    Tree<int> leaf1(Tree<int>(), 10, Tree<int>());
    Tree<int> leaf2(Tree<int>(), 30, Tree<int>());
    Tree<int> manualTree(leaf1, 20, leaf2);
    
    cout << "Manual tree root: " << manualTree.root() << "\n";
    cout << "Manual tree inorder: ";
    manualTree.inorder(printInt);
    cout << "\n";
    
    auto manualLeft = manualTree.left();
    cout << "Left child value: " << manualLeft.root() << "\n";
    
    auto parentOfManualLeft = manualLeft.parent();
    if (!parentOfManualLeft.isEmpty()) {
        cout << "Parent of left child value: " << parentOfManualLeft.root() << "\n";
    } else {
        cout << "Left child has no parent\n";
    }
    cout << "\n";
    
    // Test with strings
    cout << "Testing with strings:\n";
    Tree<string> strTree{"dog", "cat", "elephant", "ant", "bird"};
    cout << "String tree inorder: ";
    strTree.inorder([](string s) { cout << s << " "; });
    cout << "\n\n";
    
    cout << "Tree smart pointer test complete!\n";
    cout << "Note: Smart pointers automatically manage memory!\n";
    cout << "Note: Parent pointers use weak_ptr to avoid circular references!\n";
    
    return 0;
}