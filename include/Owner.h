#ifndef OWNER_H
#define OWNER_H

#include <string>

using namespace std;

class Owner {
 public:
  Owner(string = "", string = "", string = "", string = "");
  string getFirst();
  string getLast();
  string getId();
  string getPassword();

 private:
  string first;
  string last;
  string pass;
  string id;
};

#endif
