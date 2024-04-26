#include <vector>
#include <list>
#include <iostream>

class Graph {
public:
    Graph(int V); 
    void addEdge(int v, int w); 
    void printGraph(); 
    void addVertex();
private:
    int V; 
    std::vector<std::list<int>> adj; 
};
