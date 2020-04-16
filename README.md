# Book Store

This is a very basic implementation of an online bookstore. It has views for both the owner and the
customer. The customer can create a profile, search for books, and add them to a shopping cart to
purchase them later. They can also view their cart and look at their order history. The owner can
choose to order books for the store and run reports on sales and expenses.

## Instructions

To run this locally, you should have a C++ compiler installed. I used g++. You should also have
PostgreSQL installed and have a database set up for this specific purpose. In the src/main.cc file,
you should update the database name, user name, and password for your database. If you are using the
defaults for address and port number, the values there should work. Otherwise, you should edit the
address and port number as well.

### Database

To get the database ready, there are a series of SQL queries in the SQL directory. These need to be
run in a specific order so that they work properly. To make them work, execute the queries in the
files in the following order:

* DDL.sql
* procedures.sql
* triggers.sql
* publisher-queries.sql
* book-queries.sql
* author-queries.sql
* genre-queries.sql

After that is set up, you should be able to run "make" in the main project directory to compile the
program. After compilation, you can run it by typing ./bookstore in the terminal (from the project
directory). Alternatively, you can type "make run" from the start, which will compile and then
immediately run the program.
