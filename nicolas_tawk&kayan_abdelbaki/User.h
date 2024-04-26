#include <vector>
#include <iostream>
using namespace std;
class User {

public:

    User(int id, string name);

    string getName();
    int getId();
    vector<User*> getConnections();
    void setName(string name);
    void setId(int id);
    void addConnection(User* user);
    void removeConnection(User* user);
    void printUserInfo() const;

private:
    string name;
    int id;
    vector<User*> connections;
};
