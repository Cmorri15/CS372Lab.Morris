#pragma once
#include <vector>
#include <set>
#include <queue>
#include <map>
#include "graph.hpp"

// Task 2: Check if a path is a simple cycle
// A simple cycle:
// - Starts and ends at the same node
// - Visits each node at most once (except start/end node)
// - All edges in the path must exist in the graph
template<typename N>
bool isSimpleCycle(Graph<N>& graph, const std::vector<N>& path) {
    // Empty path or single node cannot be a cycle
    if (path.size() < 2) {
        return false;
    }
    
    // Must start and end at same node
    if (path.front() != path.back()) {
        return false;
    }
    
    // Check that all edges in the path exist (valid path)
    for (size_t i = 0; i < path.size() - 1; i++) {
        if (!graph.adjacent(path[i], path[i + 1])) {
            return false;  // Edge doesn't exist
        }
    }
    
    // Check that no node is visited more than once (except start/end)
    std::set<N> visited;
    for (size_t i = 0; i < path.size() - 1; i++) {  // Exclude last node (same as first)
        if (visited.count(path[i]) > 0) {
            return false;  // Node visited twice - not simple
        }
        visited.insert(path[i]);
    }
    
    return true;
}

// Task 3: Find path between two nodes using BFS
// Returns true if path exists, false otherwise
// If path exists, pathOut contains the path from start to end
template<typename N>
bool findPath(Graph<N>& graph, N start, N end, std::vector<N>& pathOut) {
    pathOut.clear();
    
    if (start == end) {
        pathOut.push_back(start);
        return true;
    }
    
    // BFS to find shortest path
    std::queue<N> q;
    std::map<N, bool> visited;
    std::map<N, N> parent;  // Track parent to reconstruct path
    
    q.push(start);
    visited[start] = true;
    parent[start] = start;  // Start has no parent
    
    bool found = false;
    
    while (!q.empty() && !found) {
        N current = q.front();
        q.pop();
        
        std::vector<N> neighbors = graph.neighbors(current);
        for (const N& neighbor : neighbors) {
            if (!visited[neighbor]) {
                visited[neighbor] = true;
                parent[neighbor] = current;
                q.push(neighbor);
                
                if (neighbor == end) {
                    found = true;
                    break;
                }
            }
        }
    }
    
    if (!found) {
        return false;
    }
    
    // Reconstruct path from end to start
    N current = end;
    while (current != start) {
        pathOut.push_back(current);
        current = parent[current];
    }
    pathOut.push_back(start);
    
    // Reverse to get path from start to end
    std::reverse(pathOut.begin(), pathOut.end());
    
    return true;
}