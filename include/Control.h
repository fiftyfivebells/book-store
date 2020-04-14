#ifndef CONTROL_H
#define CONTROL_H

#include "Cart.h"
#include "Customer.h"
#include "Database.h"
#include "Owner.h"
#include "View.h"

class Control {
 public:
  Control(Database *) noexcept;
  ~Control();
  void launch();

 private:
  Cart cart;
  View view;
  Database *db;
  Customer *user;
  Owner *owner;

  void bookShopping();
  void addToCart();
  void showCartOperations();
  void completePurchase();
  void emptyCart();
  void logInUser(Customer **);
  void logInOwner(Owner **);
  void registerUser(Customer **);
  void createAddress(Address **);
  void showAccountOperations();
  void getCustomerHistory();
  void trackCustomerOrders();
  void runReports();
  void orderFromPublisher();
  void createExpense();
  void annualReports();
  void customReports();
};

#endif
