#include <QCoreApplication>
#include <iostream>
#include <cstring>
using namespace std;

class Student
{
private:
    string RollNo, div;
    string telph;
    string DLno;
    string name, Class, BloodGroup, contactadd, birthday;
    int age;
    int static mem;

public:
    Student()
    {
        RollNo = "0";
        div = "3";
        Class = "Se";
        telph = "988543545";
        DLno = "A101";
        name = "Arnav";
        BloodGroup = "o+ve";
        contactadd = "patang plaza";
        birthday = "5/5/2001";
        mem++;
    }
    void getdata()
    {

        cout << "Enter Roll no: ";
        getchar();
        getline(cin, RollNo);

        cout << "Enter your name: ";
        getline(cin, name);
        cout << "Enter your class: ";
        getline(cin, Class);
        cout << "Enter division: ";
        getline(cin, div);

        cout << "Enter Blood group: ";
        getline(cin, BloodGroup);
        cout << "Enter birthday: ";
        getline(cin, birthday);
        cout << "Enter contact address: ";
        getline(cin, contactadd);
        cout << "Enter Driving license no: ";
        getline(cin, DLno);
        cout << "Enter Telephone number: ";
        getline(cin, telph);
    }
    ~Student()
    {
        cout << this->name << " (Object) is destroyed!" << endl;
        mem--;
    }
    Student(Student &s)
    {
        RollNo = s.RollNo;
        name = s.name;
        telph = s.telph;
        DLno = s.DLno;
        BloodGroup = s.BloodGroup;
        Class = s.Class;
        div = s.div;
        birthday = s.birthday;
        contactadd = s.contactadd;
        mem ++;
    }

    void display()
    {
        cout << "\n\nRoll no. is: " << RollNo << endl;
        cout << "Name is: " << name << endl;
        cout << "Class is: " << Class << endl;
        cout << "Division is: " << div << endl;
        cout << "Birthday is: " << birthday << endl;
        cout << "Blood group is: " << BloodGroup << endl;
        cout << "Contact address is: " << contactadd << endl;
        cout << "Driving license no. is: " << DLno << endl;
        cout << "Telephone number is: " << telph << endl;
    }
    static inline void members()
    {
        cout << "Total members are: " << mem << endl;
    }
    friend void vote(int);
};

int Student::mem;

void vote(int a)
{

    int age = a;
    if (age >= 18)
    {
        cout << "You can vote" << endl;
    }
    else
        cout << "You are under 18, cannot vote" << endl;
}

int main(int argc, char *argv[])

{
    QCoreApplication a(argc, argv);
    Student s;
    int age;
    s.display();
    s.getdata();
    s.display();
    cout << "Enter your age:";
    cin >> age;
    vote(age);

    int n;
    cout << "\nHow many objects u want to create:";
    cin >> n;
    Student *ptr[n];
    for (int i = 0; i < n; i++)
    {
        ptr[i] = new Student(); // new operator use to dynamic memory(run time) allocation
        ptr[i]->getdata();
    }

    for (int i = 0; i < n; i++)
    {
        ptr[i]->display();
    }
    Student::members();
    for (int i = 0; i < n; i++)
    {
        delete (ptr[i]); // delete operator use to deallocation of memory
    }

    return a.exec();
}
