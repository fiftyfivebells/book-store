#include "../include/Database.h"
#include <iostream>

Database::Database(string db, string user, string pass, string addr,
                   string port)
    : conn("dbname = " + db + " user = " + user + " password = " + pass +
           " hostaddr = " + addr + " port = " + port) {
  // string c = "dbname = " + db + " user = " + user + " password = " + pass + "
  // hostaddr = " + addr + " port = " + port;
  if (conn.is_open()) {
    std::cout << "Connected successfully" << std::endl;
  }
}

Database::~Database() {
  conn.disconnect();
}

result Database::executeQuery(string &query) {
  nontransaction n(conn);

  return result(n.exec(query));
}
