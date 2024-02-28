#include <iostream>
#include <algorithm>
using namespace std;
template <typename T>
class Sorting
{
public:
    static void selection_sort(T arr[], int size)
    {
        int i, j, min_index;
        for (i = 0; i < size - 1; i++)
        {
            min_index = i;
            for (j = i + 1; j < size; j++)
            {
                if (arr[j] < arr[min_index])
                    min_index = j;
                if (min_index != i)
                    swap(arr[min_index], arr[i]);
            }
        }
    }
};

template <typename T>
void Display(T arr[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        cout << arr[i] << ' ';
    }
    cout << endl;
}

int main()
{
    int intsize;
    int floatsize;
    cout << "Enter size for int array: ";
    cin >> intsize;

    int intarr[intsize];
    for (int i = 0; i < intsize; ++i)
    {
        cin >> intarr[i];
    }
    cout << "\nEnter size for float array: ";
    cin >> floatsize;

    float floatarr[floatsize];
    for (int i = 0; i < floatsize; ++i)
    {
        cin >> floatarr[i];
    }

    cout << "\nINT ARRAY" << endl;
    Display<int>(intarr, intsize);

    cout << "Sorted Array" << endl;

    Sorting<int>::selection_sort(intarr, intsize);
    
    cout << "After Sorting" << endl;
    Display<int>(intarr, intsize);

    cout << "\nFLOAT ARRAY" << endl;
    Display<float>(floatarr, floatsize);
    cout << "Sorted Array" << endl;
    Sorting<float>::selection_sort(floatarr, floatsize);
    cout << "After Sorting" << endl;
    Display<float>(floatarr, floatsize);

    return 0;
}
