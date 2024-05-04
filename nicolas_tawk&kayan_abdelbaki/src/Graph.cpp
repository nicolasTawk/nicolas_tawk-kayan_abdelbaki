// Graph.cpp

#include "../include/Graph.h"
#include <iostream>
#include <iostream>
#include <algorithm>
#include <limits>
#include <queue>
using namespace std;


/**
 * Initializes a graph with zero vertices and edges.
 */
Graph::Graph() {
    this->size = 0; // Set initial size to zero.
}

/**
 * Adds a vertex to the graph.
 * @param id Unique identifier for the vertex.
 */
void Graph::addVertex(int id) {
    Vertex v; // Create a new vertex instance.
    v.id = id; // Assign ID to the vertex.
    vertices.push_back(v); // Add vertex to the vertex list.
    size++; // Increment the count of vertices in the graph.
}

/**
 * Searches for a vertex by ID.
 * @param id The ID of the vertex to find.
 * @return True if the vertex is found, otherwise false.
 */
bool Graph::findVertex(int id) {
    for (auto it : vertices) {
        if (it.id == id) {
            return true; // Vertex found.
        }
    }
    return false; // Vertex not found.
}

/**
 * Adds an edge between two vertices if it does not already exist.
 * @param srcId Source vertex ID.
 * @param destId Destination vertex ID.
 * @return True if edge is added, false if not (including self-loops or existing edge).
 */
bool Graph::addEdge(int srcId, int destId) {
    if (srcId == destId) {
        cout << "equal";
        return false; // Prevents self-looping.
    }
    if (hasEdge(srcId, destId)) {
        cout << "already has";
        return false; // Prevents duplicate edges.
    }
    for (auto &vertex : vertices) {
        if (vertex.id == srcId) {
            vertex.adjacencyList.push_back({destId});
            return true; // Edge successfully added.
        }
    }
    cout << "neither";
    return false; // Both vertices must exist to add an edge.
}

/**
 * Removes an edge between two vertices.
 * @param srcId Source vertex ID.
 * @param destId Destination vertex ID.
 * @return True if the edge is removed, otherwise false.
 */
bool Graph::removeEdge(int srcId, int destId) {
    for (auto &vertex : vertices) {
        if (vertex.id == srcId) {
            auto &edges = vertex.adjacencyList;
            auto originalSize = edges.size();
            edges.remove_if([destId](const Edge &edge) {
                return edge.dest == destId;
            });
            return edges.size() != originalSize; // Returns true if size changed (edge was removed).
        }
    }
    return false; // No changes made if conditions not met.
}

/**
 * Checks if there is an edge between two vertices.
 * @param srcId Source vertex ID.
 * @param destId Destination vertex ID.
 * @return True if such an edge exists, otherwise false.
 */
bool Graph::hasEdge(int srcId, int destId) {
    auto srcIt = find_if(vertices.begin(), vertices.end(), [srcId](const Vertex &v) { return v.id == srcId; });
    if (srcIt != vertices.end()) {
        return any_of(srcIt->adjacencyList.begin(), srcIt->adjacencyList.end(), [destId](const Edge &e) {
            return e.dest == destId;
        });
    }
    return false;
}

/**
 * Removes a vertex and all its associated edges from the graph.
 * @param id ID of the vertex to remove.
 * @return True if the vertex is successfully removed, false if it does not exist.
 */
bool Graph::removeVertex(int id) {
    auto it = find_if(vertices.begin(), vertices.end(), [id](const Vertex &v) { return v.id == id; });
    if (it == vertices.end()) {
        return false; // Vertex not found.
    }
    // Remove the vertex and all edges pointing to or from it.
    vertices.erase(remove_if(vertices.begin(), vertices.end(), [id](const Vertex &v) { return v.id == id; }), vertices.end());
    for (auto &vertex : vertices) {
        vertex.adjacencyList.remove_if([id](const Edge &e) { return e.dest == id; });
    }
    size--; // Decrement the count of vertices.
    return true;
}

/**
 * Utility method for performing Depth-First Search (DFS) from a given vertex.
 * This method marks the vertex as visited and recursively visits all unvisited neighboring vertices.
 *
 * @param current The current vertex index.
 * @param visited A reference to a vector tracking which vertices have been visited.
 * @param result A reference to a vector accumulating the order of visited vertices.
 */
