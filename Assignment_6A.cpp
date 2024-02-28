#include <iostream>
#include <string>
#define MAX 20
using namespace std;
class stack
{
private:
    int arr[20];
    int topptr;

public:
    stack() : topptr(-1) {}
    void push(int x)
    {
        arr[++topptr] = x;
    }
    int top()
    {
        return arr[topptr];
    }
    void pop()
    {
        if (topptr == 1)
            topptr = -1;
        else
            topptr--;
    }
    int empty()
    {
        return topptr == -1;
    }
};
class queue
{
private:
    int arr[20];
    int frontptr, rear;

public:
    queue() : frontptr(-1), rear(-1) {}
    void push(int x)
    {
        if (frontptr == -1)
            frontptr = 0;
        arr[++rear] = x;
    }
    int front()
    {
        return arr[frontptr];
    }
    void pop()
    {
        if (frontptr == rear)
            frontptr = rear = -1;
        else
            frontptr++;
    }
    int empty()
    {
        return rear == -1;
    }
};
class node
{
private:
    int vertex;
    node *next;

public:
    node(int v = 0, node *nt = nullptr) : vertex(v), next(nt) {}
    friend class graph;
};
class graph
{
private:
    node *G[MAX];     // header to list
    int visited[MAX]; // for traversal
    int vertices;

public:
    graph()
    {
        for (int i = 0; i < MAX; i++)
            visited[i] = 0;
        for (int i = 0; i < MAX; i++)
            G[i] = nullptr;
        vertices = 0;
    }
    void setVertices()
    {
        int n;
        cout << "Enter the number of Vertices: ";
        cin >> n;
        vertices = n;
    }
    void insert(int u, int v)
    {
        node *temp = new node(v);
        if (G[u] == nullptr)
            G[u] = temp;
        else
        {
            node *ptr = G[u];
            while (ptr->next != nullptr)
                ptr = ptr->next;
            ptr->next = temp;
        }
    }
    void create_graph()
    {
        int edges;
        int u, v;
        cout << "Enter the number of edges: ";
        cin >> edges;
        for (int i = 0; i < edges; i++)
        {
            cout << "Enter the edge(V1,V2): ";
            cin >> u >> v;
            insert(u, v);
        }
    }
    void DFS(int ver)
    {
        stack s;
        for (int i = 0; i < MAX; i++)
            visited[i] = 0;

        s.push(ver);
        visited[ver] = 1;
        while (!s.empty())
        {
            int val = s.top();
            s.pop();
            cout << val << " ";
            node *ptr = G[val];
            while (ptr != nullptr)
            {
                if (visited[ptr->vertex] == 0)
                {
                    s.push(ptr->vertex);
                    visited[ptr->vertex] = 1;
                }
                ptr = ptr->next;
            }
        }
        cout << endl;
    }
    void BFS(int ver)
    {
        queue q;
        for (int i = 0; i < MAX; i++)
            visited[i] = 0;

        q.push(ver);
        visited[ver] = 1;
        while (!q.empty())
        {
            int val = q.front();
            q.pop();
            cout << val << " ";
            node *ptr = G[val];
            while (ptr != nullptr)
            {
                if (visited[ptr->vertex] == 0)
                {
                    q.push(ptr->vertex);
                    visited[ptr->vertex] = 1;
                }
                ptr = ptr->next;
            }
        }
        cout << endl;
    }
};
int main()
{
    graph g;
    int choice, v1, v2;
    while (1)
    {
        cout << "\n1.Set vertices" << endl;
        cout << "2.Create Graph" << endl;
        cout << "3.Insert edges in Graph" << endl;
        cout << "4.DFS Traversal of Graph" << endl;
        cout << "5.BFS traversal of Graph" << endl;
        cout << "6.Exit" << endl;
        cout << "\nEnter the choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            g.setVertices();
            break;
        case 2:
            g.create_graph();
            break;
        case 3:
            cout << "Enter the edge(V1,V2): ";
            cin >> v1 >> v2;
            g.insert(v1, v2);
            break;
        case 4:
            cout << "Enter the starting vertex: ";
            cin >> v1;
            g.DFS(v1);
            break;
        case 5:
            cout << "Enter the starting vertex: ";
            cin >> v1;
            g.BFS(v1);
            break;
        case 6:
            exit(1);
        default:
            cout << "Enter the correct operation!!" << endl;
            break;
        }
    }
    return 0;
}