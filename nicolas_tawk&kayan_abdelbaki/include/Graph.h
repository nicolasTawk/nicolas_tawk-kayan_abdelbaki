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


};

class Graph {
public:
    Graph() = default;

    int shortestPath(int srcId, int destId);
    bool removeVertex(int id);
    bool hasEdge(int srcId, int destId);
    void addVertex(int id);
    bool addEdge(int srcId, int destId);
    bool removeEdge(int srcId, int destId);
    void printGraph();

private:
    vector<Vertex> vertices;
};

#endif 
