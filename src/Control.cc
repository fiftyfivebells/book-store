#include "../include/Control.h"
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include "../include/Address.h"

using namespace std;

Control::Control(Database *db) noexcept : db(db) {
  user = NULL;
  owner = NULL;
}

Control::~Control() {
  delete user;
  delete owner;
}

void Control::bookShopping() {
  string searchTerm;
  int menuChoice;
  result r;

  while (1) {
    view.clearScreen();
    view.bookSearchMenu(menuChoice);

    if (menuChoice == 0) break;

    view.printStr("Enter your search term: ");
    view.readLine(searchTerm);
    view.clearScreen();

    if (menuChoice == 1) r = db->queryBookTitle(searchTerm);
    if (menuChoice == 2) r = db->queryBookAuthor(searchTerm);
    if (menuChoice == 3) r = db->queryBookGenre(searchTerm);
    if (menuChoice == 4) r = db->queryBookPublisher(searchTerm);

    for (auto row : r) {
      cout << row[0].as<string>() << ": " + row[1].as<string>() << ", "
           << row[4].as<string>() << " pages, " << row[2].as<string>()
           << " in stock, $" << row[3].as<string>() << endl;
    }

    while (1) {
      view.afterSearch(menuChoice);
      if (menuChoice == 2 || menuChoice == 0)
        break;
      else
        addToCart();
    }
    if (menuChoice == 0) break;
  }
}

void Control::addToCart() {
  string isbn;
  string query;
  int quantity;
  result r;

  view.printStr("Enter the ISBN of the book:");
  view.readStr(isbn);
  view.printStr("Enter quantity to purchase: ");
  view.readInt(quantity);

  query = "select * from book natural right outer join author where isbn = '" +
          isbn + "';";
  r = db->executeQuery(query);
  CartItem *temp = new CartItem(isbn, r[0][1].as<string>(), quantity,
                                r[0][5].as<float>(), r[0][6].as<int>());

  for (auto row : r) temp->addAuthor(r[0][7].as<string>());

  cart.addItem(temp);
}

void Control::showCartOperations() {
  int menuChoice;
  while (1) {
    view.displayCartOps(menuChoice);

    if (menuChoice == 0) break;
    if (menuChoice == 1) view.showCart(&cart);
    if (menuChoice == 2) completePurchase();
    if (menuChoice == 3) emptyCart();
  }
}

void Control::completePurchase() {
  int menuChoice;
  Address *a;
  view.addressPrompt(menuChoice);

  if (menuChoice == 0) return;
  if (menuChoice == 1) {
    a = user->getShipping();
  }
  if (menuChoice == 2) {
    createAddress(&a);
  }
  if (cart.isEmpty()) return;
  cart.purchaseCart(db, a, user);

  if (menuChoice == 2) delete a;
}

void Control::emptyCart() {
  cart.emptyCart();
  view.printStr("Your cart is now empty. Press any key to continue");
  string s;
  view.readStr(s);
}

void Control::createAddress(Address **a) {
  string streetNum;
  string streetName;
  string aptNum;
  string city;
  string state;
  string zip;

  view.printStr("Enter a street number: ");
  view.readLine(streetNum);
  view.printStr("Enter a street name: ");
  view.readLine(streetName);
  view.printStr("Enter apartment number (or enter \"\" if none): ");
  view.readLine(aptNum);
  view.printStr("Enter your city: ");
  view.readLine(city);
  view.printStr("Enter your state: ");
  view.readLine(state);
  view.printStr("Enter your zip code: ");
  view.readLine(zip);

  *a = new Address(streetNum, streetName, aptNum, city, state, zip);
}

void Control::logInUser(Customer **c) {
  string email;
  string pass;
  string actualPass;
  Address *shipping;
  Address *billing;

  view.clearScreen();
  view.printStr("Enter your email: ");
  view.readStr(email);
  actualPass = db->getUserPass(email);

  do {
    view.printStr("Enter your password (or enter 0 to quit): ");
    view.readStr(pass);

    if (pass == "0") break;
    if (pass != actualPass) view.printStr("Password was incorrect.\n");
  } while (pass != actualPass && pass != "0");

  if (pass == "0") return;

  db->getCustomer(email, c, &shipping, &billing);
  (*c)->setBilling(billing);
  (*c)->setShipping(shipping);
}

void Control::logInOwner(Owner **o) {
  string first;
  string pass;
  string actualPass;

  view.clearScreen();
  view.printStr("Enter your name: ");
  view.readStr(first);
  actualPass = db->getOwnerPass(first);

  do {
    view.printStr("Enter your password (or enter 0 to quit): ");
    view.readStr(pass);

    if (pass == "0") break;
    if (pass != actualPass) view.printStr("Password was incorrect.\n");
  } while (pass != actualPass && pass != "0");

  if (pass == "0") return;
  db->getOwner(first, o);
  view.printStr("Enter any key to continue. ");
  view.readStr(first);
}

