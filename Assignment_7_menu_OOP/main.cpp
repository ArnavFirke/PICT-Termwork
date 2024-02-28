#include <iostream>
#include <fstream>
#include <string>
using namespace std;
class Student
{
    int roll_no, age;
    string name;

public:
    Student()
    {
        roll_no = 0, age = 0, name = "";
    }
    Student(string n, int r, int a)
    {
        roll_no = r, age = a, name = n;
    }
    int getroll() { return roll_no; }
    int getage() { return age; }
    string getname() { return name; }
};

int main()
{
    fstream file;
    int input;
    cout << "1.Write data in file" << endl;
    cout << "2.Read data in file" << endl;
    cout << "3.Append data in file" << endl;
    cout << "4.Delete data in file" << endl;
    cout << "5.Exit" << endl;

    while (true)
    {
        cout << "Enter the operation: ";
        cin >> input;
        //        if(input==1)
        switch (input)
        {

        case 1:
        {
            int r, a;
            string n;
            file.open("data.txt", ios::out);
            cout << "Enter Name: ";
            cin.ignore();
            getline(cin, n);
            cout << "Enter your age: ";
            cin >> a;
            cout << "Enter your roll no: ";
            cin >> r;
            Student s(n, r, a);
            file.write((char *)&s, sizeof(Student));
            file.close();
            break;
        }
        case 2:
        {
            file.open("data.txt", ios::in);
            Student s;

            while (file)
            {
                file.read((char *)&s, sizeof(Student));
                cout << "Name: " << s.getname() << endl;
                cout << "age: " << s.getage() << endl;
                cout << "roll no: " << s.getroll() << endl;
            }
            file.close();
            break;
        }
        case 3:
        {
            int r, a;
            string n;
            file.open("data.txt", ios::app);
            cout << "Enter Name: ";
            getchar();
            getline(cin, n);
            cout << "Enter your age: ";
            cin >> a;
            cout << "Enter your roll no: ";
            cin >> r;
            Student s(n, r, a);
            file.write((char *)&s, sizeof(Student));
            file.close();
            break;
        }
        case 4:
        {
        }
        case 5:
            return 0;
        }
    }

    return 0;
}
