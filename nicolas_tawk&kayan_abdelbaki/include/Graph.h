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

    bool operator<(const Vertex& other) const {
        return id < other.id;
    }

    // Define == operator for comparison
    bool operator==(const Vertex& other) const {
        return id == other.id;
    }


};
typedef vector<Vertex>::const_iterator VertexIterator;
class Graph {
public:
    Graph();
    bool findVertex( int id);
    int shortestPath(int srcId, int destId);
    vector<int> findShortestPath(int start, int dest) const;
    void BFS(int start) const;
    bool removeVertex(int id);
    bool hasEdge(int srcId, int destId);
    void addVertex(int id);
    bool addEdge(int srcId, int destId);
    bool removeEdge(int srcId, int destId);
    void DFSUtil(int current, vector<bool>& visited);
    void DFS(int start); //
    void printGraph();


private:
    int size{};
    vector<Vertex> vertices;
};

#endif 
