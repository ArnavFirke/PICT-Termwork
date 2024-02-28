#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Student
{
private:
    int rollNumber;
    string name;
    string division;
    string address;

public:
    void addStudent()
    {
        ofstream outFile("students.txt", ios::app); // Open file in append mode to add new student
        if (!outFile)
        {
            cout << "Error opening file." << endl;
            return;
        }
        cout << "Enter Roll Number: ";
        cin >> this->rollNumber;
        cout << "Enter Name: ";
        cin.ignore();
        getline(cin, this->name);
        cout << "Enter Division: ";
        getline(cin, this->division);
        cout << "Enter Address: ";
        getline(cin, this->address);

        outFile << this->rollNumber << ',' << this->name << ','
                << this->division << ',' << this->address << endl; // Write student information to file

        cout << "Student information added successfully." << endl;

        outFile.close(); // Close the file
    }

    void deleteStudent(int rollNumber)
    {
        ifstream inFile("students.txt"); // Open file for reading
        if (!inFile)
        {
            cout << "Error opening file." << endl;
            return;
        }

        ofstream tempFile("temp.txt"); // Create a temporary file for writing
        if (!tempFile)
        {
            cout << "Error creating temporary file." << endl;
            inFile.close();
            return;
        }

        bool found = false;
        string line;

        while (getline(inFile, line)) // Read each line from the file
        {
            size_t pos = line.find(',');
            int currentRollNumber = stoi(line.substr(0, pos)); // Extract the roll number from the line

            if (currentRollNumber == rollNumber) // If the roll number matches the one to be deleted
            {
                found = true;
                continue; // Skip writing this line to the temporary file
            }

            tempFile << line << endl; // Write the line to the temporary file
        }

        inFile.close();
        tempFile.close();

        remove("students.txt");             // Remove the original file
        rename("temp.txt", "students.txt"); // Rename the temporary file to the original file name

        if (found)
            cout << "Student information deleted successfully." << endl;
        else
            cout << "Student not found." << endl;
    }

    void displayStudent(int rollNumber)
    {
        ifstream inFile("students.txt"); // Open file for reading
        if (!inFile)
        {
            cout << "Error opening file." << endl;
            return;
        }

        bool found = false;
        string line;

        while (getline(inFile, line)) // Read each line from the file
        {
            size_t pos = line.find(',');
            int currentRollNumber = stoi(line.substr(0, pos)); // Extract the roll number from the line

            if (currentRollNumber == rollNumber) // If the roll number matches the one to be displayed
            {
                found = true;

                size_t prevPos = pos + 1;
                pos = line.find(',', prevPos);
                string name = line.substr(prevPos, pos - prevPos); // Extract the name

                prevPos = pos + 1;
                pos = line.find(',', prevPos);
                string division = line.substr(prevPos, pos - prevPos); // Extract the division

                prevPos = pos + 1;
                string address = line.substr(prevPos); // Extract the address

                cout << "Roll Number: " << currentRollNumber << endl;
                cout << "Name: " << name << endl;
                cout << "Division: " << division << endl;
                cout << "Address: " << address << endl;

                break;
            }
        }

        inFile.close();

        if (!found)
        {
            cout << "Student not found." << endl;
        }
    }
};

int main()
{
    int choice;
    int rollNumber;
    Student s;

    while (true)
    {
        cout << "\n1. Add Student" << endl;
        cout << "2. Delete Student" << endl;
        cout << "3. Display Student" << endl;
        cout << "4. Exit" << endl;
        cout << "\nEnter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            s.addStudent();
            break;
        case 2:
            cout << "Enter Roll Number of student to delete: ";
            cin >> rollNumber;
            s.deleteStudent(rollNumber);
            break;
        case 3:
            cout << "Enter Roll Number of student to display: ";
            cin >> rollNumber;
            s.displayStudent(rollNumber);
            break;
        case 4:
            exit(1);
        default:
            cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}
