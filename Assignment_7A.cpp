#include <iostream>
#include <string>
using namespace std;
class FloatList
{
private:
    struct ListNode
    {
        int seatval, status;
        string id;
        struct ListNode *next;
        struct ListNode *prev;
    };
    // ListNode *head, *tail;
    ListNode *tail[10] = {nullptr}, *head[10] = {nullptr};

public:
    void create_list();
    void displayList();
    void bookseats();
    void showbook();
    void avail();
    void cancelseats();
};
void FloatList::create_list()
{
    for (int i = 0; i < 10; i++)
    {
        for (int j = 1; j <= 7; j++)
        {
            ListNode *newSeat = new ListNode;
            newSeat->seatval = j;
            newSeat->status = 0;
            newSeat->id = "";
            if (!head[i])
            {
                head[i] = tail[i] = newSeat;
            }
            else
            {
                tail[i]->next = newSeat;
                newSeat->prev = tail[i];
                tail[i] = newSeat;
                tail[i]->next = head[i];
                head[i]->prev = tail[i];
            }
        }
    }
}

void FloatList::displayList()
{
    ListNode *newSeat;

    int count = 0;
    int ch = 65;
    cout << "\n------------------------------------------------------------------------------------" << endl;
    cout << "\t\t\t\t Screen this way" << endl;
    cout << "------------------------------------------------------------------------------------" << endl;
    for (int i = 0; i < 10; i++)
    {
        newSeat = head[i];
        do
        {
            // if (newSeat->seatval / 10 == 0)
            cout << char(ch + i) << "0" << newSeat->seatval << " :";
            // else
            // cout << "S" << newSeat->seatval << " :";

            if (newSeat->status == 0)
                cout << "|___| ";
            else
                cout << "|_B_| ";
            count++;
            if (count % 7 == 0)
            {
                cout << endl;
            }
            newSeat = newSeat->next;
        } while (newSeat != head[i]);
    }
}

void FloatList::bookseats()
{
    string y;
    int row = 0, column = 0, numb;
    cout << "Enter the row: ";
    cin >> row;
    cout << "\nEnter the column from where you want seats: ";
    cin >> column;
    cout << "\nEnter the number of seats you want: ";
    cin >> numb;
    if (numb > 7)
    {
        cout << "Number of seats exceeds the limit of row" << endl;
        cout << "Enter the number of seats you want: ";
        cin >> numb;
    }
    cout << "\nEnter the ID: ";
    cin >> y;
    ListNode *newSeat = head[row - 1];
    for (int i = 0; i < column - 1; i++)
    {
        newSeat = newSeat->next;
    }

    for (int i = 0; i < numb; i++)
    {
        if (newSeat->status == 0)
        {
            newSeat->status = 1;
            newSeat->id = y;
            cout << "Seat " << newSeat->seatval << " is successfully booked!" << endl;
        }
        else
        {
            cout << "Booking Failed,Seat " << newSeat->seatval << " is already booked" << endl;
        }
        newSeat = newSeat->next;
    }
}

void FloatList::showbook()
{
    ListNode *newseat;
    int ch = 65;
    for (int i = 0; i < 10; i++)
    {
        newseat = head[i];
        while (newseat->next != head[i])
        {
            if (newseat->status == 1)
                cout << char(ch + i) << "0" << newseat->seatval << "  ";
            newseat = newseat->next;
        }
        if (newseat->status == 1)
            cout << char(ch + i) << "0" << newseat->seatval << "  " << endl;
    }
}

void FloatList::avail()
{
    ListNode *newseat;
    int count = 0, ch = 65;
    cout << "\n\n--------------------------------------------------------------------------------\n";
    cout << " \t\t\t\tScreen this way \n";
    cout << "--------------------------------------------------------------------------------\n";
    for (int i = 0; i < 10; i++)
    {
        newseat = head[i];
        while (newseat->next != head[i])
        {

            if (newseat->status == 0)
            {
                cout << char(ch + i) << "0" << newseat->seatval << " :";
                cout << "|___| ";
            }
            else if (newseat->status == 1)
                cout << "           "; // 11 spaces

            count++;
            if (count % 7 == 0)
            {
                cout << endl;
            }

            newseat = newseat->next;
        }
        if (newseat->status == 0)
        {
            cout << char(ch + i) << "0" << newseat->seatval << " :";
            cout << "|___| " << endl;
        }
        else
            cout << "           " << endl;

        count++;
    }
}

void FloatList::cancelseats()
{
    int n, i = 0, row = 0;
    string y;
    cout << "Enter the row: ";
    cin >> row;
    cout << "Enter the number of seats to be cancled: ";
    cin >> n;
    int arrseats[n];
    for (int j = 0; j < n; j++)
    {
        cout << "Enter the seat number: ";
        cin >> arrseats[j];
    }
    cout << "Enter your ID : ";
    cin >> y;
    ListNode *newSeat;
    newSeat = head[row - 1];
    while (i < n)
    {
        if (newSeat->seatval == arrseats[i])
        {
            if (newSeat->status == 1)
            {
                if (newSeat->id == y)
                {
                    newSeat->status = 0;
                    cout << "Seat " << newSeat->seatval << " is Cancelled!" << endl;
                }
                else
                    cout << "Wrong User ID !!! Seat cannot be cancelled!!!" << endl;
            }
            else
            {
                cout << "Seat not booked yet!!" << endl;
            }
            i++;
        }
        newSeat = newSeat->next;
    }
}

int main()
{
    FloatList obj;
    obj.create_list();
    int ch = 0;
    cout << "\n*********************************************\n";
    cout << " \tCINEMAX MOVIE THEATRE\n";
    cout << "*********************************************\n";
    cout << "\n1.Current Seat Status" << endl;
    cout << "2.Book Seat" << endl;
    cout << "3.Cancel Seat" << endl;
    cout << "4.Available seats" << endl;
    cout << "5.Show Booked seats" << endl;
    cout << "6.Exit" << endl;
    while (ch != 6)
    {
        cout << "\nEnter Choice:";
        cin >> ch;
        switch (ch)
        {
        case 1:
            cout << "1.Current Seat Status:" << endl;
            obj.displayList();
            break;
        case 2:
            cout << "2.Book Seat:" << endl;
            obj.bookseats();
            break;
        case 3:
            cout << "3.Cancel Seat:" << endl;
            obj.cancelseats();
            break;
        case 4:
            cout << "4.Available seats:" << endl;
            obj.avail();
            break;
        case 5:
            cout << "5.Booked seats are:" << endl;
            obj.showbook();
            break;

        default:
            break;
        }
    }
    return 0;
}