#include "../include/CartItem.h"

CartItem::CartItem(string isbn, string title, int quantity, float price,
                   int toPublisher)
    : isbn(isbn),
      quantity(quantity),
      title(title),
      price(price),
      toPublisher(toPublisher) {}

void CartItem::addAuthor(string author) { authors.push_back(author); }

string CartItem::getIsbn() { return isbn; }

string CartItem::getTitle() { return title; }

int CartItem::getQuantity() { return quantity; }

float CartItem::getPrice() { return price; }

int CartItem::getToPublisher() { return toPublisher; }

deque<string> CartItem::getAuthors() { return authors; }
