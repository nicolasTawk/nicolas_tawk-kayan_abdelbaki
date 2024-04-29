// Graph.h

#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <vector>
using namespace std;

struct Edge {
    int dest; 
};


struct Vertex {
    int id;
    list<Edge> adjacencyList; 

    Vertex(int id);
};

class Graph {
public:
    Graph() = default;
  
    int shortestPath(int srcId, int destId);
    void removeVertex(int id);
    bool hasEdge(int srcId, int destId);
    void addVertex(int id);
    void addEdge(int srcId, int destId);
    void removeEdge(int srcId, int destId);
    void printGraph();

private:
    vector<Vertex> vertices; 
};

#endif 
