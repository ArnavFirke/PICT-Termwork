#include <iostream>
#include <string>
using namespace std;
class Node
{
private:
    float data;
    Node *next;

public:
    Node(float val = 0.0, Node *nextptr = nullptr) : data(val), next(nextptr) {}
    friend class Deque;
};
class Deque
{
private:
    Node *front, *rear;

public:
    Deque() : front(nullptr), rear(nullptr) {}
    bool isEmpty()
    {
        return front == nullptr;
    }
    void Enqueue_front(float val)
    {
        Node *temp = new Node(val);
        if (isEmpty())
            front = rear = temp;
        else
        {
            temp->next = front;
            front = temp;
        }
    }

    void Enqueue_rear(float val)
    {
        Node *temp = new Node(val);
        if (isEmpty())
            front = rear = temp;
        else
        {
            rear->next = temp;
            rear = temp;
        }
    }
    void Dequeue_front()
    {
        if (isEmpty())
        {
            cout << "Queue is Empty" << endl;
            return;
        }
        else
        {
            Node *temp = front;
            front = front->next;
            delete temp;
        }
    }

    void Dequeue_rear()
    {
        if (isEmpty())
        {
            cout << "Queue is Empty" << endl;
            return;
        }
        else
        {
            Node *temp = front;
            while (temp->next != rear)
                temp = temp->next;
            rear = temp;
            delete temp->next;
        }
    }
    void display()
    {
        Node *temp = front;
        while (temp != rear)
        {
            cout << "Value is: " << temp->data << endl;
            temp = temp->next;
        }
        cout << "Value is: " << temp->data << endl;
    }
};
int main()
{
    Deque dq;
    int choice = 0, n;
    float vl;
    cout << "1. Enqueue at front" << endl;
    cout << "2. Enqueue at rear" << endl;
    cout << "3. Dequeue at front" << endl;
    cout << "4. Dequeue at rear" << endl;
    cout << "5. Display" << endl;
    cout << "6. Exit" << endl;
    while (choice != 6)
    {
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            cout << "Enueue at front\n"
                 << endl;
            cout << "Enter the number of values :";
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                cout << "Enter the value: ";
                cin >> vl;
                dq.Enqueue_front(vl);
            }
            break;
        }
        case 2:
        {
            cout << "Enueue at rear\n"
                 << endl;
            cout << "Enter the number of values :";
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                cout << "Enter the value: ";
                cin >> vl;
                dq.Enqueue_rear(vl);
            }
            break;
        }
        case 3:
        {
            cout << "Dequeue at front\n"<< endl;
            dq.Dequeue_front();
            break;
        }
        case 4:
        {
            cout << "Dequeue at rear\n"<< endl;
            dq.Dequeue_rear();
            break;
        }
        case 5:
            cout << "Displaying whole Queue\n"
                 << endl;
            dq.display();
            break;
        case 6:
            cout << "Exited" << endl;
            break;
        default:
        cout<<"Enter the correct operation"<<endl;
            break;
        }
    }
    return 0;
}