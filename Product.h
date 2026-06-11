#ifndef PRODUCT_H
#define PRODUCT_H

#include <string>
#include <vector>

class Product {
private:
    int productId;
    std::string name;
    double price;
    int stock;

public:
    // Constructor
    Product(int id, const std::string& name, double price, int stock);

    // Getters and Setters (unchanged from before)
    int getProductId() const;
    std::string getName() const;
    double getPrice() const;
    int getStock() const;
    void setName(const std::string& name);
    void setPrice(double price);
    void setStock(int stock);

    // Methods
    void addStock(int amount);
    bool reduceStock(int amount);
    std::string getDetails() const;

    // File Handling
    static std::vector<Product> loadProductsFromFile(const std::string& filename);
    static void saveProductsToFile(const std::string& filename, const std::vector<Product>& products);
};

#endif // PRODUCT_H
