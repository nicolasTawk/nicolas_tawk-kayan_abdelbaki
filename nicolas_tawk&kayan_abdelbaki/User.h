#include <vector>
#include <iostream>
using namespace std;
class User {

public:

    User(string mail, int phoneNumber, string name, string lastName);

    string getName();
    int getId();
    vector<User*> getConnections();
    void setName(string name);
    void setId(int id);
    void addConnection(User* user);
    void removeConnection(User* user);
    void printUserInfo() const;
    void setEmail(string mail);
    void setPhoneNumber(int number);
    string getMail();
    int getPhoneNumber();
    string getLastName();
    void setLastName(string lastName);
  

private:
    string name;
    string lastName;
    static int nextID;
    int id;
    string mail;
    int phoneNumber;
    vector<User*> connections;
};
