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
