// main.cpp
#include <iostream>
#include "Database.hpp"

int main() {
    Database db;

    db.addUser("alice", "password1");
    db.addUser("bob", "password2");

    std::cout << "Authentication result for Alice: " << std::boolalpha << db.authenticate("alice", "password1") << std::endl;
    std::cout << "Authentication result for Bob: " << std::boolalpha << db.authenticate("bob", "blabla123") << std::endl;

    return 0;
}
