#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <unordered_map>
#include <string>
#include <openssl/evp.h> // Pour le hachage SHA256

// classe pour stocker les utilisateurs et leurs mots de passe
class Database {
private:
    // unordered sert à stocker les utilisateurs et leurs mots de passe
    std::unordered_map<std::string, std::string> users;

    std::string hashPassword(const std::string& password);

public:
    void addUser(const std::string& username, const std::string& password);
    bool authenticate(const std::string& username, const std::string& password);
};

#endif // DATABASE_HPP
