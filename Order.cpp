#include "Order.h"
#include <fstream>
#include <iostream>
#include <sstream>
#include <iomanip> // For formatting output

// Constructor
Order::Order(int id, User* user, const std::vector<std::pair<int, int>>& items, double totalAmount)
    : orderId(id), user(user), items(items), totalAmount(totalAmount), status("Pending") {}

// Get order details
std::string Order::getOrderDetails(const std::vector<Product>& catalog) const {
    std::ostringstream details;
    details << "Order ID: " << orderId << "\n";
    details << "Status: " << status << "\n";
    details << "Items:\n";

    for (const auto& [productId, quantity] : items) {
        for (const auto& product : catalog) {
            if (product.getProductId() == productId) {
                details << "- " << product.getName() << " x" << quantity
                        << " ($" << product.getPrice() * quantity << ")\n";
                break;
            }
        }
    }

    details << "Total Amount: $" << totalAmount << "\n";
    return details.str();
}


// Track order status
std::string Order::trackStatus() const {
    return "Order Status: " + status;
}

// Update order status
void Order::updateStatus(const std::string& newStatus) {
    status = newStatus;
}

// Getter for items
const std::vector<std::pair<int, int>>& Order::getItems() const {
    return items;
}

// Getter for orderId
int Order::getOrderId() const {
    return orderId;
}

// Getter for totalAmount
double Order::getTotalAmount() const {
    return totalAmount;
}

User* Order::getUser() const {
    return user;
}

// Load orders from file
std::vector<Order> Order::loadOrdersFromFile(const std::string& filename, const std::vector<User*>& users) {
    std::vector<Order> orders;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << "\n";
        return orders;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream stream(line);
        int orderId, userId;
        double totalAmount;
        std::string status;

        // Parse order details
        stream >> orderId >> userId >> totalAmount >> std::ws;
        std::getline(stream, status, ',');

        // Parse items
        std::vector<std::pair<int, int>> items;
        std::string itemsLine;
        std::getline(stream, itemsLine);
        std::istringstream itemsStream(itemsLine);

        int productId, quantity;
        while (itemsStream >> productId >> quantity) {
            items.emplace_back(productId, quantity);
        }

        // Find associated user
        User* associatedUser = nullptr;
        for (auto user : users) {
            if (user->getUserId() == userId) {
                associatedUser = user;
                break;
            }
        }

        if (associatedUser) {
            orders.emplace_back(orderId, associatedUser, items, totalAmount);
            orders.back().updateStatus(status); // Restore status
        } else {
            std::cerr << "Error: User ID " << userId << " not found.\n";
        }
    }

    file.close();
    return orders;
}

// Save orders to file
void Order::saveOrdersToFile(const std::string& filename, const std::vector<Order>& orders) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << "\n";
        return;
    }

    for (const auto& order : orders) {
        file << order.getOrderId() << " "
             << order.user->getUserId() << " "
             << order.getTotalAmount() << " "
             << order.status << ",";

        for (const auto& [productId, quantity] : order.items) {
            file << productId << " " << quantity << " ";
        }
        file << "\n";
    }

    file.close();
}
