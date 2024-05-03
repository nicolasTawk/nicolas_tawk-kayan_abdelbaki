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
    //TODO: method that creates a graph with randomly generated connections
    // void createRandomGraph(int size);
    bool hasNeighbors(int);
    bool findVertex( int id);
    int shortestPath(int srcId, int destId);
    [[nodiscard]] vector<int> findShortestPath(int start, int dest) const;
    vector<int> BFS(int start) const;
    bool removeVertex(int id);
    bool hasEdge(int srcId, int destId);
    void addVertex(int id);
    bool addEdge(int srcId, int destId);
    bool removeEdge(int srcId, int destId);
    void DFSUtil(int current, vector<bool>& visited, vector<int> &);
    void emptyNetwork();
    vector<int> DFS(int start); //
    //TODO: implement the iterative DFS method
    // vector<int> DFSiterative(int &);

    bool isValidPath(vector<int> , int , int );
    vector<int> getOutgoingVertices(int );
    vector<int> getIncomingVertices(int );
    void printGraph();
    [[nodiscard]] vector<Vertex> getVertices() const;


private:
    int size;
    vector<Vertex> vertices;
};

#endif 
