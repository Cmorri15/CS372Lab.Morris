#pragma once
#include <vector>
#include <set>
#include <queue>
#include <map>
#include "graph.hpp"

// Check if a path is a simple cycle
template<typename N>
bool isSimpleCycle(Graph<N>& graph, const std::vector<N>& path) {
    if (path.size() < 2) {
        return false;
    }
    
    if (path.front() != path.back()) {
        return false;
    }
    
    for (size_t i = 0; i < path.size() - 1; i++) {
        if (!graph.adjacent(path[i], path[i + 1])) {
            return false;
        }
    }
    
    std::set<N> visited;
    for (size_t i = 0; i < path.size() - 1; i++) {
        if (visited.count(path[i]) > 0) {
            return false;
        }
        visited.insert(path[i]);
    }
    
    return true;
}

// Find path between two nodes using BFS
template<typename N>
bool findPath(Graph<N>& graph, N start, N end, std::vector<N>& pathOut) {
    pathOut.clear();
    
    if (start == end) {
        pathOut.push_back(start);
        return true;
    }
    
    std::queue<N> q;
    std::map<N, bool> visited;
    std::map<N, N> parent;
    
    q.push(start);
    visited[start] = true;
    parent[start] = start;
    
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
    
    N current = end;
    while (current != start) {
        pathOut.push_back(current);
        current = parent[current];
    }
    pathOut.push_back(start);
    
    std::reverse(pathOut.begin(), pathOut.end());
    
    return true;
}

#include <cstdlib>
#include <ctime>
#include "adjlistgraph.hpp"
#include "adjmatrixgraph.hpp"

// Generate a random AdjListGraph
AdjListGraph<int>& generateAdjListGraph(int numberOfNodes, double edgeProbability) {
    static AdjListGraph<int>* graph = nullptr;
    delete graph;
    graph = new AdjListGraph<int>();

    for (int newNode = 0; newNode < numberOfNodes; newNode++) {
        graph->addNode(newNode);
        for (int existing = 0; existing < newNode; existing++) {
            double r = (double)rand() / RAND_MAX;
            if (r < edgeProbability) {
                graph->addEdge(newNode, existing);
            }
        }
    }
    return *graph;
}

// Generate a random AdjMatrixGraph
AdjMatrixGraph<int>& generateAdjMatrixGraph(int numberOfNodes, double edgeProbability) {
    static AdjMatrixGraph<int>* graph = nullptr;
    delete graph;
    graph = new AdjMatrixGraph<int>();

    for (int newNode = 0; newNode < numberOfNodes; newNode++) {
        graph->addNode(newNode);
        for (int existing = 0; existing < newNode; existing++) {
            double r = (double)rand() / RAND_MAX;
            if (r < edgeProbability) {
                graph->addEdge(newNode, existing);
            }
        }
    }
    return *graph;
}