#ifndef VIEW_H
#define VIEW_H

#include <string>

using namespace std;

class View {
 public:
  void showCustomerMenu(int&);
  void showOwnerMenu(int&);
  void readInt(int&);
  void readStr(string&);
  void printStr(string);
};

#endif
