#include <algorithm>
#include <iostream>
#include <unordered_map>
#include "../include/Graph.h"
#include "../include/User.h"

using namespace std;

static int nextId = 0; // Static counter to assign unique IDs to each user, ensuring each has a unique identifier.

// Maps to maintain the network's state:
// users: Maps user IDs to User objects for easy access to user data by ID.
unordered_map<int, User> users;
// usernameToId: Facilitates quick username lookups to corresponding user IDs.
unordered_map<string, int> usernameToId;

/**
 * Adds a user to the network graph after taking their data from standard input.
 * If the username already exists, the function aborts and notifies the user.
 *
 * @param network Reference to the Graph object representing user connections.
 * The function performs the following steps:
 * 1. Receives user data via standard input and constructs a User object.
 * 2. Checks if the username already exists to prevent duplicates.
 * 3. Assigns a unique ID to the new user, adds them to the users map, and updates username-ID mapping.
 * 4. Adds a new vertex to the graph corresponding to the new user.
 * 5. Increments the ID counter for the next user.
 */
void addUser(Graph &network) {
    User user;
    cin >> user;
    string username = user.getUsername();
    if (usernameToId.find(username) != usernameToId.end()) {
        cerr << "Error: User with username '" << username << "' already exists." << endl;
        return;
    }
    users[nextId] = user;
    usernameToId[username] = nextId;
    network.addVertex(nextId);
    nextId++;
    cout << "User added successfully." << endl;
}

/**
 * Establishes a connection (edge) between two users in the network graph.
 * The connection is directional, representing a follower-followed relationship.
 *
 * @param network Reference to the Graph object.
 * The function performs the following steps:
 * 1. Receives usernames of the follower and followed from standard input.
 * 2. Retrieves their corresponding user IDs.
 * 3. Adds an edge between the follower and followed IDs in the graph.
 * 4. Provides feedback on the success or failure of the operation.
 */
void addConnection(Graph &network) {
    string follower, followed;
    cout << "Enter the username of the follower: ";
    cin >> follower;
    cout << "Enter the username of the followed: ";
    cin >> followed;
    int follower_id = usernameToId.find(follower) != usernameToId.end() ? usernameToId[follower] : -1;
    int followed_id = usernameToId.find(followed) != usernameToId.end() ? usernameToId[followed] : -1;

    if (follower_id != -1 && followed_id != -1) {
        if (network.addEdge(follower_id, followed_id))
            cout << "Friendship link added successfully" << endl;
        else
            cout << "Failed to add friendship link" << endl;
    } else {
        cout << "One or both of the users are not in the network" << endl;
    }
}

/**
 * Removes an existing connection (edge) between two users.
 * This operation respects the directionality of the connection (follower-followed).
 *
 * @param network Reference to the Graph object.
 * The function performs the following:
 * 1. Receives the usernames of the follower and followed from standard input.
 * 2. Converts usernames to user IDs.
 * 3. Attempts to remove the edge representing their connection from the graph.
 * 4. Provides feedback on the outcome.
 */
void removeConnection(Graph &network) {
    string follower, followed;
    cout << "Enter the username of the follower: ";
    cin >> follower;
    cout << "Enter the username of the followed: ";
    cin >> followed;

    int follower_id = usernameToId.find(follower) != usernameToId.end() ? usernameToId[follower] : -1;
    int followed_id = usernameToId.find(followed) != usernameToId.end() ? usernameToId[followed] : -1;

    if (follower_id != -1 && followed_id != -1) {
        if (network.removeEdge(follower_id, followed_id))
            cout << "Friendship link removed successfully" << endl;
        else
            cout << "Failed to remove friendship link" << endl;
    } else {
        cout << "One or both of the users are not in the network" << endl;
    }
}

/**
 * Removes a user entirely from the network graph and all associated data structures.
 *
 * @param network Reference to the Graph object.
 * The function performs the following:
 * 1. Receives the username of the user to be removed.
 * 2. Retrieves the user's ID and removes their vertex from the graph.
 * 3. Erases the user's data from the users map and the username-ID mapping.
 * 4. Provides feedback on the outcome.
 */
