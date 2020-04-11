#ifndef DATABASE_H
#define DATABASE_H

#include <pqxx/pqxx>
#include <string>

using namespace std;
using namespace pqxx;

class Database {
 public:
  Database(string, string, string, string, string);
  ~Database();
  result executeQuery(string&);
  result queryBookAuthor(string&);
  result queryBookTitle(string&);
  result queryBookPublisher(string&);
  result queryBookGenre(string&);

 private:
  connection conn;
};

#endif
