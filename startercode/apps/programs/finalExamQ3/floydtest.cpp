#include <iostream>
#include <vector>
#include "adjmatrixgraph.hpp"
#include "floyd.hpp"

using namespace std;

int main() {

    AdjMatrixGraph<int> g;

    vector<int> nodes = {0, 1, 2, 3};

    for (int n : nodes) {
        g.addNode(n);
    }

    g.addEdge(0, 1);
    g.addEdge(1, 2);
    g.addEdge(2, 3);
    g.addEdge(0, 3);

    vector<vector<int>> D = floydWarshall(g, nodes);

    cout << "All-Pairs Shortest Paths:\n\n";

    for (int i = 0; i < D.size(); i++) {
        for (int j = 0; j < D.size(); j++) {

            if (D[i][j] >= 1e8) cout << "INF ";
            else cout << D[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}