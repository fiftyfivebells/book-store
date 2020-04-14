#include "../include/Cart.h"

Cart::~Cart() {
  for (unsigned long int i; i < items.size(); ++i) {
    delete items[i];
  }
}

void Cart::addItem(CartItem *item) { items.push_front(item); }

void Cart::emptyCart() { items.clear(); }

bool Cart::isEmpty() { return items.size() == 0; }

void Cart::purchaseCart(Database *db, Address *a, Customer *c) { db->makeBookOrder(this, a, c); }

float Cart::calculatePurchase() {
  float amount = 0;

  for (auto it : items) {
    amount += it->getQuantity() * it->getPrice();
  }

  return amount;
}

deque<CartItem *> Cart::getItems() { return items; }
