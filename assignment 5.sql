-- drop PROCEDURE proc_Grade;
DELIMITER @

CREATE PROCEDURE proc_Grade(IN rollno INT)
BEGIN
    DECLARE Status VARCHAR(20);
    DECLARE marks INT;

    DECLARE CONTINUE HANDLER FOR 1452  -- 1452 foreign key constraint failed
        BEGIN
            SELECT "Roll no is not present" AS MESSAGE;
        END;
    DECLARE CONTINUE HANDLER FOR 1062  -- 1062 duplicate entry for primary key
        BEGIN
            SELECT "Grade is already calculated for this student" AS MESSAGE;
        END;

    SET Status = NULL;
    SELECT (Total_marks) INTO marks FROM Stud_Marks WHERE Roll=rollno;


    IF marks<=1500 AND marks>=990 THEN
        SET Status='Distinction';

    ELSEIF marks<=989 AND marks>=900 THEN
        SET Status='First Class';

    ELSEIF marks<=899 AND marks>=825 THEN
       SET Status='Second Class';
    ELSE
        SET Status='Pass';
    END IF;

    INSERT INTO Result (Roll, Class) VALUES (rollno, Status);
END;
@ 


DELIMITER ;
-- Create tables
CREATE TABLE Stud_Marks(
    Roll INT PRIMARY KEY,
    Name VARCHAR(20),
    Total_marks INT
);

CREATE TABLE Result(
    Roll INT PRIMARY KEY,
    Class VARCHAR(20),
    FOREIGN KEY(Roll) REFERENCES Stud_Marks(Roll) on DELETE CASCADE
);
-- Insert data
INSERT INTO Stud_Marks VALUES
    (1,'Arnav',1000),
    (2,'Rahul',950),
    (3,'Arnav',830),
    (4,'Pradip',500);

CALL proc_Grade(1);
CALL proc_Grade(2);
CALL proc_Grade(3);
CALL proc_Grade(4);
