#ifndef CONTROL_H
#define CONTROL_H

#include "Cart.h"
#include "Customer.h"
#include "Database.h"
#include "View.h"

class Control {
 public:
  Control(Database *) noexcept;
  ~Control();
  void launch();

 private:
  Cart cart;
  View view;
  Database *db;
  Customer *user;
  Owner *owner;

  void bookShopping();
  void addToCart();
  void showCartOperations();
  void completePurchase();
  void emptyCart();
  void logInUser(Customer **);
  void registerUser(Customer **);
  void createAddress(Address **);
};

#endif
