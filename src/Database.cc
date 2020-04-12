#include "../include/Database.h"
#include <iostream>

Database::Database(string db, string user, string pass, string addr,
                   string port)
    : conn("dbname = '" + db + "' user = " + user + " password = " + pass +
           " hostaddr = " + addr + " port = " + port) {
  if (conn.is_open()) {
    std::cout << "Connected successfully" << std::endl;
  }
}

Database::~Database() { conn.disconnect(); }

result Database::executeQuery(string &query) {
  nontransaction n(conn);
  result r;

  r = result(n.exec(query));
  n.commit();

  return r;
}

result Database::queryBookTitle(string &searchTerm) {
  nontransaction n(conn);
  result r;
  string query = "select * from book natural join author where title ilike '%" +
                 searchTerm + "%'";

  r = result(n.exec(query));
  n.commit();

  return r;
}

result Database::queryBookGenre(string &searchTerm) {
  nontransaction n(conn);
  result r;

  string query = "select * from book natural join genre where genre ilike '%" +
                 searchTerm + "%'";

  r = result(n.exec(query));
  n.commit();

  return r;
}

result Database::queryBookPublisher(string &searchTerm) {
  nontransaction n(conn);
  result r;

  string query =
      "select * from book where publisher ilike '%" + searchTerm + "%'";

  r = result(n.exec(query));
  n.commit();

  return r;
}

result Database::queryBookAuthor(string &searchTerm) {
  nontransaction n(conn);
  result r;

  string query =
      "select * from book natural join author where author ilike '%" +
      searchTerm + "%'";

  r = result(n.exec(query));
  n.commit();

  return r;
}


  return result(n.exec(query));

void Database::addCustomer(Customer *c, Address *ship, Address *bill) {
  nontransaction n(conn);
  string query =
      "insert into customer (email_address, first_name, last_name, password) "
      "values ";

  query += "('" + c->getEmail() + "', '" + c->getFirst() + "', '" +
    c->getLast() + "', '" + c->getPassword() + "';";

  result(n.exec(query));
  n.abort();
  addAddress(c->getEmail(), "shipping", ship);
  addAddress(c->getEmail(), "billing", bill);

}

}
