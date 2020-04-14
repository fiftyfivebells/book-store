#include "../include/Control.h"
#include "../include/Database.h"

int main() {
  Database *db = new Database();
  db->setConnection("3005 project", "stephen", "supersecret", "127.0.0.1", "5432");
  Control control(db);
  control.launch();
  delete db;
}
