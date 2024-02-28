#include <iostream>
#include <string>
using namespace std;

#define max_priority 3

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
    Node *front, *rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}
    bool isEmpty()
    {
        return front == nullptr;
    }
    void enqueue(string j_title)
    {
        Node *temp = new Node(j_title);
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
        if (!isEmpty())
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
            while (temp != rear)
            {
                cout << "Job Title: " << temp->title << endl;
                temp = temp->next;
            }
            cout << "Job Title: " << temp->title << endl;
        }
    }
};
class Priority_Queue
{
private:
    Queue arr[max_priority];

public:
    void enqueue(string job_title, int priority = max_priority - 1)
    {
        arr[priority].enqueue(job_title);
    }
    void dequeue()
    {
        for (int i = max_priority - 1; i > 0; i--)
        {
            if (!arr[i].isEmpty())
            {
                arr[i].dequeue();
                return;
            }
        }
        if (arr[0].isEmpty())
            cout << "Queue is Empty" << endl;
        else
            arr[0].dequeue();
    }
    void display()
    {
        for (int i = max_priority -1; i >=0 ; i--)
            arr[i].display();
    }
};
int main()
{
    Priority_Queue Prio_queue;
    string job_title = "";
    int priority = 0;
    int choice = 0;

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
            cout << "Enter Job Title: ";
            cin.ignore();
            getline(cin, job_title);
            cout << "Enter Priority (1-" << max_priority << ") : ";
            cin >> priority;
            while (priority <= 0 && priority > max_priority)
            {
                cout << "Enter only between (1-" << max_priority << ") : ";
                cin >> priority;
            }
            Prio_queue.enqueue(job_title, priority - 1);
            break;
        }

        case 2:
        {
            Prio_queue.dequeue();
            break;
        }

        case 3:
        {
            Prio_queue.display();
            break;
        }

        case 4:
        {
            break;
        }

        default:
            cout << "\n\t Wrong choice!!!";
        }
    }
    return 0;
}