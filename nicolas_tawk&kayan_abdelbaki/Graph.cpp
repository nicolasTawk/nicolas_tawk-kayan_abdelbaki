#include "Graph.h"

Graph::Graph(int V) {
    this->V = V;
    adj.resize(V);
}
void Graph::addVertex() {
    // Increase the number of vertices and add a new list for the new vertex
    adj.emplace_back();
    V++;
}
void Graph::addEdge(int v, int w) {
    adj[v].push_back(w); 
}

void Graph::printGraph() {
    for (int v = 0; v < V; ++v) {
        std::cout << "Adjacency list of vertex " << v << "\n head ";
        for (auto x : adj[v]) {
            std::cout << "-> " << x;
        }
        std::cout << std::endl;
    }
}
