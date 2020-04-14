#include "../include/Customer.h"

Customer::Customer(string first, string last, string email, string pass) {
  firstName = first;
  lastName = last;
  password = pass;
  this->email = email;
}

Customer::~Customer() {
  delete shipping;
  delete billing;
}

Address *Customer::getShipping() { return shipping; }

void Customer::setShipping(Address *ship) { shipping = ship; }

Address *Customer::getBilling() { return billing; }

void Customer::setBilling(Address *bill) { billing = bill; }

string Customer::getFirst() { return firstName; }

string Customer::getLast() { return lastName; }

string Customer::getEmail() { return email; }

string Customer::getPassword() { return password; }
