#include <iostream>
#include <string>
#include <climits>
#define MAX 15
using namespace std;
class Spanning_Tree
{
    int graph[MAX][MAX];
    int vertices, edges;
    int parent[MAX];

public:
    Spanning_Tree()
    {
        vertices = 0;
        edges = 0;
        for (int i = 0; i < vertices; i++)
            for (int j = 0; j < vertices; j++)
                graph[i][j] = 0;
    }
    void setVertices()
    {
        cout << "Enter the number of Vertices: ";
        cin >> vertices;
        cout << "Enter the number of Edges: ";
        cin >> edges;
    }
    void createGraph()
    {
        int v = vertices;
        for (int i = 0; i < edges; i++)
        {
            int a, b, w;
            cout << "Enter the the 2 vertices of edge " << endl;
            cin >> a >> b;
            cout << "Enter the weight of edge" << endl;
            cin >> w;
            graph[a][b] = graph[b][a] = w;
        }
    }
    // find the vertex with minimum key value, from the set of vertices
    // not yet included in MST
    int minKey(int key[], bool mstSet[])
    {
        int min = INT_MAX, min_index;
        for (int v = 0; v < vertices; v++)
            if (mstSet[v] == false && key[v] < min)
                min = key[v], min_index = v;
        return min_index;
    }
    void primMST()
    {
        // Key values used to pick minimum weight edge in cut
        int key[vertices];

        // To represent set of vertices included in MST
        bool mstSet[vertices];

        for (int i = 0; i < vertices; i++)
            key[i] = INT_MAX, mstSet[i] = false;

        // Always include first 1st vertex in MST.
        key[0] = 0;

        // First node is always root of MST
        parent[0] = -1;

        for (int count = 0; count < vertices - 1; count++)
        {

            // Pick the minimum key vertex from the
            // set of vertices not yet included in MST
            int u = minKey(key, mstSet);

            // Add the picked vertex to the MST Set
            mstSet[u] = true;

            for (int v = 0; v < vertices; v++)
                if (graph[u][v] && mstSet[v] == false && graph[u][v] < key[v])
                    parent[v] = u, key[v] = graph[u][v];
        }

        printMST(parent);
    }
    void printMST(int parent[])
    {
        int wt = 0;
        cout << "Edge \tWeight\n";
        for (int i = 1; i < vertices; i++)
        {
            wt += graph[i][parent[i]];
            cout << parent[i] << " - " << i << " \t"
                 << graph[i][parent[i]] << " \n";
        }
        cout << "Weight is: " << wt << endl;
    }
};

int main()
{
    Spanning_Tree g, mst;
    int choice, v1, v2, w;
    while (1)
    {
        cout << "\n1.Set vertices" << endl;
        cout << "2.Create Graph" << endl;
        cout << "3.Create Spanning tree" << endl;
        cout << "4.Exit" << endl;
        cout << "\nEnter the choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            g.setVertices();
            break;
        case 2:
            g.createGraph();
            break;
        case 3:
            g.primMST();
            break;
        case 4:
            exit(1);
        default:
            cout << "Enter the correct operation!!" << endl;
            cin.ignore(1000, '\n');
            cin.clear();
            break;
        }
    }
    return 0;
}