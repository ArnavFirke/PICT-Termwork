#include <iostream>
#include <string>
using namespace std;
class node
{
private:
    float data;
    node *left, *right;
    int lthread, rthread;

public:
    node(float dt = 0.0, int lth = 0, int rth = 0, node *lt = nullptr, node *rt = nullptr)

    {
        data = dt;
        lthread = lth;
        rthread = rth;
        left = lt;
        right = rt;
    }
    friend class tree;
};
class tree
{
private:
    node *root, *header;
    node *insuc(node *);
    node *inpred(node *);
    void bothchild(node *, node *);
    void nochild(node *, node *);
    void onechild(node *, node *);

public:
    tree() : root(nullptr), header(nullptr) {}
    node *getroot()
    {
        return root;
    }
    void insertnode(float);
    void inorder();
    void preorder();
    void Delete(float);
};
void tree::insertnode(float val)
{
    node *nptr = root, *parent = nullptr;
    node *child = new node(val);
    if (!nptr)
    {
        root = child;
        header = new node(-99);
        header->right = header;
        header->left = root;
        root->left = header;
        root->right = header;
        return;
    }

    while (1)
    {
        parent = nptr;
        if (val < parent->data)
        {
            if (parent->lthread == 1)
                nptr = nptr->left;
            else
            {
                child->left = parent->left;
                child->right = parent;
                parent->lthread = 1;
                parent->left = child;
                return;
            }
        }
        else if (val > parent->data)
        {
            if (parent->rthread == 1)
                nptr = nptr->right;
            else
            {
                child->left = parent;
                child->right = parent->right;
                parent->rthread = 1;
                parent->right = child;
                return;
            }
        }
    }
}
void tree::inorder()
{
    node *ptr = root;
    if (!ptr)
    {
        cout << "no binary threaded tree found" << endl;
        return;
    }
    // Reach leftmost node
    while (ptr->lthread == 1)
        ptr = ptr->left;
    // One by one print successors
    while (ptr != header)
    {
        cout << ptr->data << " ";
        ptr = insuc(ptr);
    }
    cout << endl;
}
node *tree::insuc(node *nptr)
{
    // If rthread is set, we can quickly find
    if (nptr->rthread == 0)
        return nptr->right;
    // Else return leftmost child of right subtree
    nptr = nptr->right;
    while (nptr->lthread == 1)
        nptr = nptr->left;
    return nptr;
}
node *tree::inpred(node *nptr)
{
    // If lthread is set, we can quickly find
    if (nptr->lthread == 0)
        return (nptr->left);
    // Else return rightmost child of lefts subtree
    nptr = nptr->left;
    while (nptr->rthread == 1)
        nptr = nptr->right;
    return nptr;
}
void tree::preorder()
{
    if (!root)
    {
        cout << "\nEmpty tree" << endl;
        return;
    }
    node *ptr = root;
    while (ptr != header)
    {
        cout << ptr->data << " ";
        if (ptr->lthread == 1)
            ptr = ptr->left;
        else if (ptr->rthread == 1)
            ptr = ptr->right;
        else
        {
            while (ptr != header && ptr->rthread != 1)
                ptr = ptr->right;
            if (ptr != header)
                ptr = ptr->right;
        }
    }
}
void tree::Delete(float val)
{
    node *nptr = root, *parent = nullptr;
    bool flag = 0;
    while (nptr != header)
    {
        if (val == nptr->data)
        {
            flag = 1;
            break;
        }
        parent = nptr;
        if (val < parent->data)
        {
            if (nptr->lthread == 1)
                nptr = nptr->left;
            else
                break;
        }
        else if (val > parent->data)
        {
            if (nptr->rthread == 1)
                nptr = nptr->right;
            else
                break;
        }
    }
    if (!flag)
        cout << "No data found" << endl;
    else if (nptr->lthread == 1 and nptr->rthread == 1)
        bothchild(parent, nptr);
    else if (nptr->lthread == 1 or nptr->rthread == 1)
        onechild(parent, nptr);
    else
        nochild(parent, nptr);
}
void tree::nochild(node *par, node *child)
{
    if (par == nullptr)
        return;
    else if (child == par->left)
    {
        par->lthread = 0;
        par->left = child->left;
    }
    else // (child == par->right)
    {
        par->rthread = 0;
        par->right = child->right;
    }
    delete child;
}
void tree::onechild(node *par, node *child)
{
    node *son; // child of node to be deleted ie child's child
    if (child->lthread == 1)
        son = child->left;
    else
        son = child->right;

    if (par == nullptr)
        return;
    else if (child == par->left)
    {
        par->left = son;
        son->left = child->left;
    }
    else if (child == par->right)
    {
        par->right = son;
        son->right = child->right;
    }

    node *suc = insuc(child);
    node *pre = inpred(child);
    if (child->lthread == 1)
        pre->right = suc;
    if (child->rthread == 1)
        suc->left = pre;

    delete child;
}
void tree::bothchild(node *par, node *child)
{
    node *parsuc = child, *suc = child->right;
    while (suc->lthread != 0)
    {
        parsuc = suc;
        suc = suc->left;
    }
    float temp = suc->data;
    if (suc->rthread == 0 and suc->lthread == 0)
        nochild(parsuc, suc);
    else
        onechild(parsuc, suc);
    child->data = temp;
}
int main()
{
    tree bst;
    int n, choice;
    float data;
    char ch;
    while (1)
    {
        cout << "\n1.Create TBST" << endl;
        cout << "2.Insert in TBST" << endl;
        cout << "3.Delete from TBST" << endl;
        cout << "4.Display TBST" << endl;
        cout << "5.Exit" << endl;
        cout << "\nEnter the choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            cout << "Enter the number of elements: ";
            cin >> n;
            for (int i = 0; i < n; i++)
            {
                cout << "Enter the data to be inserted: ";
                cin >> data;
                bst.insertnode(data);
            }
            break;
        case 2:
            cout << "Enter the data to be inserted: ";
            cin >> data;
            bst.insertnode(data);
            break;
        case 3:
            cout << "Enter the data to be deleted: ";
            cin >> data;
            bst.Delete(data);
            break;
        case 4:
            cout << "\na.Inorder" << endl;
            cout << "b.Preorder" << endl;
            cout << "\nEnter the choice: ";
            cin >> ch;
            switch (ch)
            {
            case 'a':
                bst.inorder();
                break;
            case 'b':
                bst.preorder();
                break;
            default:
                cout << "Enter the correct char!" << endl;
                break;
            }
            break;
        case 5:
            exit(1);
        default:
            cout << "Enter the correct operation" << endl;
            break;
        }
    }
    return 0;
}