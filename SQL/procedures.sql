create or replace function insert_into_publishes() returns trigger as
$body$
begin
    insert into
        publishes(isbn, email_address)
        values(new.isbn, new.publisher);

           return new;
end;
$body$
language plpgsql;

create or replace function update_book_quantities() returns trigger as
$body$
begin


end;

create or replace function book_title(search_term varchar)
  returns table(isbn varchar, title varchar, quantity numeric, price numeric) as $$
    select isb, title, quantity, price
    from book
    where title ilike ('%' || search_term || '%')
$$
language sql stable;

create or replace function book_genre(search_term varchar)
  returns table(isbn varchar, title varchar, quantity numeric, price numeric, genre varchar) as $$
    select isbn, title, quantity, price, genre
    from book natural join genre
    where genre ilike ('%' || search_term || '%')
$$
language sql stable;

create or replace function book_author(search_term varchar)
  returns table(isbn varchar, title varchar, quantity numeric, price numeric, author varchar) as $$
    select isbn, title, quantity, price, author
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

