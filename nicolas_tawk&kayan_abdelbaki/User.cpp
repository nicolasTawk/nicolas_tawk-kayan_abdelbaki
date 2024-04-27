#include "User.h"
#include <iostream>
#include <vector>
using namespace std;

//we used this static variable in order to keep track of the next id that can be used without duplication
int User::nextID = 1;

User::User(string mail, int phoneNumber, string name, string lastName){
    //auto incrementing the id as we create new objects from the class user
    this->id = nextID++;
    setName(name);
    setEmail(mail);
    setLastName(lastName);
    setPhoneNumber(phoneNumber);
    
}

//getters and setters to the class in order to acess or change private data members exclusevley
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

void User::setEmail(string mail){
    this -> mail = mail;
}

void User::setPhoneNumber(int number){
    phoneNumber = number;
}

string User::getMail(){
    return this -> mail;
}

int User::getPhoneNumber(){
    return this -> phoneNumber;
}

// this set method is there if we want to overload the ids
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
