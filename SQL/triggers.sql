create trigger update_publishes
    after insert on book
    for each row
    execute procedure insert_into_publishes();
