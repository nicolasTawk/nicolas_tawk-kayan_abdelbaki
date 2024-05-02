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

//
// void Graph::adjustIDs(int deletion) {
//     int id= 0;
//     for(int i = 0; i < vertices.size();i++) {
//
//     }
//     for(      Vertex &vertex : std::ranges::subrange(vertices.begin() + 2, vertices.end())) {
//         vertex.id--;
//         for(Edge &edge : vertex.adjacencyList) {
//             if(edge.dest > deletion)
//                 edge.dest--;
//
//         }
//     }
//     for(Vertex &vertex: vertices.begin()  , vertices.begin() + deletion) {
//         for(Edge &edge : vertex.adjacencyList) {
//             if(edge.dest > deletion)
//                 edge.dest--;
//         }
//     }
// }

bool Graph::findVertex(int id) {
    for(auto it : vertices) {
        if( it.id == id) {
            return true;
        }
    }
    return false;
}

bool Graph::addEdge(int srcId, int destId) {
    if(srcId == destId) {
        return false;  //self pointing not allowed
    }
    if(hasEdge(srcId, destId))
        return false;
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
    vertices.erase(std::remove_if(vertices.begin(), vertices.end(), [id](const Vertex &v) { return v.id == id; }), vertices.end());

    // Remove all edges in other vertices pointing to this id
    for (auto &vertex : vertices) {
        vertex.adjacencyList.remove_if([id](const Edge &e) { return e.dest == id; });
    }
    size--;
    return true;
}

void Graph::DFSUtil(int current, vector<bool>& visited) {

    //marks the current vertex current as visited.
    visited[current] = true;
    cout << current << " ";

    //loop iterates over all neighbors of the current vertex current
    for (const Edge & neighbor: vertices[current].adjacencyList) {

        if (!visited[neighbor.dest]) {

            //If the neighbor vertex has not been visited,
            //it recursively calls DFSUtil to visit that neighbor.
            DFSUtil(neighbor.dest, visited);
        }
    }
}
//TODO: has the same issue of the BFS
void Graph::DFS(int start) {

    //creates a boolean vector visited of size vertices
    //(the total number of vertices in the graph) initialized with false.
    vector<bool> visited(size, false);
    cout << size << endl;

    cout << "DFS starting from vertex " << start << ": ";

    //calls the DFSUtil function to start the DFS traversal from the vertex start
    DFSUtil(start, visited);
    cout << endl;
}

//TODO : this method needs fixing because the ids might not be consecutive due to the removeVertex method
void  Graph::BFS(int start) const {

    //creates a boolean vector visited of size vertices
    //(the total number of vertices in the graph) initialized with false.
    vector<bool> visited(size, false);

    //queue<int> q declares a queue q of integers.
    //to keep track of vertices that are discovered during the BFS traversal
    queue<int> q;

    //marks the starting vertex start as visited.
    visited[start] = true;

    //adds the starting vertex start to the queue q.
    q.push(start);

    cout << "BFS starting from vertex " << start << ": ";
    while (!q.empty()) {

        //retrieves the front element of the queue q
        int current = q.front(); cout << current << " ";
        //removes the current vertex from the queue since it has been fully explored.
        q.pop();

        //This for loop iterates over all neighbors of the current vertex current by
        //accessing the adjacency list of current stored in adjList.

        for (const Edge & neighbor : vertices[current-1].adjacencyList) {

            if (!visited[neighbor.dest]) {

                //If the neighbor vertex has not been visited, it marks it as visited.
                visited[neighbor.dest] = true;

                //then adds the neighbor vertex to the queue q to explore it in
                //the next iterations of the while loop.
                q.push(neighbor.dest);
            }
        }
    }

    cout << endl;
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

    vector<int> Graph::findShortestPath(int start, int destination) const {

        //Distance vector stores the shortest distance from the start vertex to all other vertices. Initialize distances to infinity.
        vector<int> distance(size, INT_MAX);

        //This vector stores the parent vertex of each vertex in the shortest path.
        //It is initialized with all values set to -1.
        vector<int> parent(size, -1);

        //This is a queue used for the BFS traversal.It stores vertices to be visited.
        queue<int> q;

        distance[start] = 0; // Distance to start vertex is 0
        //The start vertex is pushed onto the queue to begin the BFS traversal.
        q.push(start);

        while (!q.empty()) {
            //current is the vertex being processed from the front of the queue.
            int current = q.front();
            q.pop();

            if (current == destination)
                break; // Break if destination is found

            //For each neighbor of the current vertex, we check if
            //the distance to the neighbor through the current vertex
            //is shorter than the distance stored in distance[neighbor].
            for (const Edge & neighbor : vertices[current].adjacencyList) {
                if (distance[current] + 1 < distance[neighbor.dest]) {

                    //If a shorter path is found, we update the distance to the neighbor
                    //and set its parent to the current vertex.
                    //and the neighbor is then added to the queue for further exploration.
                    distance[neighbor.dest] = distance[current] + 1;
                    parent[neighbor.dest] = current; // Update parent
                    q.push(neighbor.dest);
                }
            }
        }
        vector<int> shortestPath;
        for (int v = destination; v != -1; v = parent[v])
            shortestPath.push_back(v);

        //The path is initially constructed in reverse order (from destination to start). We reverse it to obtain the correct order (from start to destination).
        reverse(shortestPath.begin(), shortestPath.end());

        return shortestPath;
    }

void Graph::printGraph() {
    for (const auto &vertex: vertices) {
        cout <<vertex.id << "->";
        for (const auto &edge: vertex.adjacencyList) {
            cout << edge.dest << "->";
        }
        cout << "null" <<endl;
        cout << "|\n";
    }
    cout <<"null"<<endl;
}



int main() {
    cout << "hello"<<endl;
    Graph network;
    network.addVertex(0);
    network.addVertex(1);
    network.addVertex(2);
    network.addVertex(3);
    network.addVertex(4);


    network.addEdge(0, 1);
    network.addEdge(0, 2);
    network.addEdge(1, 4);
    network.addEdge(3, 4);
    network.addEdge(2, 3);

    network.DFS(0);
    vector<int> v = network.findShortestPath(0,3);
    for(int i = 0; i < v.size(); i++) {
        cout << v[i]<< " ";
    }
    cout << endl;

    network.printGraph();

    return 0;
}