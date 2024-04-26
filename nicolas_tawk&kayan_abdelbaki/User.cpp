#include "User.h"
#include <iostream>
#include <vector>
using namespace std;

User::User(int id, string name) {
	this->id = id;
	this->name = name;
}

string User::getName() {
	return name;
}

int User::getId() {
	return id;
}

std::vector<User*> User::getConnections() {
	return connections;
}

void User::setName(string name) {
	this->name = name;
}

void User::setId(int id) {
	this->id = id;
}

void User::addConnection(User* user) {
	connections.push_back(user);
}

void User::removeConnection(User* user) {
	auto newEnd = remove(connections.begin(), connections.end(), user);
	connections.erase(newEnd, connections.end());
}

void User::printUserInfo() const {
	cout << "User ID: " << id << ", Name: " << name << std::endl;
	cout << "Connections: ";
	for (auto& connection : connections) {
			cout << connection->name << " ";
		}
		cout << endl;
	}
