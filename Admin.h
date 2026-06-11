#ifndef ADMIN_H
#define ADMIN_H

#include "Product.h"
#include "Order.h"
#include <vector>

class Admin {
private:
    std::string adminId;
    std::string password;

public:
    // Constructor
    Admin(const std::string& id, const std::string& password);

    // Product Management
    void addProduct(std::vector<Product>& catalog, const Product& product);
    void updateProduct(std::vector<Product>& catalog, int productId, const std::string& newName, double newPrice, int newStock);
    void deleteProduct(std::vector<Product>& catalog, int productId);

    // Order Management
    void viewAllOrders(const std::vector<Order>& orders, const std::vector<Product>& catalog) const;
    void updateOrderStatus(std::vector<Order>& orders, int orderId, const std::string& newStatus);

    // Reports
    void generateSalesReport(const std::vector<Order>& orders) const;

    // Authentication
    bool login(const std::string& inputId, const std::string& inputPassword) const;
};

#endif
