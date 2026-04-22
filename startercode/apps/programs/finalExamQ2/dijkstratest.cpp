#include <iostream>
#include "adjlistgraph.hpp"
#include "dijkstra.hpp"

using namespace std;

int main() {
    AdjListGraph<int> g;

    // Build graph
    for (int i = 0; i < 5; i++) {
        g.addNode(i);
    }

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(2, 3);
    g.addEdge(3, 4);

    int source = 0;

    vector<int> dist = dijkstra(g, source);

    cout << "Shortest distances from node " << source << ":\n";

    for (int i = 0; i < dist.size(); i++) {
        cout << "To " << i << ": " << dist[i] << endl;
    }

    return 0;
}