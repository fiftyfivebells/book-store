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
  void setConnection(string, string, string, string, string);
  void closeConnection();
  result executeQuery(string &);
  result queryBookAuthor(string &);
  result queryBookTitle(string &);
  result queryBookPublisher(string &);
  result queryBookGenre(string &);
  bool makeBookOrder(Cart *, Address *, Customer *);
  void addCustomer(Customer *, Address *, Address *);
  string getUserPass(string &);
  void getCustomer(string &, Customer **, Address **, Address **);
  void getOwner(string &, Owner **);
  result getCustomerOrderHistory(Customer *);
  result trackCustomerOrders(Customer *);
  result annualExpenses(string &);
  result annualSales(string &);
  result customExpenses(string &, string &);
  result customSales(string &, string &);
  void orderFromPublisher(string &, string &, int &);

 private:
  connection *conn;
  bool updateBookQuantity(string, int);
  void createCustomerOrder(string &, string &);
  void createBookOrderItem(string &, CartItem *);
  void addAddress(string, string, Address *);
  void getAddress(string, string, Address **);
  string getPublisher(string &);
};

#endif
