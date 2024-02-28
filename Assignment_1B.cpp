#include <iostream>
#include <vector>
using namespace std;
class node
{
private:
    float data;
    node *left, *right;

public:
    node(float dt = 0.0, node *lt = nullptr, node *rt = nullptr)

    {
        data = dt;
        left = lt;
        right = rt;
    }
    friend class tree;
};
class tree
{
private:
    node *root;

    void inorder(node *);
    void preorder(node *);
    void postorder(node *);
    void swapped(node *nptr)
    {
        if (!nptr)
            return;
        swapped(nptr->left);
        swapped(nptr->right);
        node *temp = nptr->left;
        nptr->left = nptr->right;
        nptr->right = temp;
    }

public:
    tree() : root(nullptr) {}
    void insert(float);
    void search(float);
    void display();
    void minmax();
    void swapfunc()
    {
        swapped(root);
    }
    vector<int> longestPath(node *);
    vector<int> path()
    {
        return longestPath(root);
    }
};
void tree::insert(float val)
{
    node *nptr = root, *parent = nullptr;
    node *temp = new node(val);
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
            else
            {
                parent = nptr;
                if (val > parent->data)
                {
                    nptr = nptr->right;
                    if (!nptr)
                    {
                        parent->right = temp;
                        return;
                    }
                }
            }
        }
    }
}
void tree::search(float val)
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
                cout << "data not found" << endl;
                return;
            }
            if (nptr->data == val)
            {
                cout << "Found" << endl;
                cout << "No of comparison: " << count << endl;
                break;
            }
        }
        else
        {
            count++;
            parent = nptr;
            if (val > parent->data)
            {
                nptr = nptr->right;
                if (!nptr)
                {
                    cout << "data not found" << endl;
                    return;
                }
                if (nptr->data == val)
                {
                    cout << "Found" << endl;
                    cout << "No of comparison: " << count << endl;
                    break;
                }
            }
        }
    }
    return;
}
void tree::minmax()
{
    node *max, *min;
    max = min = root;
    while (min->left != nullptr)
        min = min->left;
    cout << "Minimum value is: " << min->data << endl;

    while (max->right != nullptr)
        max = max->right;
    cout << "Maxnimum value is: " << max->data << endl;
}
void tree::inorder(node *nptr)
{
    if (!nptr)
        return;
    else
    {
        inorder(nptr->left);
        cout << nptr->data << " ";
        inorder(nptr->right);
    }
}
void tree::preorder(node *nptr)
{
    if (!nptr)
        return;
    else
    {
        cout << nptr->data << " ";
        preorder(nptr->left);
        preorder(nptr->right);
    }
}
void tree::postorder(node *nptr)
{
    if (!nptr)
        return;
    else
    {
        postorder(nptr->left);
        postorder(nptr->right);
        cout << nptr->data << " ";
    }
}
vector<int> tree::longestPath(node *nptr)
{
    if (nptr == nullptr)
    {
        vector<int> temp = {};
        return temp;
    }

    vector<int> rightvect = longestPath(nptr->right);

    vector<int> leftvect = longestPath(nptr->left);

    // Compare the size of the two vectors and insert current node accordingly
    if (leftvect.size() > rightvect.size())
    {
        leftvect.push_back(nptr->data);
        return leftvect;
    }
    else
    {
        rightvect.push_back(nptr->data);
        return rightvect;
    }

    // return (leftvect.size() > rightvect.size() ? leftvect : rightvect);
}
void tree::display()
{
    cout << "a.Inorder" << endl;
    cout << "b.preorder" << endl;
    cout << "c.postorder" << endl;
    cout << "\nEnter the char: ";
    char ch;
    cin >> ch;
    switch (ch)
    {
    case 'a':
        inorder(root);
        break;
    case 'b':
        preorder(root);
        break;
    case 'c':
        postorder(root);
        break;

    default:
        cout << "Enter correct char" << endl;
        break;
    }
}
int main()
{
    tree bst;
    int n, choice;
    float data;
    while (1)
    {
        cout << "\n1.create BST" << endl;
        cout << "2.Insert in BST" << endl;
        cout << "3.max and min in BST" << endl;
        cout << "4.Search BST" << endl;
        cout << "5.display BST" << endl;
        cout << "6.swap func of ptr in BST" << endl;
        cout << "7.display nodes in longest path in BST" << endl;
        cout << "8.Exit" << endl;
        cout << "\nEnter the operation: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter the number of values: ";
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                cout << "\nEnter the data :";
                cin >> data;
                bst.insert(data);
            }
            break;
        case 2:
            cout << "\nEnter the data :";
            cin >> data;
            bst.insert(data);
            break;
        case 3:
            bst.minmax();
            break;
        case 4:
            cout << "\nEnter the data to search: ";
            cin >> data;
            bst.search(data);
            break;
        case 5:
            bst.display();
            cout << endl;
            break;
        case 6:
            bst.swapfunc();
            break;
        case 7:
        {
            vector<int> temp = bst.path();
            for (int i = temp.size() - 1; i >= 0; i--)
            {
                cout << temp[i] << " ";
            }
            cout << endl;
            cout << "No. of nodes in longest path is: " << temp.size() << endl;
            break;
        }
        case 8:
            cout << "Exited successfully" << endl;
            exit(1);
        default:
            cout << "Enter the correct operation!!" << endl;
        }
    }
    return 0;
}