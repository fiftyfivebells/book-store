#include "../include/Address.h"

Address::Address(string stNum, string stName, string aptNum, string city,
                 string state, string zip) {
  streetNum = stNum;
  streetName = stName;
  this->aptNum = aptNum;
  this->city = city;
  this->state = state;
  this->zip = zip;
}

Address::Address(const Address &a) {
  streetNum = a.streetNum;
  streetName = a.streetName;
  aptNum = a.aptNum;
  city = a.city;
  state = a.state;
  zip = a.zip;
}

Address &Address::operator=(const Address rhs) {
  streetNum = rhs.streetNum;
  streetName = rhs.streetName;
  this->aptNum = rhs.aptNum;
  this->city = rhs.city;
  this->state = rhs.state;
  this->zip = rhs.zip;

  return *this;
}

string Address::getStreetNum() { return streetNum; }

string Address::getStreetName() { return streetName; }

string Address::getAptNum() { return aptNum; }

string Address::getCity() { return city; }

string Address::getState() { return state; }

string Address::getZip() { return zip; }
