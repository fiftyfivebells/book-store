create table publisher
  (email_address   varchar(30),
   street_name   varchar(20),
   street_number   numeric(4, 0),
   apt_number   varchar(4, 0),
   city   varchar(20),
   publisher_state   varchar(20),
   phone_number   varchar(14),
   bank_account   varchar(15)
   primary key (email_address, bank_account)
  );

create table book
  (isbn   varchar(20),
   title   varchar(25) not null,
   author   varchar(25) not null,
   publisher   varchar(25) not null,
   pages   numeric(4, 0) not null,
   quantity   numeric(3, 0) not null check (quantity > -1),
   price   numeric(5, 2) not null,
   percent_to_publisher   numeric(2, 0) not null,
   primary key (isbn)
   foreign key (publisher) references publisher
  );

 create table customer
  (email_address   varchar(30),
   first_name   varchar(20),
   last_name   varchar(20),
   password   varchar(128),
   primary key (email_address)
  );
