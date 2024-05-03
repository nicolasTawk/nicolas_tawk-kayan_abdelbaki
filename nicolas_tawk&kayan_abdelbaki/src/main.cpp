#include <algorithm>

#include "../include/Graph.h"
#include "../include/User.h"
#include <iostream>
#include <unordered_map>
using namespace std;


static int nextId = 0;
// handling ids in the main class since username is a unique identifier and we only need an int value to work in graphs
unordered_map<int, User> users; // Maps user IDs to User objects
unordered_map<string, int> usernameToId; // For fast username lookup


//done
void addUser(Graph &network) {
    User user;
    cin >> user;
    if (usernameToId.find(user.getUsername()) != usernameToId.end()) {
        std::cerr << "Error: User with username '" << user.getUsername() << "' already exists." << std::endl;
        return;
    }
    users[nextId] = user;
    usernameToId[user.getUsername()] = nextId;
    network.addVertex(nextId);
    nextId++;
    std::cout << "User added successfully." << std::endl;
}

void addConnection(Graph &network) {
    string follower, followed;
    cout << "Enter the username of the follower : ";
    cin >> follower;
    cout << "Enter the username of the followed : ";
    cin >> followed;
    const int follower_id = usernameToId[follower];
    const int followed_id = usernameToId[followed];
    cout << "follower id" + to_string(follower_id) + "  followed id: " + to_string(followed_id) << endl;
    if (follower_id != -1 && followed_id != -1) {
        if (network.addEdge(follower_id, followed_id))
            cout << "Frienship link added succcesfully" << endl;
        else
            cout << "Failed to add frienship link" << endl;
    } else {
        cout << "One or both of the users are not in the network" << endl;
    }
}

void removeConnection(Graph &network) {
    string follower, followed;
    cout << "Enter the username of the follower : ";
    cin >> follower;
    cout << "Enter the username of the followed : ";
    cin >> followed;

    const int follower_id = usernameToId[follower];
    const int followed_id = usernameToId[followed];
    if (follower_id != -1 && followed_id != -1) {
        if (network.removeEdge(follower_id, followed_id))
            cout << "Frienship link removed succcesfully" << endl;
        else
            cout << "Failed to remove frienship link" << endl;
    } else {
        cout << "One or both of the users are not in the network" << endl;
    }
}

void removeUser(Graph &network) {
    string username;
    cout << "Enter the username of the user you want to remove: ";
    cin >> username;
    int userId = usernameToId[username];
    if (userId == -1) {
        cout << "User not found." << endl;
        return;
    }
    network.removeVertex(userId);
    users.erase(userId);
    usernameToId.erase(username);
    cout << "User removed successfully." << endl;
}

void findShortestPath(Graph &network) {
    string username1, username2;
    cout << "Enter the username of the first user: ";
    cin >> username1;
    cout << "Enter the username of the second user: ";
    cin >> username2;
    const int id1 = usernameToId[username1];
    const int id2 = usernameToId[username2];
    if (id1 == -1 || id2 == -1) {
        cout << "One or both users do not exist." << endl;
    }
    vector<int> shortestPath = network.findShortestPath(id1, id2);
    for (const int &id: shortestPath) {
        cout << "(" + to_string(id) + ":" + users[id].getUsername() + ")" << "->";
    }
    cout << "done"<< endl;
    cout << "The degree of connectivity = " + to_string(shortestPath.size() - 1) << endl;
}


void visualiseNetwork(Graph &network) {
    for (const auto &vertex: network.getVertices()) {
        cout << "(" + to_string(vertex.id) + ":" + users[vertex.id].getUsername() + ")" << "->";
        for (const auto &edge: vertex.adjacencyList) {
            cout << "(" + to_string(edge.dest) + ":" + users[edge.dest].getUsername() + ")" << "->";
        }
        cout << "null" << endl;
        cout << "|\n";
    }
    cout << "null" << endl;
}

void BFS(Graph &network) {
    string username;
    cout << "Enter the username of the starting vertex: ";
    cin >> username;
    vector<int> BFS = network.BFS(usernameToId[username]);
    for (const int &id: BFS) {
        cout << "(" + to_string(id) + ":" + users[id].getUsername() + ")" << "->";
    }
    cout << "done"<< endl;
    if (BFS.size() == users.size())
        cout << "All vertices were vistied!" << endl;
}


void DFS(Graph &network) {
    string username;
    cout << "Enter the username of the starting vertex: ";
    cin >> username;
    vector<int> DFS = network.DFS(usernameToId[username]);
    for (const int &id: DFS) {
        cout << "(" + to_string(id) + ":" + users[id].getUsername() + ")" << "->";
    }
    cout << "done" << endl;
    if (DFS.size() == users.size())
        cout << "All vertices were vistied!" << endl;
}

void getFollowers(Graph &network) {
    string username;
    cout << "Enter the username : ";
    cin >> username;
    vector<int> followers = network.getIncomingVertices(usernameToId[username]);
    for (const int &id: followers) {
        cout << users[id].getUsername() << ",";
    }
    cout << "end" << endl;
}

void getFollowings(Graph &network) {
    string username;
    cout << "Enter the username : ";
    cin >> username;
    vector<int> followings = network.getOutgoingVertices(usernameToId[username]);
    for (const int &id: followings) {
        cout << users[id].getUsername() << ",";
    }
    cout << "end" << endl;
}

void getMostPopular(Graph &network) {
}

void getMutuals(Graph &network) {
    string username1, username2;
    cout << "Enter the username of the first user: ";
    cin >> username1;
    cout << "Enter the username of the second user: ";
    cin >> username2;
    const int id1= usernameToId[username1];
    const int id2 = usernameToId[username2];
    if (id1 == -1 || id2 == -1) {
        cout << "One or both users do not exist." << endl;
    }
    vector<int> followers1 = network.getOutgoingVertices(id1);
    vector<int> followers2 = network.getOutgoingVertices(id2);
    vector<int> mutualUsers;
    sort(followers1.begin(), followers1.end());
    sort(followers2.begin(), followers2.end());

    set_intersection(
        followers1.begin(), followers1.end(),
        followers2.begin(), followers2.end(),
        back_inserter(mutualUsers)

    );
    for (const int &id: mutualUsers) {
        cout << users[id].getUsername() << ",";
    }
    cout << "end" << endl;
}

void printUserDetails() {
    string username;
    cout << "Enter the username : ";
    cin >> username;
    int id = usernameToId[username];
    if (id == -1) {
        cout << "User does not exist." << endl;
        return;
    }
    cout << users[id]<< endl;
}

void checkFrienshipDegree(Graph &network) {
    string username1, username2;
    cout << "Enter the username of the first user: ";
    cin >> username1;
    cout << "Enter the username of the second user: ";
    cin >> username2;
    int id1 = usernameToId[username1];
    int id2 = usernameToId[username2];
    if (id1 == -1 || id2 == -1) {
        cout << "One or both users do not exist." << endl;
    }
    if (network.hasEdge(id1, id2)
        && network.hasEdge(id2, id1)) {
        cout << "The users are friends" << endl;
    } else if (network.hasEdge(id1, id2)) {
        cout << username1 + " follows " + username2 << endl;
    } else if (network.hasEdge(id2, id1)) {
        cout << username2 + " follows " + username1 << endl;
    } else {
        cout << "None of the users follow each other" << endl;
    }
}

void emptyNetwork(Graph &network) {
    network.emptyNetwork();
    users.clear();
    usernameToId.clear();
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
            checkFrienshipDegree(network);
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
