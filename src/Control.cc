#include "../include/Control.h"

#include <iostream>
#include <string>

using namespace std;

Control::Control() noexcept : db("3005 project", "stephen", "supersecret", "127.0.0.1", "5432") {}

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
