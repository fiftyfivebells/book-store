#include "../include/Control.h"

#include <iostream>
#include <string>

using namespace std;

void Control::launch() {
  int choice, owner;

  while (1) {
    view.selectMenu(owner);
  }

  if (owner == 0) return;

  while (1) {
    if (owner == 1) {
      view.showCustomerMenu(choice);
    } else {
      view.showOwnerMenu(choice);
    }
  }
}
