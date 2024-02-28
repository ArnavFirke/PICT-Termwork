#include <iostream>
#include <string>
#include <iomanip>
using namespace std;
class node
{
private:
    char key;
    string value;
    node *next;

public:
    node(char k = '$', string val = "", node *nt = nullptr) : key(k), value(val), next(nt) {}
    friend class HashTable;
};
class HashTable
{
private:
    node *data[100];
    int size, index;

public:
    HashTable()
    {
        for (int i = 0; i < size; i++)
            data[i] = nullptr;
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
        node *temp = new node();
        cout << "\nEnter Key(char) : ";
        cin >> temp->key;
        cin.ignore(1000, '\n');
        cin.clear();
        cout << "Enter Key's Value : ";
        getline(cin, temp->value);
        // int(a)=97
        index = int(temp->key - 97) % size;
        cout << index << endl;
        // Inserting record using linear probing in case of collision
        if (data[index] == nullptr)
        {
            data[index] = temp;
        }
        else if (data[index] != nullptr)
        {
            node *ptr = data[index];
            while (ptr->next != nullptr)
                ptr = ptr->next;
            ptr->next = temp;
        }
    }
    void Delete()
    {
        char k;
        string val;
        cout << "\nEnter Key(char) to delete: ";
        cin >> k;
        cin.ignore(1000, '\n');
        cin.clear();
        cout << "Enter Key's Value to delete: ";
        getline(cin, val);
        index = int(k - 97) % size;

        if (data[index] == nullptr)
        {
            cout << "Data not found" << endl;
        }
        else
        {
            node *ptr = data[index];
            node *prev = nullptr;
            while (ptr != nullptr and ptr->value != val)
            {
                prev = ptr;
                ptr = ptr->next;
            }
            if (ptr == nullptr)
                cout << "Data not found" << endl;
            else
            {
                if (prev == nullptr)
                    data[index] = ptr->next;
                else
                    prev->next = ptr->next;
            }
        }
    }
    void search()
    {
        char k;
        cout << "\nEnter Key(char) to search: ";
        cin >> k;
        index = int(k - 97) % size;

        // Inserting record using linear probing in case of collision
        if (data[index] == nullptr)
        {
            cout << "Data not found" << endl;
        }
        if (data[index] != nullptr)
        {
            node *ptr = data[index];
            while (ptr != nullptr)
            {
                cout << ptr->value << " ";
                ptr = ptr->next;
            }
            cout << endl;
        }
    }
    void display()
    {
        cout << "HASH TABLE" << endl;
        for (int i = 0; i < size; i++)
        {
            node *ptr = data[i];
            if (ptr != nullptr)
                cout << left << setw(4) << ptr->key << "= ";
            else
                cout << left << setw(4) << "NULL";
            while (ptr != nullptr)
            {
                cout << left << ptr->value << " ";
                ptr = ptr->next;
            }
            cout << endl;
        }
    }
};
int main()
{
    HashTable table;
    int m, choice;
    while (1)
    {
        cout << "\n1.Create Hash Table" << endl;
        cout << "2.Insert in Hash Table" << endl;
        cout << "3.Search key in Hash Table" << endl;
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
            table.search();
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