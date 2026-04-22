#pragma once

#include <vector>
#include <limits>
#include "adjmatrixgraph.hpp"

template <typename N>
std::vector<std::vector<int>> floydWarshall(AdjMatrixGraph<N>& g, const std::vector<N>& nodes) {

    int n = nodes.size();
    const int INF = 1e8;

    std::vector<std::vector<int>> D(n, std::vector<int>(n, INF));

    // initialize diagonal
    for (int i = 0; i < n; i++) {
        D[i][i] = 0;
    }

    // build initial distances using SAFE neighbors()
    for (int i = 0; i < n; i++) {

        std::vector<N> neigh = g.neighbors(nodes[i]);

        for (N v : neigh) {

            // find index of v
            for (int j = 0; j < n; j++) {
                if (nodes[j] == v) {
                    D[i][j] = 1;
                }
            }
        }
    }

    // Floyd-Warshall core
    for (int k = 0; k < n; k++) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {

                if (D[i][k] + D[k][j] < D[i][j]) {
                    D[i][j] = D[i][k] + D[k][j];
                }
            }
        }
    }

    return D;
}