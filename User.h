#ifndef USER_H
#define USER_H

#include "Cart.h"
#include <string>
#include <vector>

class User {
private:
    int userId;
    std::string username;
    std::string password; // Password remains private
    std::string email;
    Cart* cart; // Each user has an associated cart

public:
    // Constructor
    User(int id, const std::string& username, const std::string& password, const std::string& email);

    // Destructor
    ~User();

    // Authentication Methods
    bool login(const std::string& inputUsername, const std::string& inputPassword) const;
    void logout() const;

    // Profile Management
    void updateUsername(const std::string& newUsername);
    void updatePassword(const std::string& newPassword);
    void updateEmail(const std::string& newEmail);

    // Cart Management
    Cart* getCart();

    // Getters
    int getUserId() const;
    std::string getUsername() const;
    std::string getEmail() const;

    // File Handling
    static std::vector<User> loadUsersFromFile(const std::string& filename);
    static void saveUsersToFile(const std::string& filename, const std::vector<User>& users);
};

#endif // USER_H
