-- drop PROCEDURE MergeData;
-- drop table N_EmpId ;
-- drop table O_EmpId ;

DELIMITER //

CREATE PROCEDURE MergeData()
BEGIN
    DECLARE done INT DEFAULT FALSE;
    DECLARE n_emp_id INT;
    DECLARE n_name VARCHAR(255);
    DECLARE n_salary DECIMAL(10, 2);

    -- Declare a cursor for the N_EmpId table
    DECLARE n_cursor CURSOR FOR SELECT EmpId, Ename, Salary FROM N_EmpId;

    -- Declare continue handler for the cursor
    DECLARE CONTINUE HANDLER FOR NOT FOUND SET done = TRUE;

    OPEN n_cursor;

    -- Start processing rows from N_EmpId
    read_loop: LOOP
        FETCH n_cursor INTO n_emp_id, n_name, n_salary;

        IF done THEN
            LEAVE read_loop;
        END IF;

        -- Check if the n_emp_id already exists in O_EmpId
        IF NOT EXISTS (SELECT 1 FROM O_EmpId WHERE EmpId = n_emp_id) THEN
            -- If the row doesn't exist in O_EmpId, insert it
            INSERT INTO O_EmpId (EmpId, Ename, Salary) VALUES (n_emp_id, n_name, n_salary);
        END IF;
    END LOOP ;

    CLOSE n_cursor;
END;
//

DELIMITER ;



-- Create the N_EmpId table
CREATE TABLE N_EmpId (
    EmpId INT,
    Ename VARCHAR(10),
    Salary INT
);

-- Insert data into N_EmpId
INSERT INTO N_EmpId 
VALUES
    (101,'Arnav',5000),
    (102,'Pradip',5600),
    (103,'Swaraj',1000),
    (104,'Rahul',45000),
    (105,'Swati',6000);

-- Create the O_EmpId table
CREATE TABLE O_EmpId (
    EmpId INT,
    Ename VARCHAR(10),
    Salary INT
);

-- Insert data into O_EmpId
INSERT INTO O_EmpId 
VALUES
    (100,'Prem',400),
    (102,'Pradip',5600),
    (104,'Rahul',45000),
    (106,'Dev',6500),
    (108,'Divya',1000);


-- Call the procedure to merge data
CALL MergeData();







