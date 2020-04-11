#ifndef CONTROL_H
#define CONTROL_H

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
