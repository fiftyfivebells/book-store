#include "../include/Control.h"
#include <iostream>
#include <string>

using namespace std;

Control::Control() noexcept
    : db("3005 project", "stephen", "supersecret", "127.0.0.1", "5432") {}

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
    }
  }
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