void Graph::DFSUtil(int current, vector<bool> &visited, vector<int> &result) {
    visited[current] = true;
    result.push_back(current); // Include this vertex in the result vector.
    // Recurse for all adjacent vertices.
    for (const Edge &neighbor : vertices[current].adjacencyList) {
        if (!visited[neighbor.dest]) {
            DFSUtil(neighbor.dest, visited, result);
        }
    }
}

/**
 * Initiates a Depth-First Search starting from the specified vertex.
 * This method prepares necessary data structures and starts the recursive DFS process.
 *
 * @param start The starting vertex index for the DFS.
 * @return A vector of vertex indices representing the DFS traversal order.
 */
vector<int> Graph::DFS(const int start) {
    vector<bool> visited(vertices.size(), false); // Track visited status of vertices.
    vector<int> result; // Store the traversal result.
    DFSUtil(start, visited, result); // Start the DFS from the given vertex.
    return result;
}

/**
 * Performs a Breadth-First Search (BFS) starting from the specified vertex.
 * This method uses a queue to explore all vertices level by level according to their distance from the start vertex.
 *
 * @param start The starting vertex index for the BFS.
 * @return A vector of vertex indices representing the BFS traversal order.
 */
vector<int> Graph::BFS(int start) const {
    vector<bool> visited(size, false); // Track visited status of vertices.
    queue<int> q; // Queue to manage the frontier vertices.
    vector<int> result; // Store the traversal result.

    visited[start] = true; // Mark the start vertex as visited.
    q.push(start); // Enqueue the start vertex.

    // Process the queue until empty.
    while (!q.empty()) {
        int current = q.front();
        q.pop();
        result.push_back(current); // Add the current vertex to the result.

        // Process all adjacent vertices.
        for (const Edge &neighbor : vertices[current].adjacencyList) {
            if (!visited[neighbor.dest]) {
                visited[neighbor.dest] = true; // Mark vertex as visited.
                q.push(neighbor.dest); // Enqueue the vertex.
            }
        }
    }

    return result;
}

/**
 * Clears all vertices and their associated edges from the graph, resetting it to an empty state.
 */
void Graph::emptyNetwork() {
    vertices.clear(); // Clear all vertices.
    size = 0; // Reset the size of the graph to zero.
}




//TODO : this function needs fixing
/*int Graph::shortestPath(int srcId, int destId) {
    // Implementing a BFS for shortest path calculation
    queue<int> q;
    vector<int> distances(vertices.size() + 1, numeric_limits<int>::max()); // Assuming vertex IDs start at 1

    // Find the source vertex index (assuming efficient vertex lookup)
    auto srcIndex = find_if(vertices.begin(), vertices.end(), [srcId](const Vertex &v) { return v.id == srcId; });
    if (srcIndex == vertices.end()) return -1; // Source vertex not found

    // Initialize distances and enqueue source vertex
    q.push(srcId);
    distances[srcId] = 0;

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        // Iterate through adjacent vertices directly from the current vertex
        for (const auto &edge: vertices[current].adjacencyList) {
            if (distances[edge.dest] == numeric_limits<int>::max()) {
                // Unvisited neighbor
                distances[edge.dest] = distances[current] + 1;
                q.push(edge.dest);
                if (edge.dest == destId) return distances[edge.dest]; // Destination found, return distance
            }
        }
    }

    return -1; // No path found
}*/
bool inline Graph::hasNeighbors(int id) {
    return !vertices[id].adjacencyList.empty();
}

bool Graph::isValidPath(vector<int> path, int start, int dest) {
    return path.front() == start && path.back() == dest;
}

vector<int> Graph::getIncomingVertices( int id) {
    std::vector<int> incomingVertices;
    for (const auto& vertex : vertices) {
        for (const auto& edge : vertex.adjacencyList) {
            if (edge.dest == id) {  // Check if edge points to vertexId
                incomingVertices.push_back(vertex.id);  // Add the source vertex's ID
                break;  // Break to avoid adding the same vertex ID multiple times if multiple edges point to vertexId
            }
        }
    }
    return incomingVertices;
}

vector<int> Graph::getOutgoingVertices(int id) {
    vector<int> dests;
    for (const Edge& edge : vertices[id].adjacencyList) {
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
