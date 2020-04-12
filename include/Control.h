#ifndef CONTROL_H
#define CONTROL_H

#include "Cart.h"
#include "Customer.h"
#include "Database.h"
#include "View.h"

class Control {
 public:
  Control() noexcept;
  ~Control();
  void launch();
  void bookShopping();
  void addToCart();
  void showCartOperations();
  void completePurchase();
  void emptyCart();
  void logInUser(Customer **);
  void registerUser(Customer **);
  void createAddress(Address **);

 private:
  Cart cart;
  View view;
  Database db;
};

#endif
