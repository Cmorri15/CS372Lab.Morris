#pragma once

#include <vector>
#include <queue>
#include <limits>
#include <set>
#include <map>
#include "graph.hpp"

template<typename N>
std::vector<int> dijkstra(Graph<N>& g, N source) {

    std::set<N> allNodes;
    std::queue<N> q;
    std::set<N> visited;

    q.push(source);
    visited.insert(source);

    while (!q.empty()) {
        N u = q.front();
        q.pop();

        allNodes.insert(u);

        std::vector<N> neigh = g.neighbors(u);
        for (N v : neigh) {
            if (!visited.count(v)) {
                visited.insert(v);
                q.push(v);
            }
        }
    }

    std::map<N, int> index;
    int i = 0;
    for (N n : allNodes) {
        index[n] = i++;
    }

    int n = allNodes.size();

    std::vector<int> dist(n, std::numeric_limits<int>::max());
    std::vector<bool> used(n, false);

    using P = std::pair<int, N>;
    std::priority_queue<P, std::vector<P>, std::greater<P>> pq;

    dist[index[source]] = 0;
    pq.push({0, source});

    while (!pq.empty()) {

        P top = pq.top();
        pq.pop();

        int d = top.first;
        N u = top.second;

        int ui = index[u];

        if (used[ui]) continue;
        used[ui] = true;

        std::vector<N> neigh = g.neighbors(u);

        for (N v : neigh) {
            int vi = index[v];

            int alt = dist[ui] + 1; // unweighted graph

            if (alt < dist[vi]) {
                dist[vi] = alt;
                pq.push({alt, v});
            }
        }
    }

    return dist;
}