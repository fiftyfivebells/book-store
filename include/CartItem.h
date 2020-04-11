#ifndef CART_ITEM_H
#define CART_ITEM_H

#include <string>

using namespace std;

class CartItem {
 public:
  CartItem(string="", int=0);

 private:
  string isbn;
  int quantity;
};

#endif
