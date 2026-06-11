#ifndef CART_H
#define CART_H

#include "Product.h"
#include <map>
#include <string>

class Cart {
private:
    int cartId;
    std::map<int, int> items; // Maps productId to quantity

public:
    // Constructor
    Cart(int id);

    // Methods
    void addProduct(const Product& product, int quantity);
    void removeProduct(int productId);
    double calculateTotal(const std::vector<Product>& products) const;
    void viewCart(const std::vector<Product>& products) const;

    // Getters
    int getCartId() const;
};

#endif
