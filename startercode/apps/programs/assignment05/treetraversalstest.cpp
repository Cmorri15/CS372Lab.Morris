#include <iostream>
#include "tree_smartptr.hpp"
#include "treetraversals.hpp"

using namespace std;

void printInt(int x) {
    cout << x << " ";
}

int main() {
    cout << "Testing Tree Traversal Functions\n";
    cout << "=================================\n\n";
    
    // Create a tree
    cout << "Creating tree with values: 50, 30, 70, 20, 40, 60, 80\n";
    Tree<int> tree{50, 30, 70, 20, 40, 60, 80};
    
    cout << "\nTree structure:\n";
    cout << "        50\n";
    cout << "       /  \\\n";
    cout << "      30   70\n";
    cout << "     / \\   / \\\n";
    cout << "    20 40 60 80\n\n";
    
    // Compare different traversals
    cout << "Inorder (left-root-right): ";
    tree.inorder(printInt);
    cout << "\n";
    
    cout << "Preorder (root-left-right): ";
    tree.preorder(printInt);
    cout << "\n";
    
    cout << "Postorder (left-right-root): ";
    tree.postorder(printInt);
    cout << "\n";
    
    cout << "Level order (level by level): ";
    levelTraversal(tree, printInt);
    cout << "\n\n";
    
    // Test level traversal with different tree
    cout << "Creating smaller tree: 5, 3, 7, 1, 4\n";
    Tree<int> tree2{5, 3, 7, 1, 4};
    
    cout << "\nTree structure:\n";
    cout << "      5\n";
    cout << "     / \\\n";
    cout << "    3   7\n";
    cout << "   / \\\n";
    cout << "  1   4\n\n";
    
    cout << "Level order traversal: ";
    levelTraversal(tree2, printInt);
    cout << "\n\n";
    
    // Test prune function
    cout << "Testing prune function (removes all leaf nodes):\n\n";
    
    cout << "Original tree level order: ";
    levelTraversal(tree, printInt);
    cout << "\n";
    
    Tree<int> prunedTree = prune(tree);
    
    cout << "After pruning level order: ";
    levelTraversal(prunedTree, printInt);
    cout << "\n";
    
    cout << "Original tree size: " << tree.size() << "\n";
    cout << "Pruned tree size: " << prunedTree.size() << "\n\n";
    
    // Test prune on tree2
    cout << "Pruning smaller tree:\n";
    cout << "Original: ";
    levelTraversal(tree2, printInt);
    cout << "\n";
    
    Tree<int> prunedTree2 = prune(tree2);
    cout << "After pruning: ";
    levelTraversal(prunedTree2, printInt);
    cout << "\n\n";
    
    // Test with single node (should become empty)
    cout << "Testing prune on single-node tree:\n";
    Tree<int> singleNode{42};
    cout << "Original size: " << singleNode.size() << "\n";
    Tree<int> prunedSingle = prune(singleNode);
    cout << "After pruning size: " << prunedSingle.size() << "\n";
    cout << "Is empty? " << (prunedSingle.isEmpty() ? "yes" : "no") << "\n\n";
    
    // Test with strings
    cout << "Testing with string tree:\n";
    Tree<string> strTree{"dog", "cat", "elephant", "ant", "bird"};
    cout << "Level order: ";
    levelTraversal(strTree, [](string s) { cout << s << " "; });
    cout << "\n\n";
    
    cout << "Tree traversals test complete!\n";
    
    return 0;
}