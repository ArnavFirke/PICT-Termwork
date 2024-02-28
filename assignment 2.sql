-- Creating Tables
CREATE TABLE PlacementDrive(
    Drive_id INT PRIMARY KEY NOT NULL,
    Pcompany_name VARCHAR(30),
    package INT,
    location VARCHAR(30)
);

CREATE TABLE Training(
    T_id INT PRIMARY KEY NOT NULL,
    Tcompany_name VARCHAR(30),
    T_fee INT,
    T_year INT
);

CREATE TABLE student(
    S_id INT PRIMARY KEY NOT NULL AUTO_INCREMENT,
    Drive_id INT,
    T_id INT,
    S_name VARCHAR(30),
    CGPA FLOAT(1),
    S_branch VARCHAR(30),
    S_dob DATE,
    FOREIGN KEY(Drive_id) REFERENCES PlacementDrive(Drive_id) ON DELETE CASCADE,
    FOREIGN KEY(T_id) REFERENCES Training(T_id) ON DELETE CASCADE
);

-- Inserting values into tables
INSERT INTO PlacementDrive VALUES
     (1, 'Microsoft', 900000, 'USA'),
    (2, 'Amazon', 500000, 'PUNE'),
    (3, 'Apple', 1100000, 'USA'),
    (4, 'Tesla', 400000, 'USA'),
    (5, 'Uber', 700000, 'PUNE'),
    (6, 'Adobe', 300000, 'USA'),
    (7, 'Google', 1000000, 'MUMBAI'),
    (8, 'Facebook', 950000, 'MUMBAI'),
    (9, 'TCS', 800000, 'India'),
    (10, 'Infosys', 750000, 'PUNE'),
    (11, 'Wipro', 400000, 'India'),
    (12, 'HCL Technologies', 850000, 'India'),
    (13, 'Tech Mahindra', 750000, 'India');



INSERT INTO Training 
VALUES
    (1, 'Microsoft Training', 90000, 2021),
    (2, 'Amazon Training', 8000, 2022),
    (3, 'Apple Training', 11000, 2023),
    (4, 'Tesla Training', 85000, 2022),
    (5, 'Uber Training', 7000, 2021),
    (6, 'Adobe Training', 85000, 2018),
    (7, 'Google Training', 10000, 2020),
    (8, 'Facebook Training', 9500, 2018),
    (9, 'TCS Training', 80000, 2017),
    (10, 'Infosys Training', 7500, 2015);

ALTER TABLE student AUTO_INCREMENT = 101;

INSERT INTO student (Drive_id, T_id, S_name, CGPA, S_branch, S_dob)
VALUES
    (1, 1, 'Arnav', 8.7, 'CE', '1998-06-10'),
    (2, 4, 'Pradip' , 9.0, 'IT', '1999-02-15'),
    (3, 8, 'Swaraj', 8.5, 'CE', '1998-11-25'),
    (4, 5, 'Aryan', 9.2, 'CE', '1997-09-20'),
    (5, 2, 'Akash', 8.9, 'ENTC', '1999-07-05'),
    (6, 3, 'Divya', 8.4, 'CE', '1998-04-12'),
    (7, 7, 'Dev', 9.1, 'IT', '1997-12-30'),
    (8, 8, 'Avadut', 8.8, 'CE', '1998-08-18'),
    (9, 10, 'Devansh', 8.3, 'ENTC', '1999-03-08'),
    (10, 5, 'Anup', 8.6, 'CE', '1997-07-22'),
    (1, 5, 'Rahul', 9.3, 'IT', '1999-05-01'),
    (3, 3, 'Prem', 8.2, 'CE', '1998-01-28'),
    (8, 1, 'Swaroop', 9.5, 'CE', '1997-10-09'),
    (9, 4, 'Atharva', 8.1, 'IT', '1998-09-27'),
    (5, 9, 'Kishor', 9.6, 'CE', '1999-06-07'),
    (6, 5, 'Gajanan', 8.0, 'ENTC', '1998-02-17');

-- Creating View (Simple)
CREATE OR REPLACE VIEW student_view AS SELECT S_id, S_name, CGPA FROM student;

-- Creating Index (Simple)
CREATE INDEX idx_s_id ON student(S_id);

-- Creating Index (Unique)
CREATE UNIQUE INDEX idx_s_name ON student(S_name);

-- Creating Index (Composite)
CREATE INDEX idx_branch_cgpa ON student(S_branch, CGPA);

-- Creating Index (Full Text)
CREATE INDEX text_idx ON student(S_name(15));

-- Showing index in the student table
SHOW INDEX FROM student;

-- Display all student details with branches 'CE' and 'IT' and student names starting with 'A' or 'D'
SELECT * FROM student WHERE S_branch IN ('CE', 'IT') AND (S_name LIKE 'A%' OR S_name LIKE 'D%');

-- List the number of different companies. (Use of distinct)
SELECT COUNT(DISTINCT Pcompany_name) as Pcompany_name FROM PlacementDrive;

-- Give a 15% increase in the fee of the Training whose joining year is 2019.
UPDATE Training SET T_fee = 1.15 * T_fee WHERE T_year = 2019;

-- Delete Student details having a CGPA score less than 7.
DELETE FROM student WHERE CGPA < 7;

-- Find the names of companies belonging to Pune or Mumbai
SELECT Pcompany_name,location FROM PlacementDrive WHERE location IN ('PUNE', 'MUMBAI');

-- Find the student name who joined training in 2019 as well as in 2021
SELECT S_name FROM student WHERE T_id IN (SELECT T_id FROM Training WHERE T_year IN (2019, 2021));

-- Find the student name having the maximum CGPA score and names of students having CGPA score between 7 to 9
SELECT S_name FROM student WHERE CGPA = (SELECT MAX(CGPA) FROM student);
-- or query
SELECT S_name, CGPA FROM student ORDER BY CGPA DESC LIMIT 1;

SELECT S_name FROM student WHERE CGPA BETWEEN 7 AND 9;

-- Display all Student names with T_id in decreasing order of Fees
SELECT S_name, Training.T_id, T_fee FROM student INNER JOIN Training ON student.T_id = Training.T_id ORDER BY T_fee DESC;

-- Display Pcompany name, S_name, location, and Package with Packages 30K, 40K, and 50k
SELECT Pcompany_name, S_name, location, package FROM student INNER JOIN PlacementDrive 
    ON student.Drive_id = PlacementDrive.Drive_id WHERE package IN (30000, 40000, 50000);
