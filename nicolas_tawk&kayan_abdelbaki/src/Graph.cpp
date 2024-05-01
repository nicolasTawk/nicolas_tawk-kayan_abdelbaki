// Graph.cpp

#include "../include/Graph.h"
#include <iostream>
#include <iostream>
#include <algorithm>
#include <limits>
#include <queue>

void Graph::addVertex(int id) {
    Vertex newVertex;
    newVertex.id = id;
    vertices.push_back(newVertex);
}



bool Graph::addEdge(int srcId, int destId) {
    for (auto& vertex : vertices) {
        if (vertex.id == srcId) {
            vertex.adjacencyList.push_back({ destId });
            break;
        }
    }
}

bool Graph::removeEdge(int srcId, int destId) {
    for (auto& vertex : vertices) {
        if (vertex.id == srcId) {
            vertex.adjacencyList.remove_if([destId](const Edge& edge) {
                return edge.dest == destId;
                });
            break;
        }
    }
}

bool Graph::hasEdge(int srcId, int destId) {
    auto src = find_if(vertices.begin(), vertices.end(), [srcId](const Vertex& v) { return v.id == srcId; });
    if (src != vertices.end()) {
        return any_of(src->adjacencyList.begin(), src->adjacencyList.end(), [destId](const Edge& e) { return e.dest == destId; });
    }
    return false;
}

bool Graph::removeVertex(int id) {
    vertices.erase(remove_if(vertices.begin(), vertices.end(), [id](const Vertex& v) { return v.id == id; }), vertices.end());
    for (auto& vertex : vertices) {
        vertex.adjacencyList.remove_if([id](const Edge& e) { return e.dest == id; });
    }
}


int Graph::shortestPath(int srcId, int destId) {
    // Implementing a BFS for shortest path calculation
    queue<int> q;
    vector<int> distances(vertices.size() + 1, numeric_limits<int>::max());  // Assuming vertex IDs start at 1

    // Find the source vertex index (assuming efficient vertex lookup)
    auto srcIndex = find_if(vertices.begin(), vertices.end(), [srcId](const Vertex& v) { return v.id == srcId; });
    if (srcIndex == vertices.end()) return -1;  // Source vertex not found

    // Initialize distances and enqueue source vertex
    q.push(srcId);
    distances[srcId] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        // Iterate through adjacent vertices directly from the current vertex
        for (const auto& edge : vertices[current].adjacencyList) {
            if (distances[edge.dest] == numeric_limits<int>::max()) {  // Unvisited neighbor
                distances[edge.dest] = distances[current] + 1;
                q.push(edge.dest);
                if (edge.dest == destId) return distances[edge.dest];  // Destination found, return distance
            }
        }
    }

    return -1;  // No path found
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

