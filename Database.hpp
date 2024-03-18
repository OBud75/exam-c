#ifndef DATABASE_HPP
#define DATABASE_HPP

#include <unordered_map>
#include <string>
#include <openssl/evp.h> // Pour le hachage SHA256

// classe pour stocker les utilisateurs et leurs mdp
class Database {
private:
    // unordered pour stocker les usernames et leurs mdp
    std::unordered_map<std::string, std::string> users;

    std::string hashPassword(const std::string& password);

public:
    void addUser(const std::string& username, const std::string& password);
    bool authenticate(const std::string& username, const std::string& password);
};

// méthode privée pour hasher le mdp
std::string Database::hashPassword(const std::string& password) {
    // prend un mot de passe en clair en entrée et
    // retourne le mot de passe haché à l'aide de l'algorithme de hachage SHA256 fourni par OpenSSL

    EVP_MD_CTX* mdctx = EVP_MD_CTX_new();
    unsigned char hash[EVP_MAX_MD_SIZE];
    unsigned int hashLen;

    EVP_DigestInit(mdctx, EVP_sha256());
    EVP_DigestUpdate(mdctx, password.c_str(), password.length());
    EVP_DigestFinal(mdctx, hash, &hashLen);

    std::string hashedPassword(reinterpret_cast<char*>(hash), hashLen);

    EVP_MD_CTX_free(mdctx);

    return hashedPassword;
}


// méthodes publiques pour ajouter un utilisateur et vérifier l'authentification
void Database::addUser(const std::string& username, const std::string& password) {
    // prend un nom d'utilisateur et un mot de passe en clair en entrée
    // hache le mot de passe
    // stocke le nom d'utilisateur associé au mot de passe haché dans la base de données

    std::string hashedPassword = hashPassword(password);
    users[username] = hashedPassword;
}
bool Database::authenticate(const std::string& username, const std::string& password) {
    // prend un nom d'utilisateur et un mot de passe en clair en entrée
    // hache le mot de passe et vérifie s'il correspond 
    // au mot de passe haché stocké dans la base de données pour l'utilisateur correspondant
    auto it = users.find(username);
    if (it != users.end()) {
        std::string hashedPassword = hashPassword(password);
        return it->second == hashedPassword;
    }
    return false;
}

#endif // DATABASE_HPP
