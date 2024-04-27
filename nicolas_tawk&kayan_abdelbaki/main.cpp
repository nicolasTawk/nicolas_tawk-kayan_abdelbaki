#include "Graph.h"
#include "User.h"
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
    users[id] = user ;
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

void menu() {
    cout << "Enter a number from 1 to 20" << endl;
    cout << "1: Initialize the network" << endl;
    cout << "1: Add a user to the network " << endl;
    cout << "2: Add a connection to a user" << endl;
    cout << "3: remove a connection from a user" << endl;
    cout << "4: check if a user is connected to another" << endl;
    cout << "5: remove a user from the network" << endl;
    cout << "6: find the distance between two users" << endl;
    cout << "7: illustrate the network" << endl;
    cout << "8: print the details about a user" << endl;
    cout << "9: get the followers of a user" << endl;
    cout << "10: get the followings of a user" << endl;
    cout << "11: traverse the network using BFS" << endl;
    cout << "12: traverse the network using DFS" << endl;

    cout << "11: empty the network" << endl;
    cout << "12: exit" << endl;
}

void handleChoice(Graph network, int choice) {
    switch (choice) {
    case 1:
        cout << "hello";
        // addUser(network);
    }
}
int main() {
    Graph network =  Graph();
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
   

    int choice;
    do {
        menu();
        cin >> choice;
        while (choice < 1 || choice > 12) {
            cout << "Make sure the number is between 1 and 12 inclusively" << endl;
            cin >> choice;
        }
       // handleChoice(choice);
        
    }while (choice != 12);


    return 0;
}




