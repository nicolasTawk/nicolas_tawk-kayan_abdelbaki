#include "../include/Graph.h"
#include <iostream>
#include <algorithm>
#include <limits>
#include <queue>
using namespace std;

// Constructor for the Graph class, initializes an empty graph
Graph::Graph() {
    this->size = 0;
}

// Adds a new vertex with the specified ID to the graph
// @param id: The unique identifier for the new vertex
void Graph::addVertex(int id) {
    Vertex v;
    v.id = id;
    vertices.push_back(v);
    size++;
}

// Checks if a vertex with the specified ID exists in the graph
// @param id: The ID to check for in the graph
// @return: Returns true if the vertex is found, false otherwise
bool Graph::findVertex(int id) {
    for (auto it: vertices) {
        if (it.id == id) {
            return true;
        }
    }
    return false;
}

// Adds an edge from a source vertex to a destination vertex
// @param srcId: The source vertex ID
// @param destId: The destination vertex ID
// @return: Returns true if the edge was added, false otherwise (if edge already exists or if IDs are the same)
bool Graph::addEdge(int srcId, int destId) {
    if (srcId == destId) {
        cout << "equal";
        return false; // Self pointing not allowed
    }
    if (hasEdge(srcId, destId)) {
        cout << "already has";
        return false; // Edge already exists
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
    return false; // Neither vertex found
}

// Removes an edge between the specified source and destination vertices
// @param srcId: The source vertex ID
// @param destId: The destination vertex ID
// @return: Returns true if the edge was removed, false otherwise
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

// Checks if there is an edge from the source vertex to the destination vertex
// @param srcId: The source vertex ID
// @param destId: The destination vertex ID
// @return: Returns true if the edge exists, false otherwise
bool Graph::hasEdge(int srcId, int destId) {
    auto src = find_if(vertices.begin(), vertices.end(), [srcId](const Vertex &v) { return v.id == srcId; });
    if (src != vertices.end()) {
        return any_of(src->adjacencyList.begin(), src->adjacencyList.end(),
                      [destId](const Edge &e) { return e.dest == destId; });
    }
    return false;
}

// Removes a vertex and all edges connected to it
// @param id: The ID of the vertex to remove
// @return: Returns true if the vertex was removed, false otherwise
bool Graph::removeVertex(int id) {
    auto it = std::find_if(vertices.begin(), vertices.end(), [id](const Vertex &v) { return v.id == id; });

    if (it == vertices.end()) {
        return false; // Vertex not found
    }

    vertices.erase(std::remove_if(vertices.begin(), vertices.end(), [id](const Vertex &v) { return v.id == id; }),
                   vertices.end());

    for (auto &vertex: vertices) {
        vertex.adjacencyList.remove_if([id](const Edge &e) { return e.dest == id; });
    }
    size--;
    return true;
}

// Utility function for Depth-First Search (DFS)
// @param current: The current vertex being visited
// @param visited: Reference to vector indicating if a vertex has been visited
// @param result: Reference to vector storing the order of visited vertices
void Graph::DFSUtil(int current, vector<bool> &visited, vector<int> &result) {
    visited[current] = true;
    result.push_back(current);

    for (const Edge &neighbor: vertices[current].adjacencyList) {
        if (!visited[neighbor.dest]) {
            DFSUtil(neighbor.dest, visited, result);
        }
    }
}

// Performs Depth-First Search starting from the given vertex
// @param start: The starting vertex for DFS
// @return: Returns a vector containing the order of visited vertices
vector<int> Graph::DFS(const int start) {
    vector<bool> visited(vertices.size(), false);
    vector<int> result;

    DFSUtil(start, visited, result);
    return result;
}

// Performs Breadth-First Search starting from the given vertex
// @param start: The starting vertex for BFS
// @return: Returns a vector containing the order of visited vertices
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

// Empties the entire network, removing all vertices and edges
void Graph::emptyNetwork() {
    vertices.clear();
}

// Helper function to count all paths from source to destination with exactly x hops
// @param src: The source vertex ID
// @param dest: The destination vertex ID
// @param hops: The current number of hops
// @param x: The maximum allowed number of hops
// @return: Returns the count of all valid paths
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

// Counts all paths from source to destination with exactly x hops
// @param src: The source vertex ID
// @param dest: The destination vertex ID
// @param x: The maximum allowed number of hops
// @return: Returns the count of all valid paths
int Graph::countPaths(int src, int dest, int x) {
    return countPathsUtil(src, dest, 0, x);
}

// Checks if a vertex has any neighbors
// @param id: The vertex ID
// @return: Returns true if the vertex has neighbors, false otherwise
bool inline Graph::hasNeighbors(int id) {
    return !vertices[id].adjacencyList.empty();
}

// Validates a path from start to destination
// @param path: Vector containing vertex IDs representing the path
// @param start: The starting vertex ID
// @param dest: The destination vertex ID
// @return: Returns true if the path is valid, false otherwise
bool Graph::isValidPath(vector<int> path, int start, int dest) {
    return path.front() == start && path.back() == dest;
}

// Retrieves all incoming vertices to the specified vertex ID
// @param id: The vertex ID
// @return: Returns a vector of vertex IDs that have edges pointing to the specified vertex
vector<int> Graph::getIncomingVertices(int id) {
    std::vector<int> incomingVertices;
    for (const auto &vertex: vertices) {
        for (const auto &edge: vertex.adjacencyList) {
            if (edge.dest == id) {
                incomingVertices.push_back(vertex.id);
                break;
            }
        }
    }
    return incomingVertices;
}

// Retrieves all outgoing vertices from the specified vertex ID
// @param id: The vertex ID
// @return: Returns a vector of vertex IDs that are destinations from the specified vertex
vector<int> Graph::getOutgoingVertices(int id) {
    vector<int> dests;
    for (const Edge &edge: vertices[id].adjacencyList) {
        dests.push_back(edge.dest);
        cout << edge.dest;
    }
    return dests;
}

// Finds the shortest path from start to destination
// @param start: The starting vertex ID
// @param destination: The destination vertex ID
// @return: Returns a vector containing vertex IDs in the order of the shortest path
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

// Prints the entire graph structure to the console
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

// Retrieves the list of all vertices in the graph
// @return: Returns a vector of vertices
vector<Vertex> Graph::getVertices() const {
    return vertices;
}

