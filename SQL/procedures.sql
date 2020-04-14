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

