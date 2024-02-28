DELIMITER @

CREATE PROCEDURE CALC(IN radius FLOAT)
BEGIN
    DECLARE rad,area FLOAT;
    -- declare continue handler for userdefined state
    DECLARE CONTINUE HANDLER FOR SQLSTATE '12345'
    BEGIN
        SELECT "RADIUS is not between 5 and 9" AS MESSAGE;
    END;
    
    SET rad = radius;

    IF rad >= 5.0 AND rad <= 9.0 THEN
        SET area = 3.14 * rad * rad;
        INSERT INTO AREA VALUES(rad,area);
    ELSE
        SIGNAL SQLSTATE '12345';
    END IF;

END;
@
DELIMITER ;
-- Create table
CREATE TABLE AREA(
    Radius FLOAT PRIMARY KEY,
    Area FLOAT 
);

CALL CALC(4.6);
CALL CALC(5.6);
CALL CALC(6.6);

