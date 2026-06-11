# Shopping-Cart
A C++ object-oriented online shopping cart system featuring user authentication, product management, shopping carts, order processing, payment simulation, and admin reporting.
Hi, this is my project a while back in 2023 "Shopping cart", let go through explainning how it work.
Warning, once you run the code and want to close it. Make sure exist correctly or exist terminal out all he way or not. If you run the code again
while it not exist correctly, you will stuck in loop.

User Function:
-it create username, password, emails and roles (admin or customer)
-It will set acount admin or customer then then send it to Admin Function or Customer Function
-There already two account exist, one for customer and one admin
-Customer Username: lephuc, Password: 123
-Admin Username: phucle, Password:123
-But you could create your own account if you want.

Customer Function:
-Set User as a customer
-allow user to go Shopping
-buy items
-remove items
-check out
-view order history

Admin Function:
-Set User as an admin
-allow user to add new items
-manage the stocks, remove, add or update it

Order Function:
-Manage order items from customer and setup order items like id, name, amount and cost

Payment Function:
-Just set option for customer to choose option for Payment
NOTE: there wont be any money set for customer at all since am not exactly understand how I would set money for customer 

Main Function:
-Setup a display function to run everything

ShoppingCart Function:
-Handling product for customer card
-Whenever they add or remove items in their cart.
-Check total money.

If you run code and stuck in loop, this because you didn't exits code running earlier correctly. Just run again
Hope you enjoy my project.
## Compilation Instructions

Compile the project using g++:

```bash
g++ main.cpp User.cpp Product.cpp Cart.cpp Order.cpp Payment.cpp Admin.cpp -o shoppingcart
