#include <QCoreApplication>
#include <iostream>
#include <string>
using namespace std;
class Publication
{
protected:
    float price;

public:
    string title;
    Publication(string TITLE, float PRICE)
    {
        title = TITLE;
        price = PRICE;
    }
    void gettitle()
    {
        cout << "Enter the Title:";
        cin >> title;
        cout << "Enter the Price:";
        cin >> price;
    }
};

class Book : public Publication
{
    int pcount;

public:
    Book(string title = "", float price = 0.0, int p = 0) : Publication{title, price}
    {
        pcount = p;
    }
    void getpages()
    {
        cout << "Enter total pages:";
        cin >> pcount;
    }

    void getdetails()
    {
        cout << "\nShowing details for Book" << endl;
        cout << "Book title is:" << this->title << endl;
        cout << "page count is:" << this->pcount << endl;
        cout << "Price is:" << this->price << endl
             << "\n";
    }
};

class Tape : public Publication
{
    float ptime;

public:
    Tape(string title = "", float price = 0.0, float t = 0.0) : Publication{title, price}
    {
        ptime = t;
    }
    void gettime()
    {
        cout << "Enter the playing time:";
        cin >> ptime;
    }
    void getdetails()
    {
        cout << "\nShowing details for Tape" << endl;
        cout << "Cassette title is:" << this->title << endl;
        cout << "Playing time is " << this->ptime << " minutes" << endl;
        cout << "Price is:" << this->price << endl
             << "\n";
    }
};

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    //    Book b1("Times",250.36,45);
    //    Tape t1("Romans",450.6,63);
    //    b1.getdetails();
    //    t1.getdetails();

    int n;
    cout << "The operations are:" << endl;
    cout << "1.Add new Book" << endl;
    cout << "2.Add new Tape" << endl;
    cout << "3.Display Book" << endl;
    cout << "4.Display Tape" << endl;
    cout << "5.Exit" << endl;
    while (n != 5)
    {
        cout << "Enter the operation:";
        cin >> n;
        switch (n)
        {
        case 1:
            Book *p;
            p = new Book;
            p->gettitle();
            p->getpages();
            break;

        case 2:
            Tape *t;
            t = new Tape;
            t->gettitle();
            t->gettime();
            break;

        case 3:
            p->getdetails();
            break;

        case 4:
            t->getdetails();
            break;

        case 5:
            cout << "Exited successfully" << endl;
            break;
        }
    }
    return a.exec();
}
