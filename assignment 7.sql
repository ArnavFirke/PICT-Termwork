-- Create table 
CREATE TABLE Library_Audit (
    audit_id INT AUTO_INCREMENT PRIMARY KEY,
    book_id INT,
    book_name VARCHAR(255),
    copies INT,
    action VARCHAR(10),  -- 'UPDATE' or 'DELETE'
    audit_timestamp TIMESTAMP
);


CREATE TABLE Library (
    book_id INT AUTO_INCREMENT PRIMARY KEY,
    book_name VARCHAR(255) NOT NULL,
    copies INT NOT NULL
);

-- Create a trigger 

DELIMITER //

CREATE TRIGGER library_update_trigger
    BEFORE UPDATE ON Library
    FOR EACH ROW
    BEGIN
        INSERT INTO Library_Audit (book_id, book_name, copies, action, audit_timestamp)
        VALUES (OLD.book_id, OLD.book_name, OLD.copies, 'UPDATE', NOW());
    END;
//
DELIMITER ;

-- Create a trigger to track deletions in the Library table
DELIMITER //
CREATE TRIGGER library_delete_trigger
    BEFORE DELETE ON Library
    FOR EACH ROW
    BEGIN
        INSERT INTO Library_Audit (book_id, book_name, copies, action, audit_timestamp)
        VALUES (OLD.book_id, OLD.book_name, OLD.copies, 'DELETE', NOW());
    END;
//
DELIMITER ;


-- Insert sample data into the Library table
INSERT INTO Library (book_name, copies) 
VALUES
    ('The Great Gatsby', 10),
    ('To Kill a Mockingbird', 8),
    ('1984', 12),
    ('Pride and Prejudice', 6),
    ('The Catcher in the Rye', 7);

UPDATE Library SET copies=16 WHERE book_id=4;

DELETE FROM Library WHERE book_id=4;

SELECT * FROM Library_Audit;