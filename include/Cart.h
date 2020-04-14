#ifndef CART_H
#define CART_H

#include <deque>
#include "Address.h"
#include "CartItem.h"
#include "Database.h"

using namespace std;

// forward declare
class Database;

class Cart {
 public:
  ~Cart();
  void emptyCart();
  bool isEmpty();
  void addItem(CartItem *);
  void purchaseCart(Database *, Address *, Customer *);
  float calculatePurchase();
  deque<CartItem *> getItems();

 private:
  deque<CartItem *> items;
};

#endif
