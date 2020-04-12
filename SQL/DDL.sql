create extension if not exists "uuid-ossp";  -- needed to generate uuids

create table publisher
  (email_address   varchar(30),
   street_name   varchar(20),
   street_number   numeric(4, 0),
   apt_number   varchar(5),
   city   varchar(20),
   publisher_state   varchar(20),
   zip   numeric(5, 0),
   phone_number   varchar(14),
   bank_account   varchar(15),
   primary key (email_address)
  );

create table book
  (isbn   varchar(10),
   title   varchar(150) not null,
   publisher   varchar(80) not null,
   pages   numeric(4, 0) not null,
   quantity   numeric(3, 0) not null check (quantity > -1),
   price   numeric(5, 2) not null,
   percent_to_publisher   numeric(2, 0) not null,
   primary key (isbn),
   foreign key (publisher) references publisher
    on delete cascade
  );

create table author
  (author   varchar(80),
   isbn   varchar(10),
   primary key (author, isbn),
   foreign key (isbn) references book
    on delete cascade
  );

create table genre
  (isbn   varchar(10),
   genre   varchar(50) not null,
   primary key (isbn, genre),
   foreign key (isbn) references book
    on delete cascade
  );

create table customer
  (email_address   varchar(30),
   first_name   varchar(20) not null,
   last_name   varchar(20) not null,
   password   varchar(128) not null,
   primary key (email_address)
  );

create table customer_address
  (address_type   varchar(10) not null,
   customer_email   varchar(30),
   street_number   numeric(4, 0) not null,
   street_name   varchar(20) not null,
   apt_number   varchar(5),
   city   varchar(20) not null,
   c_state   varchar(20) not null,
   zip   numeric(5, 0) not null,
   primary key (address_type, customer_email),
   foreign key (customer_email) references customer
    on delete cascade
  );

create table owner
  (first_name   varchar(20) not null,
   last_name   varchar(20) not null,
   id   uuid default uuid_generate_v4(),
   password   varchar(128) not null,
   primary key (id)
  );

create table book_order
  (order_number   uuid default uuid_generate_v4(),
   order_date   date not null default current_date,
   amount   numeric(7, 2) not null,
   shipping_street_number   numeric(4, 0) not null,
   shipping_street_name   varchar(20) not null,
   shipping_apt_number   varchar(5),
   shipping_city   varchar(20) not null,
   shipping_state   varchar(20) not null,
   shipping_zip   numeric(5, 0) not null,
   status   varchar(15) not null,
   current_location   varchar(15) not null,
   primary key (order_number)
  );

create table customer_book_order
  (order_number   uuid,
   customer_email  varchar(30) not null,
   primary key (order_number),
   foreign key (order_number) references book_order
    on delete cascade,
   foreign key (customer_email) references customer
    on delete set null
  );

create table order_contains
  (isbn   varchar(20),
   order_number   uuid not null,
   quantity   numeric(4, 0) not null check (quantity > -1),
   primary key (isbn, order_number),
   foreign key (isbn) references book
    on delete set null,
   foreign key (order_number) references book_order
    on delete cascade
  );

 create table publishes
  (isbn   varchar(20),
   email_address   varchar(30),
   primary key (isbn, email_address),
   foreign key (isbn) references book
    on delete cascade,
   foreign key (email_address) references publisher
    on delete cascade
  );

create table orders_books
  (owner_id   uuid,
   email_address   varchar(30) not null,
   isbn   varchar(20) not null,
   order_date   date not null default current_date,
   quantity   numeric(4, 0) not null,
   primary key (owner_id),
   foreign key (owner_id) references owner
    on delete set null,
   foreign key (isbn, email_address) references publishes
    on delete set null
  );

create table misc_expenses
  (expense_id   uuid default uuid_generate_v4(),
   expense_date   date not null default current_date,
   type   varchar(20) not null,
   amount   numeric(7, 2) not null,
   primary key (expense_id)
  );

create table spends
 (expense_id   uuid not null,
  owner_id   uuid not null,
  primary key (expense_id),
  foreign key (owner_id) references owner
   on delete set null,
  foreign key (expense_id) references misc_expenses
   on delete cascade
 );
