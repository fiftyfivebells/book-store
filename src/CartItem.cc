#include "../include/CartItem.h"

CartItem::CartItem(string isbn, string title, int quantity)
    : isbn(isbn), quantity(quantity), title(title) {}

void CartItem::addAuthor(string author) {
  authors.push_back(author);
}

string CartItem::getIsbn() { return isbn; }

string CartItem::getTitle() { return title; }

int CartItem::getQuantity() { return quantity; }

deque<string> CartItem::getAuthors() { return authors; }
