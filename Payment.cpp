#include "Payment.h"
#include <iostream>

// Constructor definition
Payment::Payment(int id, Order* order, User* user, const std::string& method)
    : paymentId(id), order(order), user(user), paymentMethod(method), status("Pending") {}

// Simulate payment processing
bool Payment::processPayment() {
    std::cout << "Processing payment for Order ID: " << order->getOrderId() << "\n";
    std::cout << "Payment Method: " << paymentMethod << "\n";

    // Simulate payment success/failure
    int randomOutcome = rand() % 2; // Random 0 or 1
    if (randomOutcome == 0) {
        status = "Failed";
        std::cerr << "Payment failed. Please try again.\n";
        order->updateStatus("Pending"); // Notify the order
        return false;
    }

    status = "Completed";
    std::cout << "Payment successful! Thank you for your purchase.\n";
    order->updateStatus("Paid"); // Notify the order
    return true;
}

// Update payment status
void Payment::updateStatus(const std::string& newStatus) {
    status = newStatus;
    std::cout << "Payment status updated to: " << status << "\n";
}

// Get payment details
std::string Payment::getPaymentDetails() const {
    return "Payment ID: " + std::to_string(paymentId) + "\n" +
           "Order ID: " + std::to_string(order->getOrderId()) + "\n" +
           "User: " + user->getUsername() + "\n" +
           "Payment Method: " + paymentMethod + "\n" +
           "Status: " + status + "\n";
}

// Getters
int Payment::getPaymentId() const { return paymentId; }
std::string Payment::getStatus() const { return status; }
