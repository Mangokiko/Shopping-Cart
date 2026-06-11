#ifndef ORDER_H
#define ORDER_H

#include "User.h"
#include <vector>
#include <string>
#include <utility> // For std::pair

class Order {
private:
    int orderId;
    User* user; // Associated user for the order
    std::vector<std::pair<int, int>> items; // Vector of (productId, quantity)
    double totalAmount;
    std::string status;

public:
    // Constructor
    Order(int id, User* user, const std::vector<std::pair<int, int>>& items, double totalAmount);

    // Methods
    std::string getOrderDetails(const std::vector<Product>& catalog) const;
    std::string trackStatus() const;
    void updateStatus(const std::string& newStatus);

    // Getter for items
    const std::vector<std::pair<int, int>>& getItems() const;

    // Getters
    int getOrderId() const;
    double getTotalAmount() const;
    User* getUser() const;
    

    // File Handling
    static std::vector<Order> loadOrdersFromFile(const std::string& filename, const std::vector<User*>& users);
    static void saveOrdersToFile(const std::string& filename, const std::vector<Order>& orders);

    friend class Payment; // Payment class can access private members if needed
};

#endif // ORDER_H
