#include "Admin.h"
#include <iostream>
#include <iomanip>
#include <algorithm>

// Constructor
Admin::Admin(const std::string& id, const std::string& password)
    : adminId(id), password(password) {}

// Product Management
void Admin::addProduct(std::vector<Product>& catalog, const Product& product) {
    catalog.push_back(product);
    std::cout << "Product added successfully: " << product.getName() << "\n";
}

void Admin::updateProduct(std::vector<Product>& catalog, int productId, const std::string& newName, double newPrice, int newStock) {
    for (auto& product : catalog) {
        if (product.getProductId() == productId) {
            product.setName(newName);
            product.setPrice(newPrice);
            product.setStock(newStock);
            std::cout << "Product updated successfully: " << product.getName() << "\n";
            return;
        }
    }
    std::cerr << "Error: Product with ID " << productId << " not found.\n";
}

void Admin::deleteProduct(std::vector<Product>& catalog, int productId) {
    auto it = std::remove_if(catalog.begin(), catalog.end(),
                             [productId](const Product& product) { return product.getProductId() == productId; });

    if (it != catalog.end()) {
        catalog.erase(it, catalog.end());
        std::cout << "Product with ID " << productId << " deleted successfully.\n";
    } else {
        std::cerr << "Error: Product with ID " << productId << " not found.\n";
    }
}

// Order Management
void Admin::viewAllOrders(const std::vector<Order>& orders, const std::vector<Product>& catalog) const {
    if (orders.empty()) {
        std::cout << "No orders available.\n";
        return;
    }

    std::cout << "All Orders:\n";
    for (const auto& order : orders) {
        std::cout << order.getOrderDetails(catalog) << "\n";
    }
}

void Admin::updateOrderStatus(std::vector<Order>& orders, int orderId, const std::string& newStatus) {
    for (auto& order : orders) {
        if (order.getOrderId() == orderId) {
            order.updateStatus(newStatus);
            return;
        }
    }
    std::cerr << "Error: Order with ID " << orderId << " not found.\n";
}

// Reports
void Admin::generateSalesReport(const std::vector<Order>& orders) const {
    if (orders.empty()) {
        std::cout << "No orders available for reporting.\n";
        return;
    }

    double totalRevenue = 0;
    int totalProductsSold = 0;

    for (const auto& order : orders) {
        totalRevenue += order.getTotalAmount();
        for (const auto& [productId, quantity] : order.getItems()) {
            totalProductsSold += quantity;
        }
    }

    std::cout << "Sales Report:\n";
    std::cout << "--------------------------\n";
    std::cout << "Total Revenue: $" << std::fixed << std::setprecision(2) << totalRevenue << "\n";
    std::cout << "Total Products Sold: " << totalProductsSold << "\n";
}


// Authentication
bool Admin::login(const std::string& inputId, const std::string& inputPassword) const {
    if (adminId == inputId && password == inputPassword) {
        std::cout << "Admin login successful.\n";
        return true;
    }
    std::cerr << "Admin login failed. Invalid credentials.\n";
    return false;
}
