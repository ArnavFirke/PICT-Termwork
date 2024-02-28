#include <iostream>
#include <climits>
using namespace std;
class OptimalBST
{
private:
    double *keys;
    double *probabilities;
    int n;

    // Function to calculate the sum of probabilities in a given range
    double sumOfProbabilities(int start, int end)
    {
        double sum = 0.0;
        for (int i = start; i <= end; i++)
            sum += probabilities[i];
        return sum;
    }

public:
    // Constructor
    OptimalBST(double keys[], double probabilities[], int n)
    {
        this->keys = new double[n];
        this->probabilities = new double[n];
        this->n = n;
        for (int i = 0; i < n; i++)
        {
            this->keys[i] = keys[i];
            this->probabilities[i] = probabilities[i];
        }
    }

    // Function to construct an optimal BST given the probabilities
    // of successful searches for keys and failure searches
    void constructOptimalBST()
    {
        // Create a 2D array to store the computed costs
        double cost[n + 1][n + 1];

        // Initialize cost[i][i] as the probability of key[i]
        for (int i = 0; i < n; i++)
            cost[i][i] = probabilities[i];

        // Compute the cost for all subtrees of size 2 to n
        for (int subtreeSize = 2; subtreeSize <= n; subtreeSize++)
        {
            for (int i = 0; i <= n - subtreeSize + 1; i++)
            {
                int j = i + subtreeSize - 1;
                cost[i][j] = INT_MAX;

                // Try making each key in the range i to j as the root
                for (int root = i; root <= j; root++)
                {
                    // Calculate the cost when keys[root] becomes the root
                    double leftSubtreeCost = (root > i) ? cost[i][root - 1] : 0;
                    double rightSubtreeCost = (root < j) ? cost[root + 1][j] : 0;
                    double currentCost = leftSubtreeCost + rightSubtreeCost + sumOfProbabilities(i, j);

                    // Update the minimum cost if currentCost is less
                    if (currentCost < cost[i][j])
                        cost[i][j] = currentCost;
                }
            }
        }

        // Display the minimum cost
        cout << "Optimal BST constructed with minimum cost: " << cost[0][n - 1] << endl;
    }

    // Function to display the keys along with their left and right children
    void displayArray()
    {
        for (int i = 0; i < n; i++)
        {
            cout << "Key: " << keys[i] << endl;

            if (i > 0)
                cout << "Left Child: " << keys[i - 1] << endl;
            else
                cout << "Left Child: NULL" << endl;

            if (i < n - 1)
                cout << "Right Child: " << keys[i + 1] << endl;
            else
                cout << "Right Child: NULL" << endl;

            cout << "------------------------" << endl;
        }
    }
};
int main()
{
    int option;
    int n;
    double *keys;
    double *probabilities;
    OptimalBST *bst = nullptr; // Declare the pointer outside the switch statement

    while (true)
    {
        cout << "------ Optimal BST Menu ------" << endl;
        cout << "1. Create Optimal BST" << endl;
        cout << "2. Display Optimal BST" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your option: ";
        cin >> option;

        switch (option)
        {
        case 1:
            // Create Optimal BST
            cout << "Enter the number of keys: ";
            cin >> n;

            keys = new double[n];
            probabilities = new double[n];

            cout << "Enter the keys: ";
            for (int i = 0; i < n; i++)
                cin >> keys[i];

            cout << "Enter the probabilities: ";
            for (int i = 0; i < n; i++)
                cin >> probabilities[i];

            // Construct Optimal BST
            if (bst != nullptr)
            {
                delete bst; // Delete the previous bst if it exists
            }
            bst = new OptimalBST(keys, probabilities, n);
            bst->constructOptimalBST();

            delete[] keys;
            delete[] probabilities;
            break;

        case 2:
            // Display Optimal BST
            if (bst != nullptr)
            {
                cout << "Optimal BST:" << endl;
                bst->displayArray();
            }
            else
            {
                cout << "Optimal BST is not yet created." << endl;
            }
            break;

        case 3:
            // Exit the program
            cout << "Exiting..." << endl;
            delete bst; // Delete the bst before exiting
            return 0;

        default:
            cout << "Invalid option. Please try again." << endl;
            break;
        }

        cout << endl;
    }
}
/*

double keys[] = {10, 12, 20, 25, 30};
double probabilities[] = {0.15, 0.1, 0.05, 0.1, 0.2};


Keys array:
Key: 10
Right Child: 12
------------------------
Key: 12
Left Child: 10
Right Child: 20
------------------------
Key: 20
Left Child: 12
Right Child: 25
------------------------
Key: 25
Left Child: 200.1
Right Child: 30
------------------------
Key: 30
Left Child: 25
Right Child: NULL
------------------------
Optimal BST constructed with minimum cost: 1.3 */