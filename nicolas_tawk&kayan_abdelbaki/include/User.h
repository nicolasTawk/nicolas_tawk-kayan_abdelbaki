#ifndef USER_H
#define USER_H


#include <vector>
#include <iostream>
using namespace std;
class User {

public:

    User(string name, string username, int phoneNumber, string mail, string lastName);
    explicit User(string username);
    [[nodiscard]] string getName() const;
    int getId() const;
    void setName(string name);
    void setId(int id);
    void printUserInfo() const;
    void setEmail(string mail);
    void setPhoneNumber(int number);
    string getMail() const;
    int getPhoneNumber() const;
    string getLastName() const;
    void setLastName(string lastName);
    void setUsername(string username);
    string getUsername() const;

private:
    string username;
    string name;
    string lastName;
    static int nextID;
    int id;
    string mail;
    int phoneNumber;

};

#endif
