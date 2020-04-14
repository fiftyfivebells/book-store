#ifndef CUSTOMER_H
#define CUSTOMER_H

#include <string>
#include "Address.h"

using namespace std;

class Customer {
 public:
  Customer(string = "", string = "", string = "", string = "");
  ~Customer();
  Address *getShipping();
  Address *getBilling();
  void setShipping(Address *);
  void setBilling(Address *);
  string getFirst();
  string getLast();
  string getEmail();
  string getPassword();

 private:
  string firstName;
  string lastName;
  string password;
  string email;
  Address *shipping;
  Address *billing;
};

#endif
