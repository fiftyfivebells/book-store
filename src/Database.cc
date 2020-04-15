#include "../include/Database.h"
#include <iostream>

Database::Database() {}

Database::~Database() {
  conn->disconnect();
  delete conn;
}

void Database::setConnection(string db, string user, string pass, string addr,
                             string port) {
  conn = new connection("dbname = '" + db + "' user = " + user +
                        " password = " + pass + " hostaddr = " + addr +
                        " port = " + port);
  if (conn->is_open()) std::cout << "Connected successfully" << std::endl;
}

result Database::executeQuery(string &query) {
  nontransaction n(*conn);
  result r;

  r = result(n.exec(query));
  n.commit();

  return r;
}

result Database::queryBookTitle(string &searchTerm) {
  nontransaction n(*conn);
  result r;
  string query = "select * from book_title('" + searchTerm + "');";

  r = result(n.exec(query));
  n.commit();

  return r;
}

result Database::queryBookGenre(string &searchTerm) {
  nontransaction n(*conn);
  result r;
  string query = "select * from book_genre('" + searchTerm + "';";

  r = result(n.exec(query));
  n.commit();

  return r;
}

result Database::queryBookPublisher(string &searchTerm) {
  nontransaction n(*conn);
  result r;

  string query =
      "select * from book where publisher ilike '%" + searchTerm + "%'";

  r = result(n.exec(query));
  n.commit();

  return r;
}

result Database::queryBookAuthor(string &searchTerm) {
  nontransaction n(*conn);
  result r;

  string query = "select * from book_author('" + searchTerm + "');";

  r = result(n.exec(query));
  n.commit();

  return r;
}

bool Database::makeBookOrder(Cart *c, Address *a, Customer *cust) {
  nontransaction n(*conn);
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
  string email = cust->getEmail();
  createCustomerOrder(id, email);

  for (unsigned long int i = 0; i < c->getItems().size(); ++i)
    createBookOrderItem(id, c->getItems()[i]);

  return true;
}

bool Database::updateBookQuantity(string id, int q) {
  nontransaction n(*conn);
  string query = "update book set quantity = quantity - " + to_string(q) +
                 " where isbn = '" + id + "';";

  result(n.exec(query));

  n.abort();
  return true;
}

void Database::createBookOrderItem(string &id, CartItem *item) {
  nontransaction n(*conn);
    string query =
        "insert into order_contains (isbn, order_number, quantity) values ";
  query += "('" + item->getIsbn() + "', '{" + id + "}', " +
           to_string(item->getQuantity()) + ");";

  result(n.exec(query));

  n.abort();
  updateBookQuantity(item->getIsbn(), item->getQuantity());
}

void Database::createCustomerOrder(string &id, string &email) {
  nontransaction n(*conn);
  string query =
      "insert into customer_book_order (order_number, customer_email) values ";

  query += "('{" + id + "}', '" + email + "');";

  result(n.exec(query));
  n.abort();
}

void Database::addCustomer(Customer *c, Address *ship, Address *bill) {
  nontransaction n(*conn);
  cout << "customer name: " << c->getFirst() << endl;
  string query =
      "insert into customer (email_address, first_name, last_name, password) "
      "values ";

  query += "('" + c->getEmail() + "', '" + c->getFirst() + "', '" +
           c->getLast() + "', '" + c->getPassword() + "');";

  result(n.exec(query));
  n.abort();
  addAddress(c->getEmail(), "shipping", ship);
  addAddress(c->getEmail(), "billing", bill);
}

void Database::addAddress(string email, string type, Address *a) {
  nontransaction n(*conn);
  string query =
      "insert into customer_address (address_type, customer_email, "
      "street_number, street_name, apt_number, city, c_state, zip) values ";

  query += "('" + type + "', '";
  query += email + "', ";
  query += a->getStreetNum() + ", '";
  query += a->getStreetName() + "', '";
  query += a->getAptNum() + "', '";
  query += a->getCity() + "', '";
  query += a->getState() + "', ";
  query += a->getZip() + ");";

  result(n.exec(query));
  n.abort();
}

string Database::getUserPass(string &email) {
  nontransaction n(*conn);

  string query = "select password from customer where email_address = '";
  query += email + "';";

  result r = result(n.exec(query));

  return r[0][0].as<string>();
}

string Database::getOwnerPass(string &name) {
  nontransaction n(*conn);
  result r;
  string query =
      "select password from owner where first_name = '" + name + "';";

  r = result(n.exec(query));

  return r[0][0].as<string>();
  return "";
}

void Database::getCustomer(string &email, Customer **c, Address **ship,
                           Address **bill) {
  nontransaction n(*conn);
  result r;
  string query =
      "select * from customer where email_address = '" + email + "';";

  r = result(n.exec(query));

  *c = new Customer(r[0][1].as<string>(), r[0][2].as<string>(),
                    r[0][0].as<string>(), r[0][3].as<string>());

  n.abort();
  getAddress(email, "shipping", ship);
  getAddress(email, "billing", bill);
}

void Database::getOwner(string &name, Owner **o) {
  nontransaction n(*conn);
  result r;
  string query = "select * from owner where first_name = '" + name + "';";

  r = result(n.exec(query));

  *o = new Owner(r[0][0].as<string>(), r[0][1].as<string>(),
                 r[0][2].as<string>(), r[0][3].as<string>());
}

void Database::getAddress(string email, string type, Address **a) {
  result r;
  nontransaction n(*conn);
  string query =
      "select * from customer_address where customer_email = '" + email + "' ";
  query += " and address_type = '" + type + "';";
  r = result(n.exec(query));
  *a = new Address(r[0][2].as<string>(), r[0][3].as<string>(),
                   r[0][4].as<string>(), r[0][5].as<string>(),
                   r[0][6].as<string>(), r[0][7].as<string>());

  n.abort();
}

result Database::getCustomerOrderHistory(Customer *c, int &choice) {
  nontransaction n(*conn);
  string status = (choice == 1) ? "<>" : "=";

  string query =
      "select * from customer_book_order, book_order where "
      "customer_book_order.order_number = book_order.order_number and status "
      + status + "'delivered' and "
      "customer_email = '" +
      c->getEmail() + "';";

  return result(n.exec(query));
}

result Database::customExpenses(string &start, string &end) {
  nontransaction n(*conn);
  string query =
      "select * from expense_report('" + start + "', '" + end + "');";
  return result(n.exec(query));
}

result Database::customSales(string &start, string &end) {
  nontransaction n(*conn);
  string query = "select * from sales_report('" + start + "', '" + end + "');";
  return result(n.exec(query));
}

result Database::annualSales(string &year) {
  string start = year + "-01-01";
  string end = year + "-12-31";

  return customSales(start, end);
}

result Database::annualExpenses(string &year) {
  string start = year + "-01-01";
  string end = year + "-12-31";

  return customExpenses(start, end);
}

void Database::orderFromPublisher(string &id, string &isbn, int &quantity) {
  string email = getPublisher(isbn);
  nontransaction n(*conn);

  string query = "select * from order_from_publisher('{" + id + "}', '" +
                 email + "', '" + isbn + "', " + to_string(quantity) + ");";

  result(n.exec(query));
}

string Database::getPublisher(string &isbn) {
  nontransaction n(*conn);
  result r;
  string query = "select publisher from book where isbn = '" + isbn + "';";
  r = result(n.exec(query));
  n.abort();

  return r[0][0].as<string>();
}
