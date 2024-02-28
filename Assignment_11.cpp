#include <iostream>
#include <string>
using namespace std;
class Node
{
private:
    string title;
    Node *next;

public:
    Node(string tt = "", Node *nxt = nullptr) : title(tt), next(nxt) {}
    friend class Queue;
};
class Queue
{
private:
    Node *rear, *front;

public:
    Queue() : rear(nullptr), front(nullptr) {}
    bool isEmpty()
    {
        return front == nullptr;
    }
    void enqueue(string title)
    {
        Node *temp = new Node(title);
        if (isEmpty())
            front = rear = temp;
        else
        {
            rear->next = temp;
            rear = temp;
        }
    }
    void dequeue()
    {
        if (isEmpty())
        {
            cout << "Queue is empty" << endl;
            return;
        }
        else
        {
            Node *temp = front;
            front = front->next;
            delete temp;
        }
    }
    void display()
    {
        if (!isEmpty())
        {
            Node *temp = front;
            while (temp != nullptr)
            {
                cout << "Job Title: " << temp->title << endl;
                temp = temp->next;
            }
        }
    }
};

int main()
{
    Queue q;
    int choice = 0, n=0;
    string title;

    cout << "1. Enqueue" << endl;
    cout << "2. Dequeue" << endl;
    cout << "3. Display" << endl;
    cout << "4. Exit" << endl;
    while (choice != 4)
    {
        cout << "\nEnter your choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
        {
            cout << "Enueue\n" << endl;
            cout << "Enter the numbers of Job:";
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                cout << "Enter the title: ";
                cin.ignore();
                getline(cin,title);
                q.enqueue(title);
            }
            break;
        }
        case 2:
            cout << "Dequeue" << endl;
            q.dequeue();
            break;
        case 3:
            cout << "Displaying whole Queue\n" << endl;
            q.display();
            break;
        case 4:
            cout << "Exited" << endl;
            break;
        default:
            break;
        }
    }
    return 0;
}