#include <iostream>
#include <string>
using namespace std;
class node
{
private:
    string data;
    string meaning;
    node *left, *right;

public:
    node(string dt = "", string mem = "", node *lt = nullptr, node *rt = nullptr)

    {
        data = dt;
        meaning = mem;
        left = lt;
        right = rt;
    }
    friend class tree;
};
class tree
{
private:
    node *root;
    void acending(node *);
    void decending(node *);

public:
    tree() : root(nullptr) {}
    void insert(string, string);
    void search(string);
    void update(string);
    void Delete(string);
    void print();
};
void tree::insert(string val, string mean)
{
    node *nptr = root, *parent = nullptr;
    node *temp = new node(val, mean);
    if (!nptr)
        root = temp;
    else
    {
        while (1)
        {
            parent = nptr;
            if (val < parent->data)
            {
                nptr = nptr->left;
                if (!nptr)
                {
                    parent->left = temp;
                    return;
                }
            }
            else if (val > parent->data)
            {
                nptr = nptr->right;
                if (!nptr)
                {
                    parent->right = temp;
                    return;
                }
            }
            else
            {
                cout << "Key is alreadt present!" << endl;
                return;
            }
        }
    }
}
void tree::search(string val)
{
    node *nptr = root, *parent = nullptr;
    int count = 0;
    while (1)
    {
        parent = nptr;
        if (val < parent->data)
        {
            count++;
            nptr = nptr->left;
            if (!nptr)
            {
                cout << "Data not found" << endl;
                return;
            }
            if (nptr->data == val)
            {
                cout << "Key Found" << endl;
                cout << nptr->data << ": " << nptr->meaning << endl;
                cout << "No of comparison: " << count << endl;
                break;
            }
        }
        else if (val > parent->data)
        {
            count++;
            nptr = nptr->right;
            if (!nptr)
            {
                cout << "Data not found" << endl;
                return;
            }
            if (nptr->data == val)
            {
                cout << "Key Found" << endl;
                cout << nptr->data << ": " << nptr->meaning << endl;
                cout << "No of comparison: " << count << endl;
                break;
            }
        }
        else
        {
            cout << "Key Found" << endl;
            cout << nptr->data << ": " << nptr->meaning << endl;
            cout << "No of comparison: " << count << endl;
            break;
        }
    }
    return;
}
void tree::update(string val)
{
    node *nptr = root, *parent = nullptr;
    while (1)
    {
        parent = nptr;
        if (val < parent->data)
        {
            nptr = nptr->left;
            if (!nptr)
            {
                cout << "data not found" << endl;
                return;
            }
            if (nptr->data == val)
            {
                cout << "Enter the new meaning: ";
                cin >> nptr->meaning;
                break;
            }
        }
        else if (val > parent->data)
        {
            nptr = nptr->right;
            if (!nptr)
            {
                cout << "data not found" << endl;
                return;
            }
            if (nptr->data == val)
            {
                cout << "Enter the new meaning: ";
                cin >> nptr->meaning;
                break;
            }
        }
        else
        {
            cout << "Enter the new meaning: ";
            cin >> nptr->meaning;
            break;
        }
    }
}
void tree::Delete(string val)
{
    node *nptr = root, *parent = nullptr;
    while (1)
    {
        parent = nptr;
        if (val < parent->data)
        {
            nptr = nptr->left;
            if (!nptr)
            {
                cout << "data not found" << endl;
                return;
            }
            if (nptr->data == val)
            {
                if (nptr->left == nullptr and nptr->right == nullptr)
                {
                    parent->left = nullptr;
                    free(nptr);
                }
                else if (nptr->left != nullptr and nptr->right != nullptr)
                {
                    // smallest value from right sub tree
                    node *temp = nptr->right;
                    while (temp->left != nullptr)
                        temp = temp->left;

                    string tem1 = temp->data;
                    string tem2 = temp->meaning;
                    Delete(temp->data);
                    nptr->data = tem1;
                    nptr->meaning = tem2;
                }
                else if (nptr->left != nullptr)
                {
                    parent->left = nptr->left;
                }
                else if (nptr->right != nullptr)
                {
                    parent->left = nptr->right;
                }
                break;
            }
        }
        else if (val > parent->data)
        {
            nptr = nptr->right;

            if (!nptr)
            {
                cout << "data not found" << endl;
                return;
            }
            if (nptr->data == val)
            {
                if (nptr->left == nullptr and nptr->right == nullptr)
                {
                    parent->right = nullptr;
                    free(nptr);
                }
                else if (nptr->left != nullptr and nptr->right != nullptr)
                {
                    node *temp = nptr->right;
                    while (temp->left != nullptr)
                    {
                        temp = temp->left;
                    }
                    string tem1 = temp->data;
                    string tem2 = temp->meaning;
                    Delete(temp->data);
                    nptr->data = tem1;
                    nptr->meaning = tem2;
                }
                else if (nptr->left != nullptr)
                {
                    parent->right = nptr->left;
                    free(nptr);
                }
                else if (nptr->right != nullptr)
                {
                    parent->right = nptr->right;
                    free(nptr);
                }
                break;
            }
        }
    }
}
void tree::print()
{
    cout << "a.Acending" << endl;
    cout << "b.Decending" << endl;
    cout << "\nEnter the char: ";
    char ch;
    cin >> ch;
    switch (ch)
    {
    case 'a':
        acending(root);
        break;
    case 'b':
        decending(root);
        break;
    default:
        cout << "Enter correct char" << endl;
        break;
    }
}
void tree::acending(node *nptr)
{
    if (!nptr)
        return;
    else
    {
        acending(nptr->left);
        cout << nptr->data << ": " << nptr->meaning << endl;
        acending(nptr->right);
    }
}
void tree::decending(node *nptr)
{
    if (!nptr)
        return;
    else
    {
        decending(nptr->right);
        cout << nptr->data << ": " << nptr->meaning << endl;
        decending(nptr->left);
    }
}

int main()
{
    tree bst;
    int n, choice;
    string data;
    string mem;
    while (1)
    {
        cout << "\n1.create BST" << endl;
        cout << "2.Insert in BST" << endl;
        cout << "3.Delete from BST" << endl;
        cout << "4.update BST" << endl;
        cout << "5.Search BST" << endl;
        cout << "6.display BST" << endl;
        cout << "7.Exit" << endl;
        cout << "\nEnter the operation: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter the number of words: ";
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                cout << "\nEnter the data :";
                cin >> data;
                cout << "Enter the data meaning :";
                cin >> mem;
                bst.insert(data, mem);
            }
            break;
        case 2:
            cout << "\nEnter the data :";
            cin >> data;
            cout << "Enter the data meaning :";
            cin >> mem;
            bst.insert(data, mem);
            break;
        case 3:
            cout << "\nEnter the data to be deleted: ";
            cin >> data;
            bst.Delete(data);
            break;
        case 4:
            cout << "\nEnter the data which meaning is to be updated: ";
            cin >> data;
            bst.update(data);
            break;
        case 5:
            cout << "\nEnter the data to search: ";
            cin >> data;
            bst.search(data);
            break;
        case 6:
            bst.print();
            break;
        case 7:
            cout << "Exited successfully" << endl;
            exit(1);
        default:
            cout << "Enter the correct operation!!" << endl;
        }
    }
    return 0;
}