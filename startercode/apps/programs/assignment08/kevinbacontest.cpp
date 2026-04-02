#include <iostream>
#include <vector>
#include <string>
#include "adjlistgraph.hpp"
#include "graphutils.hpp"

using namespace std;

int main() {
    cout << "Kevin Bacon Social Network\n";
    cout << "==========================\n\n";
    
    // Create a social graph with 20 people including you and Kevin Bacon
    vector<string> people = {
        "You",              // 0
        "Kevin Bacon",      // 1
        "Alice",            // 2
        "Bob",              // 3
        "Charlie",          // 4
        "Diana",            // 5
        "Eve",              // 6
        "Frank",            // 7
        "Grace",            // 8
        "Henry",            // 9
        "Ivy",              // 10
        "Jack",             // 11
        "Kelly",            // 12
        "Leo",              // 13
        "Maria",            // 14
        "Nathan",           // 15
        "Olivia",           // 16
        "Paul",             // 17
        "Quinn",            // 18
        "Rachel"            // 19
    };
    
    // Create connections (friendships)
    // Building a path from You to Kevin Bacon
    vector<pair<string, string>> connections = {
        // Your connections
        {"You", "Alice"},
        {"You", "Bob"},
        
        // Alice's connections
        {"Alice", "Charlie"},
        {"Alice", "Diana"},
        
        // Charlie's connections
        {"Charlie", "Eve"},
        {"Charlie", "Frank"},
        
        // Eve's connections
        {"Eve", "Grace"},
        {"Eve", "Henry"},
        
        // Grace's connections
        {"Grace", "Ivy"},
        {"Grace", "Kevin Bacon"},  // Connection to Kevin!
        
        // Kevin Bacon's other connections
        {"Kevin Bacon", "Jack"},
        {"Kevin Bacon", "Kelly"},
        
        // Additional network connections
        {"Bob", "Leo"},
        {"Diana", "Maria"},
        {"Frank", "Nathan"},
        {"Henry", "Olivia"},
        {"Jack", "Paul"},
        {"Kelly", "Quinn"},
        {"Leo", "Rachel"},
        
        // Make it bidirectional (undirected graph)
        {"Alice", "You"},
        {"Bob", "You"},
        {"Charlie", "Alice"},
        {"Diana", "Alice"},
        {"Eve", "Charlie"},
        {"Frank", "Charlie"},
        {"Grace", "Eve"},
        {"Henry", "Eve"},
        {"Ivy", "Grace"},
        {"Kevin Bacon", "Grace"},
        {"Jack", "Kevin Bacon"},
        {"Kelly", "Kevin Bacon"},
        {"Leo", "Bob"},
        {"Maria", "Diana"},
        {"Nathan", "Frank"},
        {"Olivia", "Henry"},
        {"Paul", "Jack"},
        {"Quinn", "Kelly"},
        {"Rachel", "Leo"}
    };
    
    AdjListGraph<string> socialGraph(people, connections);
    
    cout << "Social network created with " << people.size() << " people.\n\n";
    
    // Find path from You to Kevin Bacon
    vector<string> pathToKevin;
    bool connected = findPath(socialGraph, string("You"), string("Kevin Bacon"), pathToKevin);
    
    if (connected) {
        cout << "YES! You are connected to Kevin Bacon!\n\n";
        cout << "Path from You to Kevin Bacon:\n";
        for (size_t i = 0; i < pathToKevin.size(); i++) {
            cout << pathToKevin[i];
            if (i < pathToKevin.size() - 1) {
                cout << " -> ";
            }
        }
        cout << "\n\n";
        
        // Kevin Bacon number is the number of steps (edges) in the path
        int kevinBaconNumber = pathToKevin.size() - 1;
        cout << "Your Kevin Bacon number is: " << kevinBaconNumber << "\n";
        cout << "(This is the number of connections between you and Kevin Bacon)\n\n";
    } else {
        cout << "NO! You are not connected to Kevin Bacon.\n";
        cout << "Path is empty.\n\n";
    }
    
    // Test with someone not connected to Kevin
    cout << "Testing with a disconnected person:\n";
    
    // Add an isolated person
    socialGraph.addNode("Isolated Person");
    
    vector<string> pathFromIsolated;
    bool isolatedConnected = findPath(socialGraph, string("Isolated Person"), string("Kevin Bacon"), pathFromIsolated);
    
    if (isolatedConnected) {
        cout << "Isolated Person IS connected to Kevin Bacon.\n";
        cout << "Path: ";
        for (size_t i = 0; i < pathFromIsolated.size(); i++) {
            cout << pathFromIsolated[i];
            if (i < pathFromIsolated.size() - 1) cout << " -> ";
        }
        cout << "\n";
    } else {
        cout << "Isolated Person is NOT connected to Kevin Bacon.\n";
        cout << "Path is empty (size: " << pathFromIsolated.size() << ")\n";
    }
    
    cout << "\nKevin Bacon test complete!\n";
    
    return 0;
}