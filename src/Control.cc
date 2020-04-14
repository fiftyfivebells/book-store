#include "../include/Control.h"
#include <bits/stdc++.h>
#include <iostream>
#include <string>
#include "../include/Address.h"

using namespace std;

Control::Control(Database *db) noexcept
    : db(db) {
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
      cout << row[0].as<string>() << ": " + row[1].as<string>() << endl;
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
  r = db.executeQuery(query);
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
  Address *a = new Address("100", "Willow Street", "", "Boston", "MA", "02102");

  cart.purchaseCart(&db, a);
}

void Control::emptyCart() {
  cart.emptyCart();
  view.printStr("Your cart is now empty. Press any key to continue");
  string s;
  view.readLine(s);
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


void Control::launch() {
  int choice, owner;

  view.selectMenu(owner);
  if (owner == 0) return;

  while (1) {
    if (owner == 1) {
      view.displayLogInOrRegister(choice, owner);
      if (choice == 0) break;
      if (choice == 1) logInUser(&user);
      if (choice == 2) registerUser(&user);
      view.showCustomerMenu(choice);
      if (choice == 0) break;
      if (choice == 1) bookShopping();
      if (choice == 2) showCartOperations();
    } else {
      view.showOwnerMenu(choice);
      if (choice == 0) break;
    }
  }
}
