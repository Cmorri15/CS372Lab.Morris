#include <iostream>
#include "tree_smartptr.hpp"
#include "treefringe.hpp"

using namespace std;

void printList(const ListSmartPtr<int>& list) {
    for (auto it = list.cbegin(); it != list.cend(); ++it) {
        cout << *it << " ";
    }
    cout << "\n";
}

int main() {
    cout << "Testing Tree Fringe Functions\n";
    cout << "==============================\n\n";
    
    // Build Tree 1:
    //       50
    //      /  \
    //    30    70
    //   /  \   / \
    //  20  40 60 80
    cout << "Tree 1 structure:\n";
    cout << "       50\n";
    cout << "      /  \\\n";
    cout << "    30    70\n";
    cout << "   /  \\   / \\\n";
    cout << "  20  40 60 80\n\n";
    
    Tree<int> tree1{50, 30, 70, 20, 40, 60, 80};
    
    cout << "Fringe of Tree 1 (leaves left to right): ";
    ListSmartPtr<int> fringe1 = getFringe(tree1);
    printList(fringe1);
    cout << "\n";
    
    // Build Tree 2 - different shape but same fringe
    //         50
    //        /
    //       30
    //      /  \
    //    20    40
    //         /  \
    //        60   70
    //              \
    //              80
    cout << "Tree 2 structure (different shape):\n";
    cout << "         50\n";
    cout << "        /\n";
    cout << "       30\n";
    cout << "      /  \\\n";
    cout << "    20    40\n";
    cout << "         /  \\\n";
    cout << "        60   70\n";
    cout << "              \\\n";
    cout << "              80\n\n";
    
    // Manually build tree2 with specific structure
    Tree<int> leaf20(Tree<int>(), 20, Tree<int>());
    Tree<int> leaf60(Tree<int>(), 60, Tree<int>());
    Tree<int> leaf80(Tree<int>(), 80, Tree<int>());
    Tree<int> node70(Tree<int>(), 70, leaf80);
    Tree<int> node40(leaf60, 40, node70);
    Tree<int> node30(leaf20, 30, node40);
    Tree<int> tree2(node30, 50, Tree<int>());
    
    cout << "Fringe of Tree 2 (leaves left to right): ";
    ListSmartPtr<int>& fringe2 = getFringe(tree2);
    printList(fringe2);
    cout << "\n";
    
    // Compare fringes
    cout << "Do Tree 1 and Tree 2 have the same fringe? ";
    cout << (hasSameFringe(tree1, tree2) ? "YES" : "NO") << "\n\n";
    
    // Build Tree 3 - different fringe
    //       100
    //      /   \
    //    50     150
    //   /  \
    //  25  75
    cout << "Tree 3 structure:\n";
    cout << "       100\n";
    cout << "      /   \\\n";
    cout << "    50     150\n";
    cout << "   /  \\\n";
    cout << "  25  75\n\n";
    
    Tree<int> tree3{100, 50, 150, 25, 75};
    
    cout << "Fringe of Tree 3 (leaves left to right): ";
    ListSmartPtr<int>& fringe3 = getFringe(tree3);
    printList(fringe3);
    cout << "\n";
    
    cout << "Do Tree 1 and Tree 3 have the same fringe? ";
    cout << (hasSameFringe(tree1, tree3) ? "YES" : "NO") << "\n\n";
    
    // Test with single node tree
    cout << "Testing with single node tree (leaf):\n";
    Tree<int> singleNode(Tree<int>(), 42, Tree<int>());
    cout << "Single node fringe: ";
    ListSmartPtr<int>& fringeSingle = getFringe(singleNode);
    printList(fringeSingle);
    cout << "\n";
    
    // Test with empty tree
    cout << "Testing with empty tree:\n";
    Tree<int> emptyTree;
    cout << "Empty tree fringe size: " << getFringe(emptyTree).size() << "\n\n";
    
    cout << "Fringe test complete!\n";
    
    return 0;
}