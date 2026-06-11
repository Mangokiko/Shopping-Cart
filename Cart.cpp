#include "Cart.h"
#include <iostream>
#include <iomanip>

// Constructor
Cart::Cart(int id) : cartId(id) {}

// Add a product to the cart
void Cart::addProduct(const Product& product, int quantity) {
    if (quantity <= 0) {
        std::cerr << "Quantity must be greater than zero.\n";
        return;
    }
    if (items.find(product.getProductId()) != items.end()) {
        items[product.getProductId()] += quantity;
    } else {
        items[product.getProductId()] = quantity;
    }
    std::cout << quantity << " x " << product.getName() << " added to the cart.\n";
}

// Remove a product from the cart
void Cart::removeProduct(int productId) {
    if (items.erase(productId)) {
        std::cout << "Product removed from the cart.\n";
    } else {
        std::cerr << "Product not found in the cart.\n";
    }
}

// Calculate the total cost of items in the cart
double Cart::calculateTotal(const std::vector<Product>& products) const {
    double total = 0.0;

    for (const auto& [productId, quantity] : items) {
        for (const auto& product : products) {
            if (product.getProductId() == productId) {
                total += product.getPrice() * quantity;
                break;
            }
        }
    }

    return total;
}

// View all items in the cart
void Cart::viewCart(const std::vector<Product>& products) const {
    if (items.empty()) {
        std::cout << "Your cart is empty.\n";
        return;
    }

    std::cout << "Items in your cart:\n";
    for (const auto& [productId, quantity] : items) {
        for (const auto& product : products) {
            if (product.getProductId() == productId) {
                std::cout << "- " << product.getName()
                          << " x" << quantity
                          << " ($" << std::fixed << std::setprecision(2)
                          << product.getPrice() * quantity << ")\n";
                break;
            }
        }
    }

    double total = calculateTotal(products);
    std::cout << "Total: $" << std::fixed << std::setprecision(2) << total << "\n";
}

// Get the cart ID
int Cart::getCartId() const {
    return cartId;
}
