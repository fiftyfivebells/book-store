#ifndef DATABASE_H
#define DATABASE_H

#include <pqxx/pqxx>
#include <string>
#include "Address.h"
#include "Cart.h"
#include "Customer.h"
#include "Owner.h"

using namespace std;
using namespace pqxx;

// forward declare
class Cart;

class Database {
 public:
  Database();
  ~Database();
  result executeQuery(string &);
  result queryBookAuthor(string &);
  result queryBookTitle(string &);
  result queryBookPublisher(string &);
  result queryBookGenre(string &);
  bool makeBookOrder(Cart *, Address *, Customer *);
  bool updateBookQuantity(string, int);
  void createBookOrderItem(string &, CartItem *);
  void createCustomerOrder(string &, string &);
  void addCustomer(Customer *, Address *, Address *);
  void addAddress(string, string, Address *);
  void getOwner(string &, Owner **);

 private:
  connection conn;
};

#endif
