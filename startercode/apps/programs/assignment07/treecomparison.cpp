#include <iostream>
#include <iomanip>
#include "treeutils.hpp"

using namespace std;

int main() {
    cout << "BST vs AVL Tree Search Performance Comparison\n";
    cout << "=============================================\n\n";
    
    int sizes[] = {100, 500, 1000, 2500, 5000, 10000};
    
    cout << fixed << setprecision(6);
    cout << setw(10) << "Size" 
         << setw(20) << "BST Avg (ms)" 
         << setw(20) << "AVL Avg (ms)" 
         << setw(20) << "Speedup" << "\n";
    cout << string(70, '-') << "\n";
    
    for (int size : sizes) {
        cout << "Testing with " << size << " elements...\n";
        
        // Generate random tree
        Tree<int>& bst = generateRandomTree(size);
        
        // Convert to AVL
        AVLTree<int>& avl = convertToAVL(bst);
        
        // Compare search times
        pair<double, double>& times = compareSearchTimes(bst, avl);
        
        double speedup = times.first / times.second;
        
        cout << setw(10) << size 
             << setw(20) << times.first 
             << setw(20) << times.second 
             << setw(20) << speedup << "x\n";
    }
    
    cout << "\nComparison complete!\n";
    
    return 0;
}