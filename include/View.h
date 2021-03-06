#ifndef VIEW_H
#define VIEW_H

#include <string>
#include "Cart.h"
#include "Database.h"

using namespace std;

class View {
 public:
  void selectMenu(int &);
  void showCustomerMenu(int &);
  void showOwnerMenu(int &);
  void readInt(int &);
  void readStr(string &);
  void readLine(string &);
  void printStr(string);
  void clearScreen();
  void bookSearchMenu(int &);
  void afterSearch(int &);
  void showCart(Cart *);
  void displayBook(CartItem *);
  void displayCartOps(int &);
  void displayLogInOrRegister(int &, int &);
  void displayAccountOptions(int &);
  void displayReportsOptions(int &);
  void displayPublisherOrder(int &);
  void displayExpenseOptions(int &);
  void addressPrompt(int &);
};

#endif
