#include "../include/View.h"
#include <iomanip>
#include <iostream>
#include <limits>
#include <string>

using namespace std;

void View::selectMenu(int &choice) {
  cout << endl << endl;
  cout << "Are you a customer or an owner? Select below: " << endl;
  cout << "  (1) Customer" << endl;
  cout << "  (2) Owner" << endl;
  cout << "  (0) Exit" << endl << endl;

  cout << "Enter your selection: ";
  cin >> choice;

  if (choice == 0) return;

  while (choice < 0 || choice > 2) {
    cout << "Enter your selection: ";
    cin >> choice;
  }
}

void View::displayLogInOrRegister(int &choice, int &owner) {
  clearScreen();
  cout << "Select an option: " << endl;
  cout << "  (1) Login (if existing user)" << endl;
  if (owner == 1)
    cout << "  (2) Register (if new user)" << endl;
  cout << "  (0) Quit" << endl << endl;

  cout << "Enter your selection: ";
  cin >> choice;
  if (choice == 0) return;

  while (choice < 0 || choice > 2) {
    cout << "Enter your selection: ";
    cin >> choice;
  }
}

void View::showCustomerMenu(int &choice) {
  clearScreen();
  cout << "Select an option: " << endl;
  cout << "  (1) Search for books" << endl;
  cout << "  (2) Look at cart" << endl;
  cout << "  (3) Account options" << endl;
  cout << "  (0) Exit" << endl << endl;

  cout << "Enter your selection: ";
  cin >> choice;
  if (choice == 0) return;

  while (choice < 0 || choice > 3) {
    cout << "Enter your selection: ";
    cin >> choice;
  }
}

void View::showOwnerMenu(int &choice) {
  cout << endl << endl;
  cout << "Select an option: " << endl;
  cout << "  (1) Run reports" << endl;
  cout << "  (2) Order books" << endl;
  cout << "  (3) Create an expense" << endl;
  cout << "  (0) Exit" << endl << endl;

  cout << "Enter your selection: ";
  cin >> choice;
  if (choice == 0) return;

  while (choice < 0 || choice > 3) {
    cout << "Enter your selection: ";
    cin >> choice;
  }
}

void View::bookSearchMenu(int &choice) {
  cout << "What would you like to search by?" << endl;
  cout << "  (1) Title" << endl;
  cout << "  (2) Author" << endl;
  cout << "  (3) Genre" << endl;
  cout << "  (4) Publisher" << endl;

  cout << "  (0) Back to previous menu" << endl << endl;

  cout << "Enter your selection: ";
  cin >> choice;
  if (choice == 0) return;

  while (choice < 0 || choice > 4) {
    cout << "Enter your selection: ";
    cin >> choice;
  }
}

void View::readLine(string &str) {
  getline(cin, str);

  while (str.length() == 0)
    getline(cin, str);
}

void View::printStr(string str) { cout << str; }

void View::readStr(string &str) { cin >> str; }

void View::readInt(int &n) { cin >> n; }

void View::clearScreen() {
  printStr("\033[2J");
  printStr("\033[1;1H");
}

void View::afterSearch(int &choice) {
  cout << "What would you like to do?" << endl;
  cout << "  (1) Purchase one of selection" << endl;
  cout << "  (2) Search again" << endl;
  cout << "  (0) Back to previous menu" << endl;
  cout << "Enter your selection: ";

  cin >> choice;

  if (choice == 2) return;

  while (choice < 1 || choice > 2) {
    printStr("Enter your selection:");
    cin >> choice;
  }
}

void View::displayBook(CartItem *item) {
  cout << item->getIsbn() << ": " << setw(12) << item->getTitle() << ", "
       << item->getQuantity() << " in cart." << endl;
}

void View::showCart(Cart *cart) {
  clearScreen();

  if (cart->getItems().size() == 0) {
    cout << "Nothing in your cart." << endl;
    return;
  }

  for (int i = 0; i < cart->getItems().size(); ++i) {
    cout << "Item " << (i + 1) << ": ";
    displayBook(cart->getItems()[i]);
  }
}

void View::displayCartOps(int &choice) {
  cout << "What would you like to do?" << endl;
  cout << "  (1) View shopping cart" << endl;
  cout << "  (2) Purchase shopping cart" << endl;
  cout << "  (3) Empty cart" << endl;
  cout << "  (0) Back to previous " << endl;
  cout << "Enter your selection: " << endl;

  cin >> choice;

  if (choice == 0) return;

  while (choice < 0 || choice > 3) {
    cout << "Enter your selection: " << endl;
    cin >> choice;
  }
}
