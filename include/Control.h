#ifndef CONTROL_H
#define CONTROL_H

#include "Cart.h"
#include "Customer.h"
#include "Database.h"
#include "View.h"

class Control {
 public:
  Control() noexcept;
  void launch();
  void bookShopping();
  void addToCart();

 private:
  View view;
  Database db;

};

#endif
