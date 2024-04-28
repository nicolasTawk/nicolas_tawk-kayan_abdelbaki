// Graph.cpp

#include "Graph.h"
#include <iostream>

//Vertex::Vertex(int id) : id(id) {}


//void Graph::addVertex(int id) {
    //vertices.push_back(id);
//}
void Graph::addVertex(int id) {
    Vertex newVertex(id);
    vertices.push_back(newVertex);
}



void Graph::addEdge(int srcId, int destId) {
    for (auto& vertex : vertices) {
        if (vertex.id == srcId) {
            vertex.adjacencyList.push_back({ destId });
            break;
        }
    }
}

void Graph::removeEdge(int srcId, int destId) {
    for (auto& vertex : vertices) {
        if (vertex.id == srcId) {
            vertex.adjacencyList.remove_if([destId](const Edge& edge) {
                return edge.dest == destId;
                });
            break;
        }
    }
}

void Graph::printGraph() {
    for (const auto& vertex : vertices) {
        std::cout << "Vertex " << vertex.id << " connects to: ";
        for (const auto& edge : vertex.adjacencyList) {
            std::cout << edge.dest << ", ";
        }
        std::cout << std::endl;
    }
}

