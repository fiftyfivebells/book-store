#ifndef ADDRESS_H
#define ADDRESS_H

#include <string>

using namespace std;

class Address {
 public:
  Address(string, string, string, string, string, string);
  string getStreetNum();
  string getStreetName();
  string getAptNum();
  string getCity();
  string getState();
  string getZip();

 private:
  string streetNum;
  string streetName;
  string aptNum;
  string city;
  string state;
  string zip;
};

#endif
