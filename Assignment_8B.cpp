#include <iostream>
#include <string>
using namespace std;

class Node
{
private:
    int value;
    Node *next;

public:
    Node(int data = 0, Node *nextptr = nullptr) : value(data), next(nextptr) {}
    friend class FloatList;
};

class FloatList
{
    Node *head;

public:
    FloatList() : head(nullptr) {}
    void appendNode(int);
    FloatList EitherList(FloatList, FloatList);
    FloatList NeitherList(FloatList, FloatList, FloatList);
    FloatList UnionList(FloatList, FloatList);
    FloatList IntersectionList(FloatList, FloatList);
    void addlist();
    void Display();
};
void FloatList::appendNode(int data)
{
    Node *newnode = new Node(data);
    if (head == nullptr)
    {
        head = newnode;
    }
    else
    {
        Node *nodeptr = head;
        while (nodeptr->next)
            nodeptr = nodeptr->next;
        nodeptr->next = newnode;
    }
}
void FloatList::addlist()
{
    int n;
    int roll;
    cout << "Enter the number of Students: ";
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        cout << "Enter the roll no.:";
        cin >> roll;
        appendNode(roll);
    }
}
void FloatList::Display()
{
    Node *nodeptr = head;
    while (nodeptr != nullptr)
    {
        cout << nodeptr->value << " ";
        nodeptr = nodeptr->next;
    }
    cout << endl;
}
FloatList FloatList::EitherList(FloatList l1, FloatList l2)
{
    auto nodeptr1 = l1.head;
    FloatList ulist;
    bool flag;
    while (nodeptr1 != nullptr)
    {
        auto nodeptr2 = l2.head;
        flag = true;
        while (nodeptr2 != nullptr)
        {
            if (nodeptr1->value == nodeptr2->value)
            {
                flag = false;
                break;
            }
            nodeptr2 = nodeptr2->next;
        }
        if (flag == true)
            ulist.appendNode(nodeptr1->value);
        nodeptr1 = nodeptr1->next;
    }
    auto nodeptr2 = l2.head;
    while (nodeptr2 != nullptr)
    {
        auto nodeptr1 = l1.head;
        flag = true;
        while (nodeptr1 != nullptr)
        {
            if (nodeptr1->value == nodeptr2->value)
            {
                flag = false;
                break;
            }
            nodeptr1 = nodeptr1->next;
        }
        if (flag == true)
            ulist.appendNode(nodeptr2->value);
        nodeptr2 = nodeptr2->next;
    }
    return ulist;
}
FloatList FloatList::IntersectionList(FloatList l1, FloatList l2)
{
    auto nodeptr1 = l1.head;
    FloatList ulist;
    bool flag;
    while (nodeptr1 != nullptr)
    {
        auto nodeptr = l2.head;
        flag = false;
        while (nodeptr != nullptr)
        {
            if (nodeptr1->value == nodeptr->value)
            {
                flag = true;
                break;
            }
            nodeptr = nodeptr->next;
        }
        if (flag)
            ulist.appendNode(nodeptr1->value);
        nodeptr1 = nodeptr1->next;
    }
    return ulist;
}
FloatList FloatList::NeitherList(FloatList cls, FloatList l1, FloatList l2)
{
    FloatList ulist = UnionList(l1, l2), nlist;
    bool flag;
    Node *nodeptr1 = cls.head;
    while (nodeptr1 != nullptr)
    {
        auto nodeptr = ulist.head;
        flag = true;
        while (nodeptr != nullptr)
        {
            if (nodeptr1->value == nodeptr->value)
            {
                flag = false;
                break;
            }
            nodeptr = nodeptr->next;
        }
        if (flag)
            nlist.appendNode(nodeptr1->value);
        nodeptr1 = nodeptr1->next;
    }

    return nlist;
}
FloatList FloatList::UnionList(FloatList l1, FloatList l2)
{
    auto nodeptr1 = l1.head;
    FloatList ulist;
    bool flag;
    while (nodeptr1 != nullptr)
    {
        auto nodeptr2 = l2.head;
        flag = true;
        while (nodeptr2 != nullptr)
        {
            if (nodeptr1->value == nodeptr2->value)
            {
                flag = false;
                break;
            }
            nodeptr2 = nodeptr2->next;
        }
        if (flag == true)
            ulist.appendNode(nodeptr1->value);
        nodeptr1 = nodeptr1->next;
    }

    auto nodeptr2 = l2.head;
    while (nodeptr2 != nullptr)
    {
        ulist.appendNode(nodeptr2->value);
        nodeptr2 = nodeptr2->next;
    }
    return ulist;
}
int main()
{
    FloatList vanilla, butter, cls;
    FloatList un;

    int choice = 0;
    cout << "1.Add class list" << endl;
    cout << "2.Add vanilla list" << endl;
    cout << "3.Add butterscotch list" << endl;
    cout << "4.Display list" << endl;
    cout << "5.Like Both vanilla and Butterscotch" << endl;
    cout << "6.Like either vanilla or butterscotch or not both" << endl;
    cout << "7.Like neither vanilla nor butterscotch" << endl;
    cout << "8.Exit" << endl;
    while (choice != 8)
    {
        cout << "Enter the operation: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cls.addlist();
            break;
        case 2:
            vanilla.addlist();
            break;
        case 3:
            butter.addlist();
            break;
        case 4:
            cout << "Class List:" << endl;
            cls.Display();
            cout << "Vanilla List:" << endl;
            vanilla.Display();
            cout << "Butterscotch List:" << endl;
            butter.Display();
            break;
        case 5:
            un = un.IntersectionList(vanilla, butter);
            un.Display();
            break;
        case 6:
            un = un.EitherList(vanilla, butter);
            un.Display();
            break;
        case 7:
            un = un.NeitherList(cls, vanilla, butter);
            un.Display();
            break;
        case 8:
            cout << "Exited" << endl;
            break;
        default:
            break;
        }
    }
    return 0;
}