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

bool Database::makeBookOrder(Cart *c, Address *a) {
  nontransaction n(conn);
  result r;

  string query =
      "insert into book_order (amount, shipping_street_number, "
      "shipping_street_name, shipping_apt_number, shipping_city, "
      "shipping_state, shipping_zip, status, current_location) values";

  query += "(";
  query += to_string(c->calculatePurchase());
  query += ", " + a->getStreetNum() + ", '" + a->getStreetName() + "', '" +
           a->getAptNum() + "', '" + a->getCity() + "', '" + a->getState() +
           "', " + a->getZip() + ", ";

  query += "'shipped', 'warehouse') returning order_number;";

  r = result(n.exec(query));

  if (r.size() == 0) return false;

  string id = r[0][0].as<string>();

  n.abort();

  for (unsigned long int i = 0; i < c->getItems().size(); ++i)
    createBookOrderItem(id, c->getItems()[i]);

  return true;
}

bool Database::updateBookQuantity(string id, int q) {
  nontransaction n(conn);
  string query = "update book set quantity = quantity - " + to_string(q) +
                 " where isbn = '" + id + "';";

  result(n.exec(query));

  n.abort();
  return true;
}

void Database::createBookOrderItem(string &id, CartItem *item) {
  nontransaction n(conn);
    string query =
        "insert into order_contains (isbn, order_number, quantity) values ";
  query += "('" + item->getIsbn() + "', '{" + id + "}', " +
           to_string(item->getQuantity()) + ");";

  result(n.exec(query));

  n.abort();
  updateBookQuantity(item->getIsbn(), item->getQuantity());
}

void Database::createCustomerOrder(string &id, string &email) {
  nontransaction n(conn);
  string query =
      "insert into customer_book_order (order_number, customer_email) values ";

  query += "('{" + id + "}', '" + email + "');";

  result(n.exec(query));
  n.abort();
}

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

void Database::addAddress(string email, string type, Address *a) {
  nontransaction n(conn);
  string query = "insert into customer_address (address_type, customer_email, street_number, street_name, apt_number, city, state, zip) values ";

  query += "'(" + type + "', ";
  query += email + "', ";
  query += a->getStreetNum() + ", '";
  query += a->getStreetName() + "', '";
  query += a->getAptNum() + "', '";
  query += a->getCity() + "', '";
  query += a->getState() + "', ";
  query += a->getZip() + ";";

  result(n.exec(query));
  n.abort();
}
