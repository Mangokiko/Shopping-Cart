#include <iostream>
#include <vector>
#include "Product.h"
#include "User.h"
#include "Order.h"
#include "Payment.h"
#include "Admin.h"

int main() {
    // Initialize catalog
    std::vector<Product> catalog = {
        Product(1, "Laptop", 999.99, 10),
        Product(2, "Smartphone", 499.99, 25),
        Product(3, "Tablet", 299.99, 15),
        Product(4, "Headphones", 99.99, 50),
    };

    // Initialize users and admin
    std::vector<User*> users;
    Admin admin("admin123", "adminpass");

    // Load existing orders (if applicable)
    std::vector<Order> orders = Order::loadOrdersFromFile("orders.txt", users);

    int choice;
    do {
        // Main menu
        std::cout << "\n==========================\n";
        std::cout << "Welcome to Online Shopping\n";
        std::cout << "==========================\n";
        std::cout << "1. Create Account\n";
        std::cout << "2. Login as Customer\n";
        std::cout << "3. Login as Admin\n";
        std::cout << "4. Exit\n";
        std::cout << "Enter your choice: ";
        std::cin >> choice;

        if (choice == 1) {
            // Create Account
            std::string username, password, email;
            std::cout << "Enter Username: ";
            std::cin >> username;
            std::cout << "Enter Password: ";
            std::cin >> password;
            std::cout << "Enter Email: ";
            std::cin >> email;

            int userId = users.empty() ? 1 : users.back()->getUserId() + 1;
            User* newUser = new User(userId, username, password, email);
            users.push_back(newUser);

            std::cout << "Account created successfully! Your User ID is " << userId << ".\n";
        } else if (choice == 2) {
            // Customer Login
            int userId;
            std::cout << "Enter your User ID: ";
            std::cin >> userId;

            User* currentUser = nullptr;
            for (auto* user : users) {
                if (user->getUserId() == userId) {
                    currentUser = user;
                    break;
                }
            }

            if (currentUser) {
                std::cout << "Welcome, " << currentUser->getUsername() << "!\n";

                int customerChoice;
                do {
                    std::cout << "\nCustomer Menu:\n";
                    std::cout << "1. View Products\n";
                    std::cout << "2. Place Order\n";
                    std::cout << "3. View My Orders\n";
                    std::cout << "4. Make Payment\n";
                    std::cout << "5. Logout\n";
                    std::cout << "Enter your choice: ";
                    std::cin >> customerChoice;

                    if (customerChoice == 1) {
                        // View Products
                        std::cout << "\nProduct Catalog:\n";
                        for (const auto& product : catalog) {
                            std::cout << "Product ID: " << product.getProductId()
                                      << ", Name: " << product.getName()
                                      << ", Price: $" << product.getPrice()
                                      << ", Stock: " << product.getStock() << "\n";
                        }
                    } else if (customerChoice == 2) {
                        // Place Order
                        std::vector<std::pair<int, int>> items;
                        int productId, quantity;

                        while (true) {
                            std::cout << "Enter Product ID (or -1 to finish): ";
                            std::cin >> productId;

                            if (productId == -1)
                                break;

                            std::cout << "Enter Quantity: ";
                            std::cin >> quantity;

                            items.emplace_back(productId, quantity);
                        }

                        double totalAmount = 0.0;
                        for (const auto& [id, qty] : items) {
                            for (const auto& product : catalog) {
                                if (product.getProductId() == id) {
                                    totalAmount += product.getPrice() * qty;
                                    break;
                                }
                            }
                        }

                        int orderId = orders.empty() ? 101 : orders.back().getOrderId() + 1;
                        orders.emplace_back(orderId, currentUser, items, totalAmount);
                        std::cout << "Order placed successfully! Order ID: " << orderId << "\n";
                    } else if (customerChoice == 3) {
                        // View My Orders
                        // View My Orders
                        std::cout << "\nYour Orders:\n";
                        for (const auto& order : orders) {
                            if (order.getUser()->getUserId() == currentUser->getUserId()) {
                                std::cout << order.getOrderDetails(catalog) << "\n";
                            }
                        }

                    } else if (customerChoice == 4) {
                        // Make Payment
                        int orderId;
                        std::cout << "Enter Order ID to process payment: ";
                        std::cin >> orderId;

                        Order* orderToPay = nullptr;
                        for (auto& order : orders) {
                            if (order.getOrderId() == orderId &&
                                order.getUser()->getUserId() == currentUser->getUserId()) {
                                orderToPay = &order;
                                break;
                            }
                        }

                        if (orderToPay) {
                            Payment payment(1, orderToPay, currentUser, "Credit Card");
                            if (payment.processPayment()) {
                                std::cout << "Payment processed successfully.\n";
                            } else {
                                std::cerr << "Payment failed.\n";
                            }
                        } else {
                            std::cerr << "Order not found.\n";
                        }
                    }
                } while (customerChoice != 5);
            } else {
                std::cerr << "Invalid User ID.\n";
            }
        } else if (choice == 3) {
            // Admin Login
            std::string adminId, password;
            std::cout << "Enter Admin ID: ";
            std::cin >> adminId;
            std::cout << "Enter Password: ";
            std::cin >> password;

            if (admin.login(adminId, password)) {
                int adminChoice;
                do {
                    std::cout << "\nAdmin Menu:\n";
                    std::cout << "1. View Products\n";
                    std::cout << "2. View All Orders\n";
                    std::cout << "3. Generate Sales Report\n";
                    std::cout << "4. Logout\n";
                    std::cout << "Enter your choice: ";
                    std::cin >> adminChoice;

                    if (adminChoice == 1) {
                        // View Products
                        std::cout << "\nProduct Catalog:\n";
                        for (const auto& product : catalog) {
                            std::cout << "Product ID: " << product.getProductId()
                                      << ", Name: " << product.getName()
                                      << ", Price: $" << product.getPrice()
                                      << ", Stock: " << product.getStock() << "\n";
                        }
                    } else if (adminChoice == 2) {
                        // View All Orders
                        std::cout << "\nAll Orders:\n";
                        for (const auto& order : orders) {
                            std::cout << order.getOrderDetails(catalog) << "\n";
                        }
                    } else if (adminChoice == 3) {
                        // Generate Sales Report
                        double totalRevenue = 0;
                        int totalProductsSold = 0;

                        for (const auto& order : orders) {
                            totalRevenue += order.getTotalAmount();
                            for (const auto& [productId, quantity] : order.getItems()) {
                                totalProductsSold += quantity;
                            }
                        }

                        std::cout << "\nSales Report:\n";
                        std::cout << "Total Revenue: $" << totalRevenue << "\n";
                        std::cout << "Total Products Sold: " << totalProductsSold << "\n";
                    }
                } while (adminChoice != 4);
            } else {
                std::cerr << "Invalid Admin credentials.\n";
            }
        }
    } while (choice != 4);

    // Save updated orders to file
    Order::saveOrdersToFile("orders.txt", orders);

    std::cout << "Goodbye!\n";
    return 0;
}
