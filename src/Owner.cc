#include "../include/Owner.h"

Owner::Owner(string first, string last, string id, string pass)
    : first(first), last(last), pass(pass), id(id) {}

string Owner::getFirst() { return first; }

string Owner::getLast() { return last; }

string Owner::getId() { return id; }

string Owner::getPassword() { return pass; }
