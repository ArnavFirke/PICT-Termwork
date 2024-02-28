#include <iostream>
#include <string>
using namespace std;
class Node
{
private:
    int data;
    Node *prev;
    Node *next;

public:
    explicit Node(int data = 0)
    {
        this->data = data;
        prev = nullptr;
        next = nullptr;
    }
    friend class Binary;
};

class Binary
{
    Node *head, *tail;

public:
    Binary()
    {
        head = nullptr, tail = nullptr;
    }
    void input()
    {
        int bytes;
        cout << "Enter the number of bits:";
        cin >> bytes;
        for (int i = 0; i < bytes; i++)
        {
            int data;
            cin >> data;
            while (data != 0 && data != 1)
            {
                cout << "Enter 0 or 1 only" << endl;
                cin >> data;
            }
            InsertAtHead(data);
        }
    }

    void display()
    {
        auto temp = tail;
        while (temp != nullptr)
        {
            cout << temp->data << " ";
            temp = temp->prev;
        }
        cout<<endl;
    }

    void InsertAtHead(int data)
    {
        Node *newNode = new Node(data);
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }
    void InsertAtTail(int data)
    {
        Node *newNode = new Node(data);
        if (head == nullptr)
        {
            head = newNode;
            tail = newNode;
        }
        else
        {
            newNode->prev = tail;
            tail->next = newNode;
            tail = newNode;
        }
    }

    Binary onesComplement()
    {
        Binary obj;
        auto nodeptr = head;
        while (nodeptr != nullptr)
        {
            int data;
            nodeptr->data == 1 ? data = 0 : data = 1;
            obj.InsertAtTail(data);
            nodeptr = nodeptr->next;
        }
        return obj;
    }
    Binary twosComplement()
    {
        Binary obj;
        auto nodeptr = head;
        int carry = 1;
        while (nodeptr != nullptr)
        {
            int data;
            nodeptr->data == 1 ? data = 0 : data = 1;
            if (carry == 1)
            {
                data += carry;
                if (data == 2)
                {
                    carry = 1;
                    data = 0;
                }
                else
                {
                    carry = 0;
                }
            }
            obj.InsertAtTail(data);
            nodeptr = nodeptr->next;
        }
        if (carry == 1)
        {
            obj.InsertAtTail(carry);
        }
        return obj;
    }
    Binary Add(Binary obj)
    {
        auto nodeptr1 = head;
        auto nodeptr2 = obj.head;
        Binary temp;
        int carry = 0;
        while (nodeptr1 != nullptr || nodeptr2 != nullptr)
        {

            int data = carry;
            carry = 0;
            if (nodeptr1 != nullptr)
            {
                data += nodeptr1->data;
                nodeptr1 = nodeptr1->next;
            }

            if (nodeptr2 != nullptr)
            {
                data += nodeptr2->data;
                nodeptr2 = nodeptr2->next;
            }

            if (data == 3)
            {
                carry = 1;
                data = 1;
            }
            if (data == 2)
            {
                carry = 1;
                data = 0;
            }
            temp.InsertAtTail(data);
        }
        if (carry == 1)
        {
            temp.InsertAtTail(carry);
        }
        return temp;
    }

};

int main()
{
    Binary obj1, obj2;
    int choice = 0;
    cout << "Operation are:" << endl;
    cout << "1. Enter binary numbers" << endl;
    cout << "2. 1's Complement" << endl;
    cout << "2. 2's Complement" << endl;
    cout << "4. Add binary numbers`" << endl;
    cout << "-1. Exit" << endl;
    while (choice != -1)
    {
        cout << "\nEnter operation number: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
        {
            cout << "First Binary number " << endl;
            obj1.input();
            cout << "Second binary number " << endl;
            obj2.input();
            break;
        }
        case 2:
        {
            cout << "\n1st number:     ";
            obj1.display();

            cout << "1's complement: ";
            Binary temp = obj1.onesComplement();
            temp.display();

            cout << "\n2st number:     ";
            obj2.display();

            cout << "1's complement: ";
            Binary temp2 = obj2.onesComplement();
            temp2.display();

            break;
        }

        case 3:
        {
            cout << "\n1st number:     ";
            obj1.display();

            cout << "2's complement: ";
            Binary temp = obj1.twosComplement();
            temp.display();

            cout << "\n2st number:     ";
            obj2.display();

            cout << "2's complement: ";
            Binary temp2 = obj2.twosComplement();
            temp2.display();

            break;
        }

        case 4:
        {
            Binary temp = obj1.Add(obj2);
            cout << "1st number: ";
            obj1.display();

            cout << "2nd number: ";
            obj2.display();

            cout << "Addition:   ";
            temp.display();

            break;
        }

        case -1:
        {
            cout << "Exit" << endl;
            choice = -1;
            break;
        }

        default:

            cout << "Enter valid Choice";
            break;
        }
    }

    return 0;
}