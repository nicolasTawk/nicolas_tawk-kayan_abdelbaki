#include "Graph.h"
#include <iostream>
using namespace std;

void menu() {
    cout << "Enter a number from 1 to 20" << endl;
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

    cout << "11: empty the network" << endl;
    cout << "12: exit" << endl;
}

void handleChoice(int choice) {
    switch (choice) {
    case 1:
        cout << "hello";
        //addUser();
    }
}

void addUser() {
    string name;
    cout << "Enter the name of the user : ";
    cin >> name;

}

int main() {

    Graph network(10);
    Graph g(3); // Create a graph with 3 vertices initially
    g.addEdge(0, 1); // Connect vertex 0 and 1

    // Adding a new isolated vertex
    g.addVertex(); // This will be vertex 3
    g.addVertex(); // This will be vertex 4 (also isolated)

    g.printGraph(); // Display the graph



    int choice;
    do {
        menu();
        cin >> choice;
        while (choice < 1 || choice > 12) {
            cout << "Make sure the number is between 1 and 12 inclusively" << endl;
            cin >> choice;
        }
        // handleChoice(choice);

    } while (choice != 12);


    return 0;
}
