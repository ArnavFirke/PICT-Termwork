#include <iostream>
#include <string>
// #include <bits/stdc++.h>
using namespace std;
class node;
class stack
{
private:
    int top;
    node *arr[50];

public:
    stack() : top(-1) {}
    void push(node *ele)
    {
        arr[++top] = ele;
    }
    node *pop()
    {
        return arr[top--];
    }
    node *getTop()
    {
        return arr[top];
    }
    bool empty()
    {
        return top == -1 ? 1 : 0;
    }
};
class queue
{
private:
    int front, rear;
    node *arr[25];

public:
    queue() : front(-1), rear(-1) {}
    void push(node *ptr)
    {
        if (front == -1)
            front = 0;
        arr[++rear] = ptr;
    }
    node *pop()
    {
        node *temp = arr[front];
        if (front == rear)
            front = rear = -1;
        else
            front++;
        return temp;
    }
    bool empty()
    {
        return rear == -1 ? 1 : 0;
    }
};
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
    void nrec_inorder(node *);
    void nrec_preorder(node *);
    void nrec_postorder(node *);

public:
    tree() : root(nullptr) {}
    node *getroot()
    {
        return root;
    }
    void insert();
    void swapped(node *);
    int height(node *);
    int leafcount(node *);
    int intcount(node *);
    void delete_all(node *);
    void search(float);
    void minmax();
    void display();
    node *copy(node *);
    void operator=(tree);
};
void tree::insert()
{
    int val;
    if (!root)
    {
        cout << "Enter the value of root:";
        cin >> val;
        root = new node(val);
        return;
    }
    queue q;
    q.push(root);
    while (!q.empty())
    {
        node *temp = q.pop();
        if (temp->left != nullptr)
            q.push(temp->left);
        else
        {
            cout << "Enter the value of left child of " << temp->data << " (-1 for NULL): ";
            cin >> val;
            if (val != -1)
            {
                temp->left = new node(val);
            }
        }
        if (temp->right != nullptr)
            q.push(temp->right);
        else
        {
            cout << "Enter the value of right child of " << temp->data << " (-1 for NULL): ";
            cin >> val;
            if (val != -1)
            {
                temp->right = new node(val);
            }
        }
    }
}
void tree::inorder(node *nptr)
{
    if (!nptr)
    {
        return;
    }
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
    {
        return;
    }
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
    {
        return;
    }
    else
    {
        postorder(nptr->left);
        postorder(nptr->right);
        cout << nptr->data << " ";
    }
}
void tree::nrec_inorder(node *nptr)
{
    stack s;
    while (1)
    {
        while (nptr != nullptr)
        {
            s.push(nptr);
            nptr = nptr->left;
        }
        if (s.empty())
            return;
        nptr = s.pop();
        cout << nptr->data << " ";
        nptr = nptr->right;
    }
}
void tree::nrec_preorder(node *nptr)
{
    stack s;
    while (1)
    {
        while (nptr != nullptr)
        {
            cout << nptr->data << " ";
            if (nptr->right != nullptr)
                s.push(nptr->right);
            nptr = nptr->left;
        }
        if (s.empty())
            return;
        nptr = s.pop();
    }
}
// void tree::nrec_postorder(node *nptr)
// {
//     stack s;
//     node *t = new node(-1);
//     node *temp = t;
//     while (1)
//     {
//         while (nptr != nullptr)
//         {
//             s.push(nptr);
//             if (nptr->right != nullptr)
//             {
//                 s.push(nptr->right);
//                 s.push(t);
//             }
//             nptr = nptr->left;
//         }
//         if (s.empty())
//             return;
//         // if (!nptr and nptr->data != -1)
//         //     cout << nptr->data << " ";
//         nptr = s.getTop();
//         // s.pop();
//         while ((nptr->data != t->data) and !(s.empty()))
//         {
//             nptr = s.getTop();
//             s.pop();
//             cout << nptr->data << " ";
//         }
//     }
// }
void tree::nrec_postorder(node *nptr)
{
    if (root == nullptr)
        return;

    stack s1, s2;
    s1.push(root);

    while (!s1.empty())
    {
        node *curr = s1.pop();
        s2.push(curr);

        if (curr->left)
            s1.push(curr->left);

        if (curr->right)
            s1.push(curr->right);
    }

    while (!s2.empty())
    {
        node *curr = s2.pop();
        cout << curr->data << " ";
    }
}
void tree::display()
{
    cout << "a.Inorder" << endl;
    cout << "b.preorder" << endl;
    cout << "c.postorder" << endl;
    cout << "d.Non recursive Inorder" << endl;
    cout << "e.Non recursive preorder" << endl;
    cout << "f.Non recursive postorder" << endl;
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
    case 'd':
        nrec_inorder(root);
        break;
    case 'e':
        nrec_preorder(root);
        break;
    case 'f':
        nrec_postorder(root);
        break;

    default:
        cout << "Enter correct char" << endl;
        break;
    }
}
int tree::height(node *nptr)
{
    if (!nptr)
        return 0;
    else
    {
        int l_height = height(nptr->left);
        int r_height = height(nptr->right);
        if (l_height >= r_height)
            return l_height + 1;
        else
            return r_height + 1;
    }
}
void tree::swapped(node *nptr)
{
    if (!nptr)
        return;
    swapped(nptr->left);
    swapped(nptr->right);
    node *temp = nptr->left;
    nptr->left = nptr->right;
    nptr->right = temp;
}
int tree::leafcount(node *nptr)
{
    static int leaf;
    if (!nptr)
        return 0;
    else
    {
        if (nptr->left == nullptr and nptr->right == nullptr)
            leaf++;
        leafcount(nptr->left);
        leafcount(nptr->right);
    }
    return leaf;
}
int tree::intcount(node *nptr)
{
    static int internal;
    if (!nptr)
        return 0;
    else
    {
        if (nptr->left != nullptr or nptr->right != nullptr)
            internal++;
        intcount(nptr->left);
        intcount(nptr->right);
    }
    return internal - 1; // root is not internal
}
void tree::operator=(tree tree1)
{
    this->root = copy(tree1.root);
}
void tree::delete_all(node *nptr)
{
    if (!nptr)
        return;
    else
    {
        delete_all(nptr->left);
        delete_all(nptr->right);
        if (nptr == root)
            root = nullptr;
        // nptr = nullptr;
        free(nptr);
        return;
    }
}
node *tree::copy(node *ptr)
{
    if (!ptr)
        return nullptr;
    else
    {
        node *temp = new node(ptr->data, copy(ptr->left), copy(ptr->right));
        return temp;
    }
}
int main()
{
    tree bst, bst2;
    int n, choice, h, lf, it;
    float data;
    while (1)
    {
        cout << "\n1.Insert in BST" << endl;
        cout << "2.copy BST" << endl;
        cout << "3.display BST" << endl;
        cout << "4.swap func of ptr in BST" << endl;
        cout << "5.display height of BST" << endl;
        cout << "6.Number of leaves and internal nodes" << endl;
        cout << "7.Delete whole tree" << endl;
        cout << "8.Exit" << endl;
        cout << "\nEnter the operation: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            bst.insert();
            break;
        case 2:
            bst2 = bst;
            cout << "For bst2 :" << endl;
            bst2.display();
            break;
        case 3:
            bst.display();
            cout << endl;
            break;
        case 4:
            bst.swapped(bst.getroot());
            break;
        case 5:
            h = bst.height(bst.getroot());
            cout << "Height of BSt is: " << h << endl;
            break;
        case 6:
            lf = bst.leafcount(bst.getroot());
            it = bst.intcount(bst.getroot());
            cout << "No. of leaf nodes in BSt are: " << lf << endl;
            cout << "No. of internal nodes in BSt are: " << it << endl;
            break;
        case 7:
            bst.delete_all(bst.getroot());
            break;
        case 8:
            cout << "Exited successfully" << endl;
            exit(1);
        default:
            cout << "Enter the correct operation!!" << endl;
        }
    }
    return 0;
}