void Control::registerUser(Customer **c) {
  string option;
  string first;
  string last;
  string pass;
  string email;
  Address *ship;
  Address *bill;

  view.clearScreen();
  view.printStr("Enter your first name: ");
  view.readStr(first);
  view.printStr("Enter your last name: ");
  view.readStr(last);
  view.printStr("Enter your email: ");
  view.readStr(email);
  view.printStr("Enter a password: ");
  view.readStr(pass);

  *c = new Customer(first, last, email, pass);

  view.printStr("Enter your shipping address: \n");
  createAddress(&ship);
  view.printStr("Is your billing address the same? (y or n)");
  view.readStr(option);

  if (option == "y")
    bill = new Address(*ship);
  else
    createAddress(&bill);

  db->addCustomer(*c, ship, bill);
}

void Control::showAccountOperations() {
  int menuChoice;
  while (1) {
    view.displayAccountOptions(menuChoice);

    if (menuChoice == 0) break;
    getCustomerHistory(menuChoice);
  }
}

void Control::getCustomerHistory(int &choice) {
  result r = db->getCustomerOrderHistory(user, choice);

  if (r.size() == 0)
    view.printStr("No orders to display.");
  else {
    view.printStr("Orders: ");
    for (auto row : r) {
      view.printStr("Number: " + row[0].as<string>());
      view.printStr("  Date: " + row[3].as<string>());
      view.printStr("  Amount: " + row[4].as<string>());
      view.printStr("  Status: " + row[11].as<string>());
      view.printStr("  Location: " + row[12].as<string>());
      view.printStr("\n");
    }
  }
  view.printStr("\n Enter any key to continue. ");
  string s;
  view.readStr(s);
}

void Control::orderFromPublisher() {
  string isbn, id = owner->getId();
  int quantity;

  view.clearScreen();
  view.printStr("Enter the ISBN of the book you want to order: ");
  view.readStr(isbn);
  view.printStr("Enter the quantity you'd like to order: ");
  view.readInt(quantity);

  db->orderFromPublisher(id, isbn, quantity);

  view.printStr("Your order has been placed.\n");
  view.printStr("Enter any key to continue.");
  view.readStr(isbn);
}

void Control::runReports() {
  int menuChoice;
  string start;
  string end;
  result r;

  view.clearScreen();
  view.displayReportsOptions(menuChoice);

  if (menuChoice == 0) return;

  view.printStr(
      "Enter the start date of your report in the form year-month-day (ie. "
      "2020-01-01) or enter only the year if running an annual report: ");
  view.readStr(start);

  view.printStr(
      "\nEnter the end date of your report in the form year-month-day (ie. "
      "2020-01-31) or enter \"\" if running an annual report: ");
  view.readStr(end);

  if (menuChoice == 1) {
    if (end.length() == 2)
      r = db->annualExpenses(start);
    else
      r = db->customExpenses(start, end);
  } else {
    if (end.length() == 2) {
      r = db->annualSales(start);
    } else
      r = db->customSales(start, end);
  }

  float amount = roundf(r[0][0].as<float>() * 100) / 100;

  if (menuChoice == 1)
    view.printStr("\nYour total expenses for the time period are $" +
                  to_string(amount));
  if (menuChoice == 2)
    view.printStr("\nYour total sales for the time period are $" +
                  to_string(amount));
  view.printStr("\nEnter any key to continue ");
  view.readStr(start);
}

void Control::launch() {
  int choice, owns;

  view.selectMenu(owns);
  if (owns == 0) return;

  while (1) {
    if (owns == 1) {
      if (user == NULL) {
        view.displayLogInOrRegister(choice, owns);
        if (choice == 0) break;
        if (choice == 1) logInUser(&user);
        if (choice == 2) registerUser(&user);
      }
      view.showCustomerMenu(choice);
      if (choice == 0) break;
      if (choice == 1) bookShopping();
      if (choice == 2) showCartOperations();
      if (choice == 3) showAccountOperations();
    } else {
      if (owner == NULL) {
        view.displayLogInOrRegister(choice, owns);
        if (choice == 0) break;
        if (choice == 1) logInOwner(&owner);
      }
      view.showOwnerMenu(choice);
      if (choice == 0) break;
      if (choice == 1) runReports();
      if (choice == 2) orderFromPublisher();
    }
  }
}
