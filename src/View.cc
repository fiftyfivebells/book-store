#include "../include/View.h"
#include <iostream>

using namespace std;

void View::showCustomerMenu(int &choice) {
  cout << endl << endl;
  cout << "Select an option: " << endl;
  cout << "  (1) Search for books" << endl;
  cout << "  (2) Look at cart" << endl;
  cout << "  (0) Exit" << endl << endl;

  cout << "Enter your selectio: ";
  cin >> choice;
  if (choice == 0) return;

  while (choice < 0 || choice > 2) {
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

  cout << "Enter your selectio: ";
  cin >> choice;
  if (choice == 0) return;

  while (choice < 0 || choice > 3) {
    cout << "Enter your selection: ";
    cin >> choice;
  }
}

void View::printStr(string str) { cout << str; }

void View::readStr(string &str) { cin >> str; }

void View::readInt(int &n) { cin >> n; }
