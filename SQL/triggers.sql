create trigger update_publishes
    after insert on book
    for each row
    execute procedure insert_into_publishes();

create trigger restock_books
    after update of quantity on book
    for each row
    execute procedure replenish_book_stock();
