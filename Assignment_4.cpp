#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
class HashTable
{
    // Maximum size is 100
    int data[100];
    int size;
    int index;

public:
    HashTable()
    {
        for (int i = 0; i < size; i++)
            data[i] = 0;
        index = 0;
        size = 0;
    }
    void setSize()
    {
        int sz;
        cout << "\nEnter the size: ";
        cin >> sz;
        size = sz;
    }
    void insert_record()
    {
        int t;
        cout << "\nEnter telephone number : ";
        cin >> t;
        index = t % 10;

        // Inserting record using linear probing in case of collision
        for (int j = 0; j < size; j++)
        {
            if (data[index] == t)
            {
                cout << "Record already present" << endl;
                break;
            }
            if (data[index] == 0)
            {
                data[index] = t;
                break;
            }
            else
                index = (index + 1) % size;
        }
    }
    void replacement_insert_record()
    {
        int tl;
        cout << "\nEnter telephone number : ";
        cin >> tl;
        index = tl % size;
        int indexd = index;

        for (int i = 0; i < size; i++)
        {
            if (data[index] == tl)
            {
                cout << "Record already present" << endl;
                break;
            }
            if (data[index] == 0)
            {
                data[index] = tl;
                break;
            }
            else if (index != data[index] % size)
            {
                int temp = data[index];
                while (data[indexd] != 0)
                {
                    indexd = (indexd + 1) % size;
                }
                data[indexd] = temp;
                data[index] = tl;
                break;
            }
            else
                index = (index + 1) % size;
        }
    }
    void Delete()
    {
        int t;
        cout << "\nEnter telephone number to be deleted: ";
        cin >> t;
        index = t % size;

        for (int j = 0; j < size; j++)
        {
            if (data[index] == t)
            {
                cout << "Record found at index: " << index << endl;
                data[index] = 0;
                break;
            }
            else
                index = (index + 1) % size;
        }
    }
    void display()
    {
        cout << right << setw(4) << "Index\t" << left << setw(10) << "Array" << endl;
        for (int i = 0; i < size; i++)
            cout << right << setw(4) << i << "\t" << left << setw(10) << data[i] << endl;
    }
};

int main()
{
    HashTable table;
    int m, choice;
    while (1)
    {
        cout << "\n1.Create Hash Table" << endl;
        cout << "2.Insert in Hash Table without replacement" << endl;
        cout << "3.Insert in Hash Table with replacement" << endl;
        cout << "4.Delete from Hash Table" << endl;
        cout << "5.Display Hash Table" << endl;
        cout << "6.Exit" << endl;
        cout << "\nEnter the choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            table.setSize();
            break;
        case 2:
            cout << "Enter the number of elements: ";
            cin >> m;
            for (int i = 0; i < m; i++)
                table.insert_record();
            break;
        case 3:
            cout << "Enter the number of elements: ";
            cin >> m;
            for (int i = 0; i < m; i++)
                table.replacement_insert_record();
            break;
        case 4:
            table.Delete();
            break;
        case 5:
            table.display();
            break;
        case 6:
            exit(1);
        default:
            cout << "Enter the correct operation!!" << endl;
            break;
        }
    }
    return 0;
}
