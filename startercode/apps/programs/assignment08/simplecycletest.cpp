#include <iostream>
#include <vector>
#include "adjlistgraph.hpp"
#include "graphutils.hpp"

using namespace std;

void printPath(const vector<int>& path) {
    for (size_t i = 0; i < path.size(); i++) {
        cout << path[i];
        if (i < path.size() - 1) cout << " -> ";
    }
    cout << "\n";
}

int main() {
    cout << "Testing Simple Cycle Detection\n";
    cout << "===============================\n\n";
    
    // Create a graph
    vector<int> nodes = {1, 2, 3, 4, 5};
    vector<pair<int, int>> edges = {
        {1, 2}, {2, 3}, {3, 4}, {4, 1},  // Forms a cycle: 1->2->3->4->1
        {2, 5}, {5, 3}                    // Additional edges
    };
    
    AdjListGraph<int> graph(nodes, edges);
    
    cout << "Graph edges:\n";
    for (const auto& e : edges) {
        cout << e.first << " -> " << e.second << "\n";
    }
    cout << "\n";
    
    // Test 1: Valid simple cycle
    cout << "Test 1: Valid simple cycle (1 -> 2 -> 3 -> 4 -> 1)\n";
    vector<int> path1 = {1, 2, 3, 4, 1};
    cout << "Path: ";
    printPath(path1);
    cout << "Is simple cycle? " << (isSimpleCycle(graph, path1) ? "YES" : "NO") << "\n\n";
    
    // Test 2: Valid simple cycle (different path)
    cout << "Test 2: Valid simple cycle (2 -> 5 -> 3 -> 4 -> 1 -> 2)\n";
    vector<int> path2 = {2, 5, 3, 4, 1, 2};
    cout << "Path: ";
    printPath(path2);
    cout << "Is simple cycle? " << (isSimpleCycle(graph, path2) ? "YES" : "NO") << "\n\n";
    
    // Test 3: Not a cycle (doesn't return to start)
    cout << "Test 3: Not a cycle - doesn't return to start (1 -> 2 -> 3)\n";
    vector<int> path3 = {1, 2, 3};
    cout << "Path: ";
    printPath(path3);
    cout << "Is simple cycle? " << (isSimpleCycle(graph, path3) ? "YES" : "NO") << "\n\n";
    
    // Test 4: Visits node twice (not simple)
    cout << "Test 4: Not simple - visits node 2 twice (1 -> 2 -> 5 -> 3 -> 2 -> 1)\n";
    vector<int> path4 = {1, 2, 5, 3, 2, 1};
    cout << "Path: ";
    printPath(path4);
    cout << "Is simple cycle? " << (isSimpleCycle(graph, path4) ? "YES" : "NO") << "\n\n";
    
    // Test 5: Invalid edge in path
    cout << "Test 5: Invalid - edge doesn't exist (1 -> 3 -> 4 -> 1)\n";
    vector<int> path5 = {1, 3, 4, 1};
    cout << "Path: ";
    printPath(path5);
    cout << "Is simple cycle? " << (isSimpleCycle(graph, path5) ? "YES" : "NO") << "\n\n";
    
    // Test 6: Empty path
    cout << "Test 6: Empty path\n";
    vector<int> path6 = {};
    cout << "Path: (empty)\n";
    cout << "Is simple cycle? " << (isSimpleCycle(graph, path6) ? "YES" : "NO") << "\n\n";
    
    cout << "Simple cycle test complete!\n";
    
    return 0;
}