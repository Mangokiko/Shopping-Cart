#include "User.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Constructor
User::User(int id, const std::string& username, const std::string& password, const std::string& email)
    : userId(id), username(username), password(password), email(email), cart(new Cart(id)) {}

// Destructor
User::~User() {
    delete cart;
}

// Authentication Methods
bool User::login(const std::string& inputUsername, const std::string& inputPassword) const {
    if (username == inputUsername && password == inputPassword) {
        std::cout << "Login successful.\n";
        return true;
    }
    std::cerr << "Invalid username or password.\n";
    return false;
}

void User::logout() const {
    std::cout << "User logged out.\n";
}

// Profile Management
void User::updateUsername(const std::string& newUsername) {
    username = newUsername;
    std::cout << "Username updated to: " << username << "\n";
}

void User::updatePassword(const std::string& newPassword) {
    password = newPassword;
    std::cout << "Password updated successfully.\n";
}

void User::updateEmail(const std::string& newEmail) {
    email = newEmail;
    std::cout << "Email updated to: " << email << "\n";
}

// Cart Management
Cart* User::getCart() {
    return cart;
}

// Getters
int User::getUserId() const {
    return userId;
}

std::string User::getUsername() const {
    return username;
}

std::string User::getEmail() const {
    return email;
}

// File Handling Methods
std::vector<User> User::loadUsersFromFile(const std::string& filename) {
    std::vector<User> users;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << "\n";
        return users;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream stream(line);
        int id;
        std::string username, password, email;

        // Parse user details
        stream >> id >> std::ws;
        std::getline(stream, username, ',');
        std::getline(stream, password, ',');
        std::getline(stream, email);

        // Create User object
        users.emplace_back(id, username, password, email);
    }

    file.close();
    return users;
}

void User::saveUsersToFile(const std::string& filename, const std::vector<User>& users) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << "\n";
        return;
    }

    for (const auto& user : users) {
        file << user.getUserId() << " "
             << user.getUsername() << ","
             << "******" /* Hiding password in plaintext */
             << user.getEmail() << "\n";
    }
    file.close();
}
