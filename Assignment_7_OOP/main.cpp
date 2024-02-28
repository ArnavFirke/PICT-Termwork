#include <iostream>
#include <fstream>
#include <string>
using namespace std;

struct Student
{
    int roll_no;
    string name;
};

int main()
{

    fstream file;
    string name, designation, text;
    int age, sal;

    file.open("file.txt", ios::out);
    cout << "Enter your name: ";
    getline(cin, name);
    file << "Name is :" << name << endl;
    cout << "Enter your Designation: ";
    getline(cin, designation);
    file << "Designation is :" << designation << endl;

    cout << "Enter your age: ";
    cin >> age;
    file << "Age is :" << age << endl;

    cout << "Enter your Salary: ";
    cin >> sal;
    file << "Salary is :" << sal << endl;

    file.close();

    file.open("file.txt", ios::in);
    while (getline(file, text))
    {
        cout << text << endl;
    }
    file.close();

    file.open("Binary", ios::out | ios::binary);

    Student wstu[2];
    for (int i = 0; i < 2; i++)
    {
        cout << "Enter your name: ";
        getchar();
        getline(cin, wstu[i].name);
        cout << "Enter your roll no: ";
        cin >> wstu[i].roll_no;
        file.write((char *)&wstu[i], sizeof(Student));
    }
    file.close();

    file.open("Binary", ios::in | ios::binary);
    Student rstu[3];
    for (int i = 0; i < 3; i++)
        file.read((char *)&rstu[i], sizeof(Student));
    file.close();
    for (int i = 0; i < 2; i++)
    {
        cout << "Name: " << rstu[i].name << endl;
        cout << "Roll No: " << rstu[i].roll_no << endl;
    }
    return 0;
}
