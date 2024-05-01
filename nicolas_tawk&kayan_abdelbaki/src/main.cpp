#include "../include/Graph.h"
#include "../include/User.h"
#include <iostream>
#include <unordered_map>
using namespace std;


unordered_map<int, User> users;

int getUserIDByUsername(string username) {
    for (const auto& pair : users) {
        if (pair.second.getUsername() == username) {
            return pair.first;
        }
    }
    return -1;
}
void addUser(Graph network) {
    string username;
    cout << "Enter the name of the user : ";
    cin >> username;
    User user = User(username);

    int id = getUserIDByUsername(username);
    users[id] = user;
    network.addVertex(id);
}

void addConnection(Graph network) {
    string follower, followed;
    cout << "Enter the username of the follower : ";
    cin >> follower;
    cout << "Enter the username of the followed : ";
    cin >> followed;

    int  follower_id = getUserIDByUsername(follower);
    int followed_id = getUserIDByUsername(followed);
    if (follower_id != -1 && followed_id != -1) {
        network.addEdge(follower_id, followed_id);
    }
    else {
        cout << "One or both of the users are not in the network" << endl;
    }

}

void removeConnection(Graph network) {
    string follower, followed;
    cout << "Enter the username of the follower : ";
    cin >> follower;
    cout << "Enter the username of the followed : ";
    cin >> followed;

    int  follower_id = getUserIDByUsername(follower);
    int followed_id = getUserIDByUsername(followed);
}

bool checkConnection(Graph& network, const string& username1, const string& username2) {
    int id1 = getUserIDByUsername(username1);
    int id2 = getUserIDByUsername(username2);
    if (id1 == -1 || id2 == -1) {
        cout << "One or both users do not exist." << endl;
        return false;
    }
    return network.hasEdge(id1, id2);
}

void removeUser(Graph& network, const string& username) {
    int userId = getUserIDByUsername(username);
    if (userId == -1) {
        cout << "User not found." << endl;
        return;
    }
    network.removeVertex(userId);
    users.erase(userId);
    cout << "User removed successfully." << endl;
}

int findDistanceBetweenUsers(Graph& network, const string& username1, const string& username2) {
    int id1 = getUserIDByUsername(username1);
    int id2 = getUserIDByUsername(username2);
    if (id1 == -1 || id2 == -1) {
        cout << "One or both users do not exist." << endl;
        return -1;
    }
    return network.shortestPath(id1, id2);
}

void visualizeNetwork(Graph& network) {
    network.printGraph();
}

void printUserDetails(const string& username) {
    int userId = getUserIDByUsername(username);
    if (userId == -1) {
        cout << "User does not exist." << endl;
        return;
    }
    User user = users[userId];
    cout << "Username: " << user.getUsername() << endl;
    cout << "Email: " << user.getMail() << endl;
    cout << "name: " << user.getName() << endl;
    cout << "last name: " << user.getLastName() << endl;
    cout << "phone number: " << user.getPhoneNumber() << endl;
}




void menu() {
    cout << "Enter a number from 1 to 20" << endl;
    cout << "1: Initialize the network" << endl;
    cout << "2: Add a user to the network " << endl;
    cout << "3: Add a connection to a user" << endl;
    cout << "4: remove a connection from a user" << endl;
    cout << "5: check if a user is connected to another" << endl;
    cout << "6: remove a user from the network" << endl;
    cout << "7: find the distance between two users" << endl;
    cout << "8: illustrate the network" << endl;
    cout << "9: print the details about a user" << endl;
    cout << "10: get the followers of a user" << endl;
    cout << "11: get the followings of a user" << endl;
    cout << "12: traverse the network using BFS" << endl;
    cout << "13: traverse the network using DFS" << endl;

    cout << "14: empty the network" << endl;
    cout << "15: exit" << endl;
}

void handleChoice(Graph network, int choice) {
    switch (choice) {
    case 1:
        cout << "hello";
        break;
    case 2:

        addUser(network);
        break;
    case 3:
        addConnection(network);
        break;
    case 4:
        removeConnection(network);
        break;
    case 5:
        checkConnection(network, "kayan", "nic");
        break;
    case 6:
        cout << "Enter the username of the user you want to remove";

        removeUser(network, "kayan");
        break;
    case 7:
        visualizeNetwork(network);
        break;

    }
}
int main() {
    Graph network = Graph();
    /*
    User alice("alice");
    User bob("bob");
    User sam("sam");

    network.addVertex(1);
    network.addVertex(2);
    network.addVertex(3);

    network.addEdge(1, 2);
    network.addEdge(1, 3);

    network.printGraph();

    network.removeEdge(1, 2);

    network.printGraph();
    */


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




