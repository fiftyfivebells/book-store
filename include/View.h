#ifndef VIEW_H
#define VIEW_H

#include <string>

using namespace std;

class View {
 public:
  void selectMenu(int&);
  void showCustomerMenu(int&);
  void showOwnerMenu(int&);
  void readInt(int&);
  void readStr(string&);
  void readLine(string&);
  void printStr(string);
  void clearScreen();
  void bookSearchMenu(int&);
  void afterSearch(int&);
  void displayCartOps(int&);
};

#endif
