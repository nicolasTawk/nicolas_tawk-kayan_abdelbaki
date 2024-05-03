#include "../include/Graph.h"
#include "../include/User.h"
#include <iostream>
#include <unordered_map>
using namespace std;


static int nextId = 0; // handling ids in the main class since username is a unique identifier and we only need an int value to work in graphs
unordered_map<int, User> users;  // Maps user IDs to User objects
unordered_map<string, int> usernameToId;  // For fast username lookup

//done
int getUserIdByUsername(const string& username) {
    if (usernameToId.find(username) == usernameToId.end()) {
        return -1; // User not found
    }
    return usernameToId[username];
}


//done
void addUser(  Graph& network) {
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

void addConnection(Graph& network) {
    string follower, followed;
    cout << "Enter the username of the follower : ";
    cin >> follower;
    cout << "Enter the username of the followed : ";
    cin >> followed;
    const int  follower_id = getUserIdByUsername(follower);
    const int followed_id = getUserIdByUsername(followed);
    cout << "follower id" + to_string(follower_id)+ "  followed id: " + to_string(followed_id) << endl;
    if (follower_id != -1 && followed_id != -1) {
        if(network.addEdge(follower_id, followed_id))
            cout << "Frienship link added succcesfully"<<endl;
        else
            cout <<"Failed to add frienship link"<<endl;
    }
    else {
        cout << "One or both of the users are not in the network" << endl;
    }

}

void removeConnection( Graph& network) {
    string follower, followed;
    cout << "Enter the username of the follower : ";
    cin >> follower;
    cout << "Enter the username of the followed : ";
    cin >> followed;

    int  follower_id = getUserIdByUsername(follower);
    int followed_id = getUserIdByUsername(followed);
    if (follower_id != -1 && followed_id != -1) {
        if(network.removeEdge(follower_id, followed_id))
            cout << "Frienship link removed succcesfully"<<endl;
        else
            cout <<"Failed to remove frienship link"<<endl;
    }
    else {
        cout << "One or both of the users are not in the network" << endl;
    }
}

bool checkConnection(Graph& network) {
     string follower, followed;
    cout << "Enter the username of the follower : ";
    cin >> follower;
    cout << "Enter the username of the followed : ";
    cin >> followed;
    int id1 = getUserIdByUsername(follower);
    int id2 = getUserIdByUsername(followed);
    if (id1 == -1 || id2 == -1) {
        cout << "One or both users do not exist." << endl;
        return false;
    }
    return network.hasEdge(id1, id2);
}

void removeUser(Graph& network) {
    string username;
    cout << "Enter the username of the user you want to remove: ";
    cin>> username;
    int userId = getUserIdByUsername(username);
    if (userId == -1) {
        cout << "User not found." << endl;
        return;
    }
    network.removeVertex(userId);
    users.erase(userId);
    usernameToId.erase(username);
    cout << "User removed successfully." << endl;
}

// int findDistanceBetweenUsers(Graph& network, const string& username1, const string& username2) {
//     int id1 = getUserIDByUsername(username1);
//     int id2 = getUserIDByUsername(username2);
//     if (id1 == -1 || id2 == -1) {
//         cout << "One or both users do not exist." << endl;
//         return -1;
//     }
//     return network.shortestPath(id1, id2);
// }


void visualiseNetwork(Graph& network) {
    for (const auto &vertex: network.getVertices()) {
        cout <<"("+ to_string(vertex.id)+ ":" + users[vertex.id].getUsername()+")" << "->";
        for (const auto &edge: vertex.adjacencyList) {
            cout << "("+ to_string(edge.dest)+ ":" + users[edge.dest].getUsername()+")" << "->";
        }
        cout << "null" <<endl;
        cout << "|\n";
    }
    cout <<"null"<<endl;
}

void printUserDetails(const string& username) {
    const int userId = getUserIdByUsername(username);
    if (userId == -1) {
        cout << "User does not exist." << endl;
        return;
    }
    const User user = users[userId];
    cout << user;
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
    cout << "10: check if a user follows another " << endl;
    cout << "11: get the followers of a user" << endl;
    cout << "12: get the followings of a user" << endl;
    cout << "13: find the number of possible ways we can go from one user to another in x hoops"<<endl;
    cout << "14: find the most popular user"<< endl;
    cout << "15: check if two users are friends" << endl;
    cout << "16: list the mutuals of two users" << endl;
    cout << "17: empty the network" << endl;
    cout << "18: exit" << endl;
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



    case 7:

        break;

    }
}
int main() {
    Graph network = Graph();

    // addUser(network);
    // addUser(network);
    // addConnection(network);
    // visualizeNetworkUsingIds(network);
    int choice;
    do {
        menu();
        cin >> choice;
        while (choice < 1 || choice > 15) {
            cout << "Make sure the number is between 1 and 15 inclusively" << endl;
            cin >> choice;
        }
         handleChoice(network, choice);

    } while (choice != 15);


    return 0;
}




