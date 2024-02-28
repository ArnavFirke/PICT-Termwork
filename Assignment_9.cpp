#include <iostream>
#include <string>
using namespace std;
int max(int a, int b)
{
    return (a > b) ? a : b;
}
class Node
{
private:
    string data;
    string meaning;
    Node *left, *right;
    int height;

public:
    Node(string dt = "", string mem = "", int h = 0, Node *lt = nullptr, Node *rt = nullptr)

    {
        data = dt;
        meaning = mem;
        height = h;
        left = lt;
        right = rt;
    }
    friend class tree;
};
// Class implementation of AVL tree
class tree
{
private:
    Node *root;
    int height(Node *);

public:
    tree() : root(nullptr) {}
    Node *getroot()
    {
        return root;
    }
    Node *insert(Node *, string, string);
    Node *rightRotate(Node *);
    Node *leftRotate(Node *);
    int getBalance(Node *);
    void search(string);
    void update(string);
    Node *deleteNode(Node *, string);
    void acending(Node *);
    void decending(Node *);
    void preorder(Node *);
    void print();
    Node *minValueNode(Node *node)
    {
        Node *current = node;
        // Find the leftmost leaf node
        while (current->left != NULL)
            current = current->left;

        return current;
    }
};
int tree::height(Node *node)
{
    if (node == NULL)
        return 0;
    return node->height;
}
// Function to perform a right rotation
Node *tree::rightRotate(Node *nptr)
{
    Node *ltree = nptr->left;
    Node *rchild = ltree->right;

    // Perform rotation
    ltree->right = nptr;
    nptr->left = rchild;

    // Update heights
    nptr->height = max(height(nptr->left), height(nptr->right)) + 1;
    ltree->height = max(height(ltree->left), height(ltree->right)) + 1;

    // Return new root
    return ltree;
}

// Function to perform a left rotation
Node *tree::leftRotate(Node *nptr)
{
    Node *rtree = nptr->right;
    Node *lchild = rtree->left;

    // Perform rotation
    rtree->left = nptr;
    nptr->right = lchild;

    // Update heights
    nptr->height = max(height(nptr->left), height(nptr->right)) + 1;
    rtree->height = max(height(rtree->left), height(rtree->right)) + 1;

    // Return new root
    return rtree;
}

// Function to get the balance factor of a node
int tree::getBalance(Node *node)
{
    if (node == NULL)
        return 0;
    return height(node->left) - height(node->right);
}

// Function to insert a node in the tree
Node *tree::insert(Node *node, string key, string mean)
{
    if (node == NULL)
    {
        if (!root)
            root = new Node(key, mean);
        else
            return new Node(key, mean);
        return root;
    }
    if (key < node->data)
        node->left = insert(node->left, key, mean);
    else if (key > node->data)
        node->right = insert(node->right, key, mean);
    else
        return node;

    // Update the height of the ancestor node
    node->height = 1 + max(height(node->left), height(node->right));

    // Get the balance factor of the node
    int balance = getBalance(node);

    // If the node is unbalanced, there are four cases

    // Left Left Case
    if (balance > 1 && key < node->left->data)
        return rightRotate(node);

    // Right Right Case
    if (balance < -1 && key > node->right->data)
        return leftRotate(node);

    // Left Right Case
    if (balance > 1 && key > node->left->data)
    {
        node->left = leftRotate(node->left);
        return rightRotate(node);
    }

    // Right Left Case
    if (balance < -1 && key < node->right->data)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }

    // Return the unchanged node pointer
    return node;
}

// Function to print tree values
void tree::print()
{
    cout << "a.Acending" << endl;
    cout << "b.Decending" << endl;
    cout << "c.preorder" << endl;
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
    case 'c':
        preorder(root);
        break;
    default:
        cout << "Enter correct char" << endl;
        break;
    }
}

// Function to display the tree in inorder traversal
void tree::acending(Node *nptr)
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
void tree::decending(Node *nptr)
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
void tree::preorder(Node *nptr)
{
    if (!nptr)
        return;
    else
    {
        cout << nptr->data << ": " << nptr->meaning << endl;
        preorder(nptr->left);
        preorder(nptr->right);
    }
}

// Function to update value
void tree::update(string val)
{
    Node *nptr = root, *parent = nullptr;
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

// Function to search value
void tree::search(string val)
{
    Node *nptr = root, *parent = nullptr;
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
Node *tree::deleteNode(Node *root, string key)
{
    // Perform standard BST delete
    if (root == NULL)
        return root;
    // If the key to be deleted is smaller than the root's key,
    // then it lies in the left subtree
    if (key < root->data)
        root->left = deleteNode(root->left, key);

    // If the key to be deleted is greater than the root's key,
    // then it lies in the right subtree
    else if (key > root->data)
        root->right = deleteNode(root->right, key);

    // If the key to be deleted is equal to the root's key, then this is the node to be deleted
    else
    {
        // Node with only one child or no child
        if ((root->left == NULL) || (root->right == NULL))
        {
            Node *temp = root->left ? root->left : root->right;

            // No child case
            if (temp == NULL)
            {
                temp = root;
                root = NULL;
            }
            else               // One child case
                *root = *temp; // Copy the contents of the non-empty child

            free(temp);
        }
        else
        {
            // Node with two children
            Node *temp = minValueNode(root->right);            // Get the inorder successor
            root->data = temp->data;                           // Copy the inorder successor's key to this node
            root->right = deleteNode(root->right, temp->data); // Delete the inorder successor
        }
    }

    // If the tree had only one node, then return
    if (root == NULL)
        return root;

    // Update the height of the current node
    root->height = 1 + max(height(root->left), height(root->right));

    // Get the balance factor of the node
    int balance = getBalance(root);

    // If the node is unbalanced, there are four cases

    // Left Left Case
    if (balance > 1 && getBalance(root->left) >= 0)
        return rightRotate(root);

    // Left Right Case
    if (balance > 1 && getBalance(root->left) < 0)
    {
        root->left = leftRotate(root->left);
        return rightRotate(root);
    }

    // Right Right Case
    if (balance < -1 && getBalance(root->right) <= 0)
        return leftRotate(root);

    // Right Left Case
    if (balance < -1 && getBalance(root->right) > 0)
    {
        root->right = rightRotate(root->right);
        return leftRotate(root);
    }

    // Return the unchanged node pointer
    return root;
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
                bst.insert(bst.getroot(), data, mem);
            }
            break;
        case 2:
            cout << "\nEnter the data :";
            cin >> data;
            cout << "Enter the data meaning :";
            cin >> mem;
            bst.insert(bst.getroot(), data, mem);
            break;
        case 3:
            cout << "\nEnter the data to delete:";
            cin >> data;
            bst.deleteNode(bst.getroot(), data);
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
