#ifndef DATABASE_H
#define DATABASE_H

#include <pqxx/pqxx>
#include <string>
#include "Address.h"
#include "Cart.h"

using namespace std;
using namespace pqxx;

// forward declare
class Cart;

class Database {
 public:
  Database(string, string, string, string, string);
  ~Database();
  result executeQuery(string &);
  result queryBookAuthor(string &);
  result queryBookTitle(string &);
  result queryBookPublisher(string &);
  result queryBookGenre(string &);
  bool makeBookOrder(Cart *, Address *);
  bool updateBookQuantity(string, int);
  void createBookOrderItem(string &, CartItem *);

 private:
  connection conn;
};

#endif
