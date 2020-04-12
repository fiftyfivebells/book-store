#include "../include/Control.h"
#include <iostream>
#include <string>

using namespace std;

Control::Control() noexcept
    : cart(),
      db("3005 project", "stephen", "supersecret", "127.0.0.1", "5432") {}

Control::~Control() {}

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

    if (menuChoice == 1) r = db.queryBookTitle(searchTerm);
    if (menuChoice == 2) r = db.queryBookAuthor(searchTerm);
    if (menuChoice == 3) r = db.queryBookGenre(searchTerm);
    if (menuChoice == 4) r = db.queryBookPublisher(searchTerm);

    for (auto row : r) {
      cout << row[0].as<string>() << ": " + row[1].as<string>() << endl;
    }

    while (1) {
      view.afterSearch(menuChoice);
      if (menuChoice == 2) break;
      else addToCart();
      if (menuChoice == 2)
        break;
      else
        addToCart();
    }
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


void Control::launch() {
  int choice, owner;

  view.selectMenu(owner);
  if (owner == 0) return;

  view.printStr("\033[2J");
  view.printStr("\033[1;1H");

  while (1) {
    if (owner == 1) {
      view.showCustomerMenu(choice);
      if (choice == 0) break;
    } else {
      view.showOwnerMenu(choice);
      if (choice == 0) break;
    }
  }
}
