#include <iostream>
#include <string>
// max vertices we can handle can be 20
#define MAX 20
using namespace std;
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
    int vertices;     // vertices present in graph

public:
    graph()
    {
        for (int i = 0; i < MAX; i++)
            visited[i] = 0;
        for (int i = 0; i < MAX; i++)
            G[i] = nullptr;
        vertices = 0;
    }
    // Function to set vertices in graph
    void setVertices()
    {
        cout << "Enter the number of Vertices: ";
        cin >> vertices;
    }
    // Function to insert edges in graph
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
    // Function to create graph ie for inserting vertices
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
    // Calculating out degree of vertex
    int outdegree(int ver)
    {
        int count = 0;

        node *ptr = G[ver];
        while (ptr != nullptr)
        {
            count++;
            ptr = ptr->next;
        }
        return count;
    }
    // Calculting in degree of vertex
    int indegree(int ver)
    {
        int count = 0;
        for (int i = 0; i < vertices; i++)
        {
            node *ptr = G[i];
            while (ptr != nullptr)
            {
                if (ptr->vertex == ver)
                    count++;
                ptr = ptr->next;
            }
        }
        return count;
    }
    // Checking for connected graph
    void connected()
    {
        for (int i = 0; i < vertices; i++)
        {
            node *ptr = G[i];
            while (ptr != nullptr)
            {
                visited[i] = 1;
                if (visited[ptr->vertex] == 0)
                    visited[ptr->vertex] = 1;
                ptr = ptr->next;
            }
        }
        for (int i = 0; i < vertices; i++)
        {
            if (visited[i] == 0)
            {
                cout << "Not connected" << endl;
                return;
            }
        }
        cout << "Connected Graph" << endl;
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
        cout << "4.Indegree of vertices" << endl;
        cout << "5.Outdegree of vertices" << endl;
        cout << "6.Check for connected graph" << endl;
        cout << "7.Exit" << endl;
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
            cout << "Enter the edge: ";
            cin >> v1;
            cout << "\nIndegree of vertex: " << g.indegree(v1) << endl;
            break;
        case 5:
            cout << "Enter the edge: ";
            cin >> v1;
            cout << "\nOutdegree of vertex: " << g.outdegree(v1) << endl;
            break;
        case 6:
            g.connected();
            break;
        case 7:
            exit(1);
        default:
            cout << "Enter the correct operation!!" << endl;
            break;
        }
    }
    return 0;
}