void removeUser(Graph &network) {
    string username;
    cout << "Enter the username of the user you want to remove: ";
    cin >> username;
    int userId = usernameToId.find(username) != usernameToId.end() ? usernameToId[username] : -1;

    if (userId != -1) {
        network.removeVertex(userId);
        users.erase(userId);
        usernameToId.erase(username);
        cout << "User removed successfully." << endl;
    } else {
        cout << "User not found." << endl;
    }
}

/**
 * Finds and displays the shortest path between two users in the graph.
 * This function is useful for understanding the degree of separation in social networks.
 *
 * @param network Reference to the Graph object.
 * The function performs the following:
 * 1. Receives the usernames of two users.
 * 2. Converts usernames to IDs.
 * 3. Retrieves and prints the shortest path between their vertices in the graph.
 * 4. Outputs the path and the degree of connectivity (path length).
 */
void findShortestPath(Graph &network) {
    string username1, username2;
    cout << "Enter the username of the first user: ";
    cin >> username1;
    cout << "Enter the username of the second user: ";
    cin >> username2;
    int id1 = usernameToId.find(username1) != usernameToId.end() ? usernameToId[username1] : -1;
    int id2 = usernameToId.find(username2) != usernameToId.end() ? usernameToId[username2] : -1;

    if (id1 != -1 && id2 != -1) {
        vector<int> shortestPath = network.findShortestPath(id1, id2);
        cout << "Path: ";
        for (const int &id : shortestPath) {
            cout << "(" + to_string(id) + ":" + users[id].getUsername() + ") -> ";
        }
        cout << "done" << endl;
        cout << "Degree of connectivity = " + to_string(shortestPath.size() - 1) << endl;
    } else {
        cout << "One or both users do not exist." << endl;
    }
}



/**
* Visualizes the entire network by printing a diagrammatic representation of all users and their connections.
* Each user (vertex) is represented with an ID and username, followed by a list of connections (edges) indicating who they connect to.
* This visualization aids in understanding the relational structure and connectivity within the network at a glance.
*
* @param network The Graph object that holds the entire network's graph representation.
*/
void visualiseNetwork(Graph &network) {
    // Iterate through each vertex in the graph to access individual user data.
    for (const auto &vertex : network.getVertices()) {
        // Display each user with their unique ID and username.
        cout << "(" + to_string(vertex.id) + ":" + users[vertex.id].getUsername() + ")" << "->";
        // List all direct connections for this user, showing outgoing relationships.
        for (const auto &edge : vertex.adjacencyList) {
            cout << "(" + to_string(edge.dest) + ":" + users[edge.dest].getUsername() + ")" << "->";
        }
        cout << "null" << endl;  // Ends the list of connections for this user.
        cout << "|\n";  // Visually separates each user's connections for better readability.
    }
    cout << "null" << endl;  // Indicates the end of the network visualization.
}

/**
 * Executes a Breadth-First Search (BFS) to explore the network layer by layer from a specified start point.
 * BFS is useful for mapping the shortest path in unweighted graphs and understanding network breadth.
 *
 * @param network The graph to perform BFS on, examining its breadth and connectivity.
 */
void BFS(Graph &network) {
    string username;
    cout << "Enter the username of the starting vertex: ";
    cin >> username;
    if (usernameToId.find(username) == usernameToId.end()) {
        cout << "Username does not exist." << endl;
        return;
    }
    vector<int> traversal = network.BFS(usernameToId[username]);
    // Output the BFS traversal starting from the specified user, showing the order of visitation.
    for (const int &id : traversal) {
        cout << "(" + to_string(id) + ":" + users[id].getUsername() + ")" << "->";
    }
    cout << "done" << endl;
    // Indicate whether all nodes were visited during the BFS, which reflects on the connectivity of the graph.
    if (traversal.size() == users.size())
        cout << "All vertices were visited!" << endl;
}

/**
 * Executes a Depth-First Search (DFS) from a given starting user, useful for understanding the depth and branching of network connections.
 * DFS can reveal clusters and substructures within the network, showing how deeply users are connected.
 *
 * @param network The graph to perform DFS on, examining depth and path diversity.
 */
