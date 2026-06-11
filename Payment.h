#ifndef PAYMENT_H
#define PAYMENT_H

#include "Order.h"
#include <string>

class Payment {
private:
    int paymentId;
    Order* order; // Associated order
    User* user;   // Associated user
    std::string paymentMethod;
    std::string status;

public:
    // Constructor
    Payment(int id, Order* order, User* user, const std::string& method);

    // Methods
    bool processPayment();
    void updateStatus(const std::string& newStatus);
    std::string getPaymentDetails() const;

    // Getters
    int getPaymentId() const;
    std::string getStatus() const;
};

#endif // PAYMENT_H
