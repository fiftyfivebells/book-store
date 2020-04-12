#include "../include/Address.h"

Address::Address(string &stNum, string &stName, string &aptNum, string &city,
                 string &state, string &zip) {
  streetNum = stNum;
  streetName = stName;
  aptNum = aptNum;
  city = city;
  state = state;
  zip = zip;
}

string Address::getStreetNum() { return streetNum; }

string Address::getStreetName() { return streetName; }

string Address::getAptNum() { return aptNum; }

string Address::getCity() { return city; }

string Address::getState() { return state; }

string Address::getZip() { return zip; }