void DFS(Graph &network) {
    string username;
    cout << "Enter the username of the starting vertex: ";
    cin >> username;
    if (usernameToId.find(username) == usernameToId.end()) {
        cout << "Username does not exist." << endl;
        return;
    }
    vector<int> traversal = network.DFS(usernameToId[username]);
    // Output the DFS traversal path, providing insight into the depth-first exploration of the network.
    for (const int &id : traversal) {
        cout << "(" + to_string(id) + ":" + users[id].getUsername() + ")" << "->";
    }
    cout << "done" << endl;
    // Indicate whether all nodes were reached during DFS, hinting at possible isolated sections or a fully connected network.
    if (traversal.size() == users.size())
        cout << "All vertices were visited!" << endl;
}

/**
 * Lists all followers of a specific user, identified by the incoming connections in the graph.
 * This is essential for understanding user influence and reach within the network.
 *
 * @param network The graph containing user connections.
 */
void getFollowers(Graph &network) {
    string username;
    cout << "Enter the username: ";
    cin >> username;
    if (usernameToId.find(username) == usernameToId.end()) {
        cout << "Username does not exist." << endl;
        return;
    }
    vector<int> followers = network.getIncomingVertices(usernameToId[username]);
    // Displays usernames of all followers, demonstrating the inbound connections to the specified user.
    for (const int &id : followers) {
        cout << users[id].getUsername() << ",";
    }
    cout << "end" << endl;
}

/**
 * Lists all users that a specific user is following, identified by the outgoing connections in the graph.
 * This function helps in tracking how users are engaging with others within the network.
 *
 * @param network The graph containing user connections.
 */
void getFollowings(Graph &network) {
    string username;
    cout << "Enter the username: ";
    cin >> username;
    if (usernameToId.find(username) == usernameToId.end()) {
        cout << "Username does not exist." << endl;
        return;
    }
    vector<int> followings = network.getOutgoingVertices(usernameToId[username]);
    // Displays usernames of all individuals that the specified user is following, showing the user's active connections.
    for (const int &id : followings) {
        cout << users[id].getUsername() << ",";
    }
    cout << "end" << endl;
}

void getMostPopular(Graph &network) {
}

/**
 * Identifies and lists mutual followers between two specified users.
 * Mutual followers are those users who are followed by both of the specified users, indicating shared social connections.
 *
 * @param network The graph containing user connections.
 * This function validates the existence of both usernames before calculating mutual followers.
 */
void getMutuals(Graph &network) {
    string username1, username2;
    cout << "Enter the username of the first user: ";
    cin >> username1;
    cout << "Enter the username of the second user: ";
    cin >> username2;
    if (usernameToId.find(username1) == usernameToId.end() || usernameToId.find(username2) == usernameToId.end()) {
        cout << "One or both usernames do not exist." << endl;
        return;
    }
    // Retrieve followings for both users to find mutual connections.
    vector<int> followers1 = network.getOutgoingVertices(usernameToId[username1]);
    vector<int> followers2 = network.getOutgoingVertices(usernameToId[username2]);
    vector<int> mutualUsers;
    // Use set intersection to find common followings.
    sort(followers1.begin(), followers1.end());
    sort(followers2.begin(), followers2.end());
    set_intersection(followers1.begin(), followers1.end(), followers2.begin(), followers2.end(), back_inserter(mutualUsers));
    // Display usernames of mutual followers.
    for (const int &id : mutualUsers) {
        cout << users[id].getUsername() << ",";
    }
    cout << "end" << endl;
}

/**
 * Prints detailed information about a specified user by username.
 * This includes potentially sensitive or detailed data intended for administrative or diagnostic purposes.
 *
 * @param network The graph containing user connections, although not directly used here.
 * This function validates the existence of the username in the network.
 */
void printUserDetails() {
    string username;
    cout << "Enter the username: ";
    cin >> username;
    int id = usernameToId.find(username) != usernameToId.end() ? usernameToId[username] : -1;
    if (id == -1) {
        cout << "User does not exist." << endl;
        return;
    }
    // Output user details assuming operator<< is overloaded for User objects.
    cout << users[id] << endl;
}

