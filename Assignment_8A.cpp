#include <iostream>
#include <iomanip>
using namespace std;
class Node
{
private:
    Node *next;
    bool isBooked;
    int start_time;
    int end_time;
    int min_duration;
    int max_duration;

public:
    Node(bool isBooked = false, int start_time = 0, int end_time = 0, int min_duration = 0, int max_duration = 60)
    {
        this->isBooked = isBooked;
        this->start_time = start_time;
        this->end_time = end_time;
        this->min_duration = min_duration;
        this->max_duration = max_duration;
        next = nullptr;
    };
    friend class Schedule;
};

class Schedule
{
private:
    Node *head;
    Node *tail;
    Node *sorted;
    static int slots;

public:
    Schedule()
    {
        head = nullptr;
        tail = nullptr;
        sorted = nullptr;
    }

    void MakeSlot(int startTime = 0)
    {
        Node *newSlot = new Node();
        slots++;
        if (startTime == 0)
        {
            cout << "Enter the start time:";
            cin >> startTime;
        }
        newSlot->start_time = startTime;

        cout << "Enter End time: ";
        cin >> newSlot->end_time;
        cout << "Enter Max Duration of Slot: ";
        cin >> newSlot->max_duration;
        cout << "Enter Min Duration of Slot: ";
        cin >> newSlot->min_duration;

        if (head==nullptr)
        {
            head = newSlot;
            tail = newSlot;
             
        }
        else
        {
            tail->next = newSlot;
            tail = newSlot;
        }
    }

    void ShowSlots()
    {
        if (head != nullptr)
        {
            Node *nodeptr = head;
            cout << "Booked slots are:" << endl;
            cout << left << setw(15) << "Start Time"
                 << left << setw(15) << "End Time"
                 << left << setw(15) << "Max Duration"
                 << left << setw(15) << "Min Duration" << endl;
            while (nodeptr != nullptr)
            {
                cout << left << setw(15) << nodeptr->start_time
                     << left << setw(15) << nodeptr->end_time
                     << left << setw(15) << nodeptr->max_duration
                     << left << setw(15) << nodeptr->min_duration << endl;
                nodeptr = nodeptr->next;
            }
        }
        else
        {
            cout << "Slots are not booked yet!!" << endl;
        }
    }

    void BookAppointment()
    {
        int stime;
        cout << "Enter Start time in hrs: ";
        cin >> stime;
        Node *nodeptr = head;
        while (nodeptr != nullptr)
        {
            if (nodeptr->start_time <= stime && nodeptr->end_time > stime)
            {
                cout << "Slot is aldready booked please try again!" << endl;
                return;
            }
            nodeptr = nodeptr->next;
        }
        MakeSlot(stime);
    }

    void CancelAppointment()
    {
        int sTime;
        cout << "Enter the start time(hr) to cancel the appointment ";
        cin >> sTime;
        Node *nodeptr1 = head;
        Node *nodeptr2 = head;
        while (nodeptr1 != nullptr)
        {
            if (nodeptr1->start_time == sTime)
            {
                cout << "Slot Found\nPress Y to cancel else press N" << endl;
                char ip;
                cin >> ip;
                if (ip == 'Y' || ip == 'y')
                {
                    if (nodeptr1->next == nullptr)
                    {
                        head = nullptr;
                    }
                    else if (nodeptr1 == head)
                    {
                        head = nodeptr1->next;
                    }
                    else
                    {
                        nodeptr2 = nodeptr2->next;
                    }
                    delete nodeptr1;
                    slots--;
                    return;
                }
                else
                {
                    cout << "Didn't cancel Slot" << endl;
                    return;
                }
            }
            nodeptr2 = nodeptr1;
            nodeptr1 = nodeptr1->next;
        }
        cout << "Did not find slot" << endl;
    }

    void Sort_sTime()
    {
        Node *nodeptr = head;
        for (int i = 0; i < slots; i++)
        {
            while (nodeptr->next != nullptr)
            {
                if (nodeptr->start_time > nodeptr->next->start_time)
                {
                    int temp = nodeptr->start_time;
                    nodeptr->start_time = nodeptr->next->start_time;
                    nodeptr->next->start_time = temp;

                    temp = nodeptr->end_time;
                    nodeptr->end_time = nodeptr->next->end_time;
                    nodeptr->next->end_time = temp;

                    temp = nodeptr->max_duration;
                    nodeptr->max_duration = nodeptr->next->max_duration;
                    nodeptr->next->max_duration = temp;

                    temp = nodeptr->min_duration;
                    nodeptr->min_duration = nodeptr->next->min_duration;
                    nodeptr->next->min_duration = temp;
                }
                nodeptr = nodeptr->next;
            }
        }
    }

    void insert(Node *temp)
    {
        // insertion before the head (here head is sorted)
        if (sorted == nullptr || sorted->start_time >= temp->start_time)
        {
            temp->next = sorted;
            sorted = temp;
        }
        else
        {
            Node *current = sorted;
            while (current->next != nullptr && current->next->start_time < temp->start_time)
            {
                current = current->next;
            }
            temp->next = current->next;
            current->next = temp;
        }
    }

    void insertionSort()
    {
        Node *current = head;

        while (current != nullptr)
        {
            Node *next = current->next;
            insert(current);
            current = next;
        }
        head = sorted;
    }
};

int Schedule::slots = 0;

int main()
{
    Schedule Appoint;
    int input = 0;
    cout << "Choose operation" << endl;
    cout << "1. Book an Appointment" << endl;
    cout << "2. Display Slots" << endl;
    cout << "3. Sort based on start time" << endl;
    cout << "4. Cancel an Appointment" << endl;
    cout << "5. Sort pointer manipulation" << endl;
    cout << "6. Exit" << endl;
    while (input != 6)
    {
        cout << "\nEnter the operation: ";
        cin >> input;

        switch (input)
        {
        case 1:
            Appoint.BookAppointment();
            break;

        case 2:
            Appoint.ShowSlots();
            break;

        case 3:
            Appoint.Sort_sTime();
            break;

        case 4:
            Appoint.CancelAppointment();
            break;

        case 5:
            Appoint.insertionSort();
            break;

        case 6:
            cout << "Exited!!" << endl;
            break;

        default:
            cout << "Wrong choice!!!" << endl;
        }
    }
    return 0;
}
