-- Display Student details and Placement details using NATURAL JOIN.
SELECT S_id,S_name,S_branch,S_dob,Pcompany_name,package FROM student NATURAL JOIN PlacementDrive;

-- All student details with company_name who have conducted in same drive id
SELECT S_id,S_name,S_branch,S_dob,Pcompany_name FROM student INNER JOIN PlacementDrive USING(Drive_id) GROUP BY Drive_id;

-- List all the Student name and Student branch of Student having package 5 LPA
SELECT S_name,S_branch FROM student INNER JOIN PlacementDrive USING(Drive_id) WHERE package=500000;

-- List all the student names ,company_name having T_fee more than 20000
SELECT S_name,Tcompany_name from student INNER JOIN Training on student.T_id=Training.T_id WHERE T_fee>20000;

-- Display all training details attended by "Akash” in year 2021
SELECT T_id,Tcompany_name,T_fee,T_year FROM Training INNER JOIN student USING(T_id) WHERE S_name='Akash' and T_year=2021;

-- List the total number of companies who conduct training before 2018
SELECT COUNT(T_id) AS Number_of_Companies FROM Training WHERE T_year<2018;

-- List the students name with company ‘Microsoft’ and  location ’USA’
SELECT S_name FROM student INNER JOIN Training USING(T_id) INNER JOIN PlacementDrive USING(Drive_id) where Tcompany_name='Microsoft Training' and location='USA';

-- Find the names of all Students who have joined ‘Microsoft ‘ training  in 2021
SELECT S_name FROM student INNER JOIN Training USING(T_id) WHERE Tcompany_name='Microsoft Training' and T_year=2021;

-- Create a view showing the Student and Training details
CREATE OR REPLACE VIEW Student_Training AS SELECT * FROM student NATURAL JOIN Training;

-- Perform Manipulation on simple view-Insert, update, delete, drop view
INSERT INTO student_view (S_name,CGPA) VALUES ('Pradyna',7.8),('Shubham',9.8);

UPDATE student_view set S_name='Krishna' WHERE S_id=107;

DELETE FROM student_view WHERE S_id=118;

DROP VIEW student_view;


