create or replace function insert_into_publishes() returns trigger as
$$
begin
    insert into
        publishes(isbn, email_address)
        values(new.isbn, new.publisher);

        return new;
end;
$$
language plpgsql;

create or replace function replenish_book_stock() returns trigger as
$restock_books$
declare
  pub_email varchar;
begin
  if new.quantity < 10 then
    pub_email := (select email_address from publishes where isbn = old.isbn);
    insert into orders_books (email_address, isbn, quantity) values
      (pub_email, old.isbn, 10);
    update book set quantity = quantity + 10 where isbn = new.isbn;
  end if;
  return new;
end;
$restock_books$
language plpgsql;

create or replace function book_title(search_term varchar)
  returns table(isbn varchar, title varchar, quantity numeric, price numeric, pages numeric) as $$
    select isbn, title, quantity, price, pages
    from book
    where title ilike ('%' || search_term || '%')
$$
language sql stable;

create or replace function book_genre(search_term varchar)
  returns table(isbn varchar, title varchar, quantity numeric, price numeric, genre varchar, pages numeric) as $$
    select isbn, title, quantity, price, genre, pages
    from book natural join genre
    where genre ilike ('%' || search_term || '%')
$$
language sql stable;

create or replace function book_author(search_term varchar)
  returns table(isbn varchar, title varchar, quantity numeric, price numeric, author varchar, pages numeric) as $$
    select isbn, title, quantity, price, author, pages
    from book natural join author
    where author ilike ('%' || search_term || '%')
$$
language sql stable;

create or replace function sales_report(start_date date, end_date date)
  returns numeric as $$
    select sum(amount * ((100 - percent_to_publisher) / 100)) from
      (select amount, percent_to_publisher from book_order, order_contains, book
       where book.isbn = order_contains.isbn
         and book_order.order_number = order_contains.order_number
         and order_date >= start_date
         and order_date <= end_date) as t1
$$
language sql stable;

create or replace function expense_report(start_date date, end_date date)
  returns numeric as $$
    select sum(t_cost * quantity) from
	    (select order_date, orders_books.quantity, (price * .5) as t_cost
        from orders_books, book
        where orders_books.isbn = book.isbn
        and order_date >= start_date
        and order_date <= end_date) as t1
$$
language sql stable;

create or replace function order_from_publisher(ownerid uuid, email varchar, book_id varchar, quant numeric)
  returns void as
  $$
  insert into orders_books (owner_id, email_address, isbn, quantity) values
    (ownerid, email, book_id, quant);
  update book set quantity = quantity + quant where isbn = book_id;
  $$
language sql volatile;
