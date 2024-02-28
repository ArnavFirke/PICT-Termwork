#include <iostream>
#include <fstream>
#include <string>
using namespace std;
//..........Class for Hashtable
class Hashtable
{
public:
    int addr;
    Hashtable();
} HT[10];

Hashtable ::Hashtable()
{
    for (int i = 0; i < 10; i++)
        HT[i].addr = -1;
}
// Class for Direct Access File
class Employee : public Hashtable
{
    int emp_id;
    char salary[10];
    char name[10];
    char exp[10];

public:
    void add_Rec();     //...Add Records
    void display_Rec(); //...Read Records
    void search_Rec();  //...Search A Record
    void delete_Rec();  //...Delete A Record
};
//..........Add records in the file
void Employee ::add_Rec()
{
    int index, count, tablesize = 10;
    int location;
    cout << "\nEnter number of records: ";
    cin >> count;
    ofstream fout;
    fout.open("FileDAF.txt", ios::out);
    for (int i = 0; i < count; i++)
    {
        cout << "\n Enter Employee id: ";
        cin >> emp_id;
        cout << "\n Enter Employee name: ";
        cin >> name;
        cout << "\n Enter Employee salary: ";
        cin >> salary;
        cout << "\n Enter Experience: ";
        cin >> exp;
        location = fout.tellp();    //...Return location
        index = emp_id % tablesize; //....Find index of Hashtable
        HT[index].addr = location;  //...Store location in Hashtable
        //.........Write the Record in File
        fout << emp_id << " " << name << " "
             << "" << exp << " " << salary << endl;
    }
    fout.close();
}
//..........Display records from the file
void Employee ::display_Rec()
{
    char buffer[40];
    int cnt = 1;
    ifstream fin;
    //.....Open File for Reading
    fin.open("FileDAF.txt", ios::in);
    //........Read till End of the File
    while (!fin.eof())
    {
        fin.getline(buffer, 40);
        cout << "\n\n Record " << cnt << " : " << buffer;
        cnt++;
    }
}
//.........Search A Record Randomly
//.....using Emp_No of Employee
void Employee ::search_Rec()
{
    int id;
    int tablesize = 10;
    //.......Accept Emp_id to search
    cout << "\n\t Enter Emp_id to search record: ";
    cin >> id;
    //......Find index to get the address of record
    int index = id % tablesize;
    //......read and store the address
    int location = HT[index].addr;
    //....Open the file for reading
    ifstream fin;
    fin.open("FileDAF.txt", ios::in);
    //.....go to the location
    fin.seekg(location, ios::beg);
    //.....Read from location
    char buffer[40];
    fin.getline(buffer, 40);
    cout << "\n\t Found Record : " << buffer;
}
//........To delete A Record from File.
void Employee ::delete_Rec()
{
    int i, id;
    int tablesize = 10;
    cout << "\n\t Enter the Emp_id to delete: ";
    cin >> id;
    int index = id % tablesize;
    int location = HT[index].addr;
    //....Open the file for reading
    ifstream fin;
    fin.open("FileDAF.txt", ios::in);
    //.....go to the location
    fin.seekg(location, ios::beg);
    //.....Read from location
    char buffer[40];
    fin.getline(buffer, 40);
    cout << "\n\t Deleted Record : " << buffer;
    
    fin.close();
    cout << "\n\t Remaining Records:- ";
    //....Open the file for reading
    fin.open("FileDAF.txt", ios::in);
    for (i = 0; i < 10; i++)
    {
        if (HT[i].addr != -1 && HT[i].addr != location)
        {
            //.....Read from location
            fin.seekg(HT[i].addr, ios::beg);
            fin.getline(buffer, 40);
            cout << "\n\t Record : " << buffer;
        }
    }
    fin.close();
}
int main()
{
    Employee E;
    cout << "\n\n .......A] Write Records in Direct Access File........";
    E.add_Rec();
    cout << "\n\n .......B] Read Records from Direct Access File........";
    E.display_Rec();
    cout << "\n\n .......C] Search Record in Direct Access File........";
    E.search_Rec();
    cout << "\n\n .......D] Delete Record from Direct Access File........";
    E.delete_Rec();
    cout << "\n\n";
    return 0;
}
/*------------OUTPUT---------------
.......A] Write Records in Direct Access File........
How many records..? : 3
Enter Employee id: 101
Enter Employee name: Sanjay
Enter Employee salary: 25000
Enter Experience: 02_Years
Enter Employee id: 102
Enter Employee name: Kanchan
Enter Employee salary: 34000
Enter Experience: 05_Years
Enter Employee id: 103
Enter Employee name: Armaan
Enter Employee salary: 51000
Enter Experience: 6_Years
.......B] Read Records from Direct Access File........
Record 1 : 101 Sanjay 02_Years 25000
Record 2 : 102 Kanchan 05_Years 34000
Record 3 : 103 Armaan 6_Years 51000
.......C] Search Record in Direct Access File........
Enter Emp_id to search record: 103
Found Record : 103 Armaan 6_Years 51000
.......D] Delete Record from Direct Access File........
Enter the Emp_id to delete the record: 102
Deleted Record : 102 Kanchan 05_Years 34000
Remaining Records:-
Record : 101 Sanjay 02_Years 25000
Record : 103 Armaan 6_Years 51000
*/