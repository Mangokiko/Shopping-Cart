#include "Product.h"
#include <fstream>
#include <iostream>
#include <sstream>

// Constructor
Product::Product(int id, const std::string& name, double price, int stock)
    : productId(id), name(name), price(price), stock(stock) {}

// Getters and Setters (unchanged from before)
int Product::getProductId() const { return productId; }
std::string Product::getName() const { return name; }
double Product::getPrice() const { return price; }
int Product::getStock() const { return stock; }
void Product::setName(const std::string& newName) { name = newName; }
void Product::setPrice(double newPrice) { price = newPrice; }
void Product::setStock(int newStock) { stock = newStock; }

// Methods (unchanged from before)
void Product::addStock(int amount) { stock += amount; }
bool Product::reduceStock(int amount) {
    if (stock >= amount) {
        stock -= amount;
        return true;
    }
    return false;
}
std::string Product::getDetails() const {
    std::ostringstream details;
    details << "Product ID: " << productId << "\n"
            << "Name: " << name << "\n"
            << "Price: $" << price << "\n"
            << "Stock: " << stock;
    return details.str();
}

// File Handling Methods
std::vector<Product> Product::loadProductsFromFile(const std::string& filename) {
    std::vector<Product> products;
    std::ifstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << "\n";
        return products;
    }

    std::string line;
    while (std::getline(file, line)) {
        std::istringstream stream(line);
        int id, stock;
        double price;
        std::string name;

        // Parse product details
        stream >> id >> std::ws;
        std::getline(stream, name, ',');
        stream >> price >> stock;

        // Create and add Product object
        products.emplace_back(id, name, price, stock);
    }

    file.close();
    return products;
}

void Product::saveProductsToFile(const std::string& filename, const std::vector<Product>& products) {
    std::ofstream file(filename);

    if (!file.is_open()) {
        std::cerr << "Error: Unable to open file " << filename << "\n";
        return;
    }

    for (const auto& product : products) {
        file << product.getProductId() << " "
             << product.getName() << ","
             << product.getPrice() << " "
             << product.getStock() << "\n";
    }

    file.close();
}