/**
 * Checks the friendship status between two specified users to determine if they are friends, follow each other, or have no connection.
 * This function is crucial for understanding social dynamics within the network.
 *
 * @param network The graph to check for existing connections (edges) between the users.
 * This function ensures both usernames exist before checking their relationship.
 */
void checkFriendshipDegree(Graph &network) {
    string username1, username2;
    cout << "Enter the username of the first user: ";
    cin >> username1;
    cout << "Enter the username of the second user: ";
    cin >> username2;
    int id1 = usernameToId.find(username1) != usernameToId.end() ? usernameToId[username1] : -1;
    int id2 = usernameToId.find(username2) != usernameToId.end() ? usernameToId[username2] : -1;
    if (id1 == -1 || id2 == -1) {
        cout << "One or both users do not exist." << endl;
        return;
    }
    // Check and describe the nature of the connection between the users.
    if (network.hasEdge(id1, id2) && network.hasEdge(id2, id1)) {
        cout << "The users are friends." << endl;
    } else if (network.hasEdge(id1, id2)) {
        cout << username1 + " follows " + username2 << endl;
    } else if (network.hasEdge(id2, id1)) {
        cout << username2 + " follows " + username1 << endl;
    } else {
        cout << "None of the users follow each other." << endl;
    }
}

/**
 * Clears all data from the network, effectively resetting the entire graph.
 * This function is useful for reinitializing the network during testing or after a significant modification.
 *
 * @param network The graph that will be emptied of all vertices and edges.
 */
void emptyNetwork(Graph &network) {
    network.emptyNetwork();  // Clears all vertices and edges from the graph.
    users.clear();           // Empties the map of user objects.
    usernameToId.clear();    // Clears the mapping of usernames to user IDs.
}



void menu() {
    cout << "Enter a number from 1 to 20" << endl;
    cout << "1: Add a user to the network " << endl;
    cout << "2: Add a connection between 2 users" << endl;
    cout << "3: remove a user from the network" << endl;
    cout << "4: remove a connection between two users" << endl;
    cout << "5: illustrate the network" << endl;
    cout << "6: find the shortest path between two users" << endl;
    cout << "7: traverse the network using BFS" << endl;
    cout << "8: traverse the network using DFS" << endl;
    cout << "9: print the details of a user" << endl;
    cout << "10: check the degree of frienship between two users " << endl;
    cout << "11: get the followers of a user" << endl;
    cout << "12: get the followings of a user" << endl;
    cout << "13: find the number of possible ways we can go from one user to another in x hoops" << endl;
    cout << "14: find the most popular user" << endl;
    cout << "15: list the mutuals of two users" << endl;
    cout << "16: empty the network" << endl;
    cout << "17: exit" << endl;
}

void handleChoice(Graph &network, int choice) {
    switch (choice) {
        case 1:
            addUser(network);
            break;
        case 2:
            addConnection(network);
            break;
        case 3:
            removeUser(network);
            break;
        case 4:
            removeConnection(network);
            break;
        case 5:
            visualiseNetwork(network);
            break;
        case 6:
            findShortestPath(network);
            break;
        case 7:
            BFS(network);
            break;
        case 8:
            DFS(network);
            break;
        case 9:
            printUserDetails();
            break;
        case 10:
            checkFriendshipDegree(network);
            break;
        case 11:
            getFollowers(network);
            break;
        case 12:
            getFollowings(network);
            break;
        case 13:
            cout << "not done yet" << endl;
            break;
        case 14:
            cout << "not done yet" << endl;
            break;
        case 15:
            getMutuals(network);
            break;
        case 16:
            emptyNetwork(network);
            break;
        case 17:
            cout << "Goodbye"<<endl;
        default:
            cout << "invalid choice" << endl;
            break;
    }
}

int main() {
    Graph network = Graph();

    int choice;
    do {
        menu();
        cin >> choice;
        while (choice < 1 || choice > 17) {
            cout << "Make sure the number is between 1 and 18 inclusively" << endl;
            cin >> choice;
        }
        handleChoice(network, choice);
    } while (choice != 17);


    return 0;
}

// TODO : saveToFiles (functions that saves data in a file)
void saveToFiles(Graph & network) {

}

// TODO : loadFromFiles (functions that loads data from a file)
void loadToFiles(Graph & network) {

}
