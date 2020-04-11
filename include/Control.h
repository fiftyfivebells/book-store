#ifndef CONTROL_H
#define CONTROL_H

#include "Database.h"
#include "View.h"

class Control {
 public:
  void launch();

 private:
  View view;
  Database db;
};

#endif
