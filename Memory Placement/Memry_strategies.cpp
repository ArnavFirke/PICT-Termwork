#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Strategies
{
private:
    int block, process;
    vector<int> BlockSize, BlockSize2;
    vector<int> ProcessSize;
    vector<int> allocation;

public:
    void getdata()
    {
        int temp;
        cout << "Enter the no. of Block: ";
        cin >> block;
        cout << "Enter the Block size : ";
        for (int i = 0; i < block; i++)
        {
            cin >> temp;
            BlockSize.push_back(temp);
            BlockSize2.push_back(temp);
        }
        cout << "Enter the no. of Process: ";
        cin >> process;
        cout << "Enter the Process Sizes: ";
        for (int i = 0; i < process; i++)
        {
            cin >> temp;
            ProcessSize.push_back(temp);
        }
        allocation.resize(process);
        for (int i = 0; i < process; i++)
            allocation[i] = -1;
    }
    void reinit()
    {
        int j = 0;
        for (int i : BlockSize2)
            BlockSize[j++] = i;
        for (int i = 0; i < process; i++)
            allocation[i] = -1;
    }
    void Worstfit()
    {
        for (int i = 0; i < process; i++)
        {
            int wstIdx = -1;
            for (int j = 0; j < block; j++)
            {
                if (BlockSize[j] >= ProcessSize[i])
                {
                    if (wstIdx == -1)
                        wstIdx = j;
                    else if (BlockSize[wstIdx] < BlockSize[j])
                        wstIdx = j;
                }
            }
            if (wstIdx != -1)
            {
                allocation[i] = wstIdx;
                BlockSize[wstIdx] -= ProcessSize[i];
            }
        }
        display();
        reinit();
    }
    void Bestfit()
    {

        for (int i = 0; i < process; i++)
        {
            int bestIdx = -1;
            for (int j = 0; j < block; j++)
            {
                if (BlockSize[j] >= ProcessSize[i])
                {
                    if (bestIdx == -1)
                        bestIdx = j;
                    else if (BlockSize[bestIdx] > BlockSize[j])
                        bestIdx = j;
                }
            }
            if (bestIdx != -1)
            {
                allocation[i] = bestIdx;
                BlockSize[bestIdx] -= ProcessSize[i];
            }
        }
        display();
        reinit();
    }
    void Firstfit()
    {

        for (int i = 0; i < process; i++)
        {
            int fstIdx = -1;
            for (int j = 0; j < block; j++)
            {
                if (BlockSize[j] >= ProcessSize[i])
                {
                    fstIdx = j;
                    break;
                }
            }
            if (fstIdx != -1)
            {
                allocation[i] = fstIdx;
                BlockSize[fstIdx] -= ProcessSize[i];
            }
        }
        display();
        reinit();
    }
    void Nextfit()
    {
        int j = 0, t = block - 1;
        for (int i = 0; i < process; i++)
        {
            // Do not start from beginning
            while (j < block)
            {
                if (BlockSize[j] >= ProcessSize[i])
                {
                    allocation[i] = j;
                    BlockSize[j] -= ProcessSize[i];

                    t = (j - 1) % block;
                    break;
                }
                if (t == j)
                {
                    t = (j - 1) % block;
                    break;
                }
                j = (j + 1) % block;
            }
        }
        display();
        reinit();
    }
    void display()
    {
        cout << "\nProcess No.\tProcess Size\tBlock no.\n";
        for (int i = 0; i < process; i++)
        {
            cout << "   " << i + 1 << "\t\t" << ProcessSize[i] << "\t\t";
            if (allocation[i] != -1)
                cout << allocation[i] + 1;
            else
                cout << "Not Allocated";
            cout << endl;
        }
    }
};
int main()
{
    Strategies st;
    int choice;
    while (true)
    {
        cout << "1.Enter data for block and process" << endl;
        cout << "2.Best fit" << endl;
        cout << "3.worst fit" << endl;
        cout << "4.first fit" << endl;
        cout << "5.next fit" << endl;
        cout << "6.Exit" << endl;
        cout << "\nEnter the choice: ";
        cin >> choice;
        switch (choice)
        {
        case 1:
            st.getdata();
            break;
        case 2:
            st.Bestfit();
            break;
        case 3:
            st.Worstfit();
            break;
        case 4:
            st.Firstfit();
            break;
        case 5:
            st.Nextfit();
            break;
        case 6:
            return 0;
        default:
            break;
        }
    }
    return 0;
}