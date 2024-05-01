#include "../include/User.h"
#include <iostream>
#include <vector>
using namespace std;

//we used this static variable in order to keep track of the next id that can be used without duplication
int User::nextID = 1;



User::User(string name, string username = "", int phoneNumber = 0, string mail = "", string lastName = "") {
    //auto incrementing the id as we create new objects from the class user
    this->id = nextID++;
    setName(name);
    setEmail(mail);
    setLastName(lastName);
    setPhoneNumber(phoneNumber);
    setUsername(username);

}

User::User(string username) {
    this->id = nextID++;
    setName("");
    setEmail("");
    setLastName("");
    setPhoneNumber(0);
    setUsername(username);
}

//getters and setters to the class in order to acess or change private data members exclusevley
string User::getName() const {
    return name;
}

string User::getUsername() const {
    return username;
}

void User::setUsername(string username) {
    this->username = username;
}

void User::setLastName(string lastName) {
    this->lastName = lastName;
}

string User::getLastName() const {
    return lastName;
}

int User::getId() const {
    return id;
}

void User::setName(string name) {
    this->name = name;
}

void User::setEmail(string mail) {
    this->mail = mail;
}

void User::setPhoneNumber(int number) {
    phoneNumber = number;
}

string User::getMail() const {
    return this->mail;
}

int User::getPhoneNumber() const {
    return this->phoneNumber;
}

// this set method is there if we want to overload the ids
void User::setId(int id) {
    this->id = id;
}

void User::printUserInfo() const {
    cout << "User ID: " << id << ", Name: " << name << std::endl;
    cout << "Connections: ";
    for (auto& connection : connections) {
        cout << connection->name << " ";
    }
    cout << endl;
}
