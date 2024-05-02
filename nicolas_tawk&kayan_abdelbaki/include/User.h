#ifndef USER_H
#define USER_H
#include <vector>
#include <iostream>
using namespace std;

class User {
public:
    //constructor
    User();
    User(const string &, const string &, const string &, const string &);

    //setters
    void setId(int);

    void setUsername(const string &);

    void setFullName(const string &);

    void setEmail(const string &);

    void setPhoneNumber(const string &);

    //getters
    [[nodiscard]] int getId() const;

    [[nodiscard]] string getUsername() const;

    [[nodiscard]] string getFullName() const;

    [[nodiscard]] string getEMail() const;

    [[nodiscard]] string getPhoneNumber() const;

    //additionalMethods

    [[nodiscard]] string toString() const;

    friend ostream &operator<<(ostream &os, const User &user);

    friend istream &operator>>(istream &is, User &user);

private:
    //datafields
    int id;
    string username;
    string fullName;
    string email;
    string phoneNumber;
    static int nextID;
};


#endif
