#ifndef CART_ITEM_H
#define CART_ITEM_H

#include <deque>
#include <string>

using namespace std;

class CartItem {
 public:
  CartItem(string = "", string = "", int = 0);
  void addAuthor(string);
  string getIsbn();
  string getTitle();
  deque<string> getAuthors();
  int getQuantity();
  float getPrice();
  int getToPublisher();

 private:
  string isbn;
  string title;
  float price;
  deque<string> authors;
  int quantity;
  int toPublisher;
};

#endif
