// Graph.cpp

#include "../include/Graph.h"
#include <iostream>
#include <iostream>
#include <algorithm>
#include <limits>
#include <queue>
using namespace std;


Graph::Graph() {
    this->size = 0;
}

void Graph::addVertex(int id) {
    Vertex v;
    v.id = id;
    vertices.push_back(v);
    size++;
}

bool Graph::findVertex(int id) {
    for (auto it: vertices) {
        if (it.id == id) {
            return true;
        }
    }
    return false;
}

bool Graph::addEdge(int srcId, int destId) {
    if (srcId == destId) {
        cout << "equal";
        return false; //self pointing not allowed
    }
    if (hasEdge(srcId, destId)) {
        cout << "already has";
        return false;
    }
    for (auto &vertex: vertices) {
        if (destId == vertex.id) {
            for (auto &vertex: vertices) {
                if (vertex.id == srcId) {
                    vertex.adjacencyList.push_back({destId});
                    return true;
                }
            }
        }
    }
    cout << "neither";
    return false;
}

bool Graph::removeEdge(int srcId, int destId) {
    for (auto &vertex: vertices) {
        if (vertex.id == srcId) {
            vertex.adjacencyList.remove_if([destId](const Edge &edge) {
                return edge.dest == destId;
            });
            break;
        }
    }
    return false;
}

bool Graph::hasEdge(int srcId, int destId) {
    auto src = find_if(vertices.begin(), vertices.end(), [srcId](const Vertex &v) { return v.id == srcId; });
    if (src != vertices.end()) {
        return any_of(src->adjacencyList.begin(), src->adjacencyList.end(),
                      [destId](const Edge &e) { return e.dest == destId; });
    }
    return false;
}

bool Graph::removeVertex(int id) {
    // First, check if the vertex to be removed actually exists
    auto it = std::find_if(vertices.begin(), vertices.end(), [id](const Vertex &v) { return v.id == id; });

    if (it == vertices.end()) {
        // Vertex not found
        return false;
    }

    // Remove the vertex
    vertices.erase(std::remove_if(vertices.begin(), vertices.end(), [id](const Vertex &v) { return v.id == id; }),
                   vertices.end());

    // Remove all edges in other vertices pointing to this id
    for (auto &vertex: vertices) {
        vertex.adjacencyList.remove_if([id](const Edge &e) { return e.dest == id; });
    }
    size--;
    return true;
}

void Graph::DFSUtil(int current, vector<bool> &visited, vector<int> &result) {
    visited[current] = true;
    // cout << current << " ";
    result.push_back(current);

    for (const Edge &neighbor: vertices[current].adjacencyList) {
        if (!visited[neighbor.dest]) {
            DFSUtil(neighbor.dest, visited, result);
        }
    }
}

vector<int> Graph::DFS(const int start) {
    vector<bool> visited(vertices.size(), false);
    // cout << size << endl;
    vector<int> result;

    // cout << "DFS starting from vertex " << start << ": ";

    DFSUtil(start, visited, result);
    return result;
}

vector<int> Graph::BFS(int start) const {
    vector<int> result;
    vector visited(size, false);

    queue<int> q;
    visited[start] = true;

    q.push(start);
    while (!q.empty()) {
        int current = q.front();
        result.push_back(current);
        q.pop();

        for (const Edge &neighbor: vertices[current].adjacencyList) {
            if (!visited[neighbor.dest]) {
                visited[neighbor.dest] = true;

                q.push(neighbor.dest);
            }
        }
    }

    return result;
}

void Graph::emptyNetwork() {
    vertices.clear();
}

int Graph::countPathsUtil(int src, int dest, int hops, int x) {
    if (hops > x) return 0;
    if (src == dest && hops == x) return 1;
    if (hops == x) return 0;

    int count = 0;
    for (const Edge& neighbor: vertices[src].adjacencyList) {
        count += countPathsUtil(neighbor.dest, dest, hops + 1, x);
    }
    return count;
}

int Graph::countPaths(int src, int dest, int x) {
    return countPathsUtil(src, dest, 0, x);
}

bool inline Graph::hasNeighbors(int id) {
    return !vertices[id].adjacencyList.empty();
}

bool Graph::isValidPath(vector<int> path, int start, int dest) {
    return path.front() == start && path.back() == dest;
}

vector<int> Graph::getIncomingVertices(int id) {
    std::vector<int> incomingVertices;
    for (const auto &vertex: vertices) {
        for (const auto &edge: vertex.adjacencyList) {
            if (edge.dest == id) {
                // Check if edge points to vertexId
                incomingVertices.push_back(vertex.id); // Add the source vertex's ID
                break; // Break to avoid adding the same vertex ID multiple times if multiple edges point to vertexId
            }
        }
    }
    return incomingVertices;
}

vector<int> Graph::getOutgoingVertices(int id) {
    vector<int> dests;
    for (const Edge &edge: vertices[id].adjacencyList) {
        dests.push_back(edge.dest);
        cout << edge.dest;
    }
    return dests;
}

vector<int> Graph::findShortestPath(int start, int destination) const {
    vector distance(size, INT_MAX);
    vector parent(size, -1);


    queue<int> q;

    distance[start] = 0;
    q.push(start);

    while (!q.empty()) {
        int current = q.front();
        cout << current << " ";

        q.pop();

        if (current == destination)
            break;


        for (const Edge &neighbor: vertices[current].adjacencyList) {
            if (distance[current] + 1 < distance[neighbor.dest]) {
                distance[neighbor.dest] = distance[current] + 1;
                parent[neighbor.dest] = current;
                q.push(neighbor.dest);
            }
        }
    }
    vector<int> shortestPath;
    for (int v = destination; v != -1; v = parent[v])
        shortestPath.push_back(v);

    reverse(shortestPath.begin(), shortestPath.end());
    cout << endl;
    return shortestPath;
}

void Graph::printGraph() {
    for (const auto &vertex: vertices) {
        cout << vertex.id << "->";
        for (const auto &edge: vertex.adjacencyList) {
            cout << edge.dest << "->";
        }
        cout << "null" << endl;
        cout << "|\n";
    }
    cout << "null" << endl;
}

vector<Vertex> Graph::getVertices() const {
    return vertices;
}


// int main() {
//     cout << "hello"<<endl;
//     Graph network;
//     network.addVertex(0);
//     network.addVertex(1);
//     network.addVertex(2);
//     network.addVertex(3);
//     network.addVertex(4);
//     network.addVertex(5);
//
//     network.addEdge(1, 2);
//     network.addEdge(4, 5);
//     network.addEdge(1, 3);
//     network.addEdge(2,4);
//
//
//     // vector<int> v =   network.BFS(network.getVertices()[1].id);
//
//
//
//
//      vector<int> v = network.DFS(1);
//     for(int i = 0; i < v.size(); i++) {
//         cout << v[i]<< "->";
//     }
//     cout << endl;
//
//     network.printGraph();
//
//     return 0;
// }
