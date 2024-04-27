#include "Graph.h"
#include "User.h"
#include <iostream>
#include <unordered_map>
using namespace std;

int id = 0;
unordered_map<int, User> users;

int getUserIDByName(string name) {
    for (const auto& pair : users) {
        if (pair.second.getName() == name) {
            return pair.first;
        }
    }
    return -1;
}
void addUser(Graph network) {
    string name;
    cout << "Enter the name of the user : ";
    cin >> name;

    users[id] = User(id, name);
    network.addVertex(id);
}

void addConnection(Graph network) {
    string follower, followed;
    cout << "Enter the name of the follower : ";
    cin >> follower;
    cout << "Enter the name of the followed : ";
    cin >> followed;

    int  follower_id = getUserIDByName(follower);
    int followed_id = getUserIDByName(followed);
    if (follower_id != -1 && followed_id != -1) {
        network.addEdge(follower_id, followed_id);
    }
    else {
        cout << "One or both of the users are not in the network" << endl;
    }

}

void removeConnection(Graph network) {
    string follower, followed;
    cout << "Enter the name of the follower : ";
    cin >> follower;
    cout << "Enter the name of the followed : ";
    cin >> followed;

    int  follower_id = getUserIDByName(follower);
    int followed_id = getUserIDByName(followed);
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
    User alice(1, "alice");
    User bob(2, "bob");
    User sam(3, "sam");
    
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




