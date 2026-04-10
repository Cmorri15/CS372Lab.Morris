#include <iostream>
#include <vector>
#include <chrono>
#include <cstdlib>
#include <ctime>
#include "adjmatrixgraph.hpp"
#include "graphutils.hpp"

using namespace std;
using namespace std::chrono;

int main() {
    srand(time(nullptr));

    cout << "DFS Performance Test - Adjacency Matrix\n";
    cout << "=========================================\n\n";

    vector<int> sizes = {2, 8, 64, 256, 1024};

    for (int n : sizes) {
        AdjMatrixGraph<int>& graph = generateAdjMatrixGraph(n, 0.5);

        auto start = high_resolution_clock::now();
        int visitCount = 0;
        graph.dfs(0, [&](int node) {
            visitCount++;
        });
        auto end = high_resolution_clock::now();

        duration<double> elapsed = end - start;

        cout << "Nodes: " << n
             << " | Visited: " << visitCount
             << " | DFS Time: " << elapsed.count() << " seconds\n";
    }

    cout << "\nPerformance test complete!\n";
    return 0;
}