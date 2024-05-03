#include "../include/User.h"
#include <iostream>
#include <vector>
using namespace std;

//we used this static variable in order to keep track of the next id that can be used without duplication
int User::nextID = 0;
User::User() : username("Unknown") {this->id = nextID++;}
User::User(const string& username , const string &fullName = "", const string& email = "", const string& phoneNumber = "") {
    //auto incrementing the id as we create new objects from the class user
    this->id = nextID++;
    setUsername(username);
    setFullName(fullName);
    setEmail(email);
    setPhoneNumber(phoneNumber);

}

//getters

int User::getId() const {
    return id;
}
string User::getUsername() const {
    return username;
}
string User::getFullName() const {
    return fullName;
}

string User::getEMail() const {
    return this->email;
}
string User::getPhoneNumber() const {
    return this->phoneNumber;
}

//setters
void User::setUsername(const string &username) {
    this->username = username;
}

void User::setFullName(const string &fullName) {
    this->fullName = fullName;
}

void User::setEmail(const string &email) {
    this->email = email;
}

void User::setPhoneNumber(const string &phoneNumber) {
    this->phoneNumber = phoneNumber;
}

// this set method is there if we want to overload the ids
void User::setId(int id) {
    this->id = id;
}

// int getUserIDByUsername() {
//
// }

std::string User::toString() const {
    return "Username: " + username + ", Full Name: " + fullName +
           ", Email: " + email + ", Phone Number: " + phoneNumber;
}

std::ostream& operator<<(std::ostream& os, const User& user) {
    os << user.toString();
    return os;
}

istream &operator>>(istream &is, User &user) {

    cout << " Enter username: ";
    is >> user.username;
    cout << "Enter full name: ";
    // is.ignore(); // Ignore newline leftover in the stream
    // getline(is, user.fullName);
    is >> user.fullName;
    cout << "Enter email: ";
    is >> user.email;
    cout << "Enter phone number: ";
    is >> user.phoneNumber;

    return is;
}


// int main() {
//     // Creating a User with default constructor and setting values using setters
//     User user1;
//     user1.setUsername("johnsmith");
//     user1.setFullName("John Smith");
//     user1.setEmail("john.smith@example.com");
//     user1.setPhoneNumber("1234567890");
//
//     // Display using overloaded output operator
//     cout << "User 1 details:\n" << user1 << endl;
//
//     // Testing input for a new user
//     User user2;
//     cout << "Please enter user 2 details:" << endl;
//     cin >> user2;
//
//     // Displaying the entered data
//     cout << "User 2 details:\n" << user2 << endl;
//
//     // Demonstrating getter methods
//     cout << "Accessing User 2 Details Individually:" << endl;
//     cout << "ID: " << user2.getId() << endl;
//     cout << "Username: " << user2.getUsername() << endl;
//     cout << "Full Name: " << user2.getFullName() << endl;
//     cout << "Email: " << user2.getEMail() << endl;
//     cout << "Phone Number: " << user2.getPhoneNumber() << endl;
//
//     return 0;
// }