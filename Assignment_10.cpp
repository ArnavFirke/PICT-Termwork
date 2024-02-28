#include <iostream>
using namespace std;

class HeapSort
{
private:
    int *arr; // Pointer to array
    int size; // Size of the array

    void heapify(int n, int i)
    {
        int largest = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        // Find the largest element among root, left child, and right child
        if (left < n && arr[left] > arr[largest])
            largest = left;

        if (right < n && arr[right] > arr[largest])
            largest = right;

        // If the largest element is not the root, swap them and heapify the affected subtree
        if (largest != i)
        {
            swap(arr[i], arr[largest]);
            heapify(n, largest);
        }
    }

public:
    HeapSort(int inputArr[], int arrSize)
    {
        size = arrSize;
        arr = new int[size];
        for (int i = 0; i < size; i++)
            arr[i] = inputArr[i];
    }

    void sort()
    {
        int n = size;

        // Build a max heap by heapifying internal nodes in reverse order
        for (int i = n / 2 - 1; i >= 0; i--)
            heapify(n, i);

        // Extract elements from the heap one by one and heapify the reduced heap
        for (int i = n - 1; i >= 0; i--)
        {
            swap(arr[0], arr[i]);
            heapify(i, 0);
        }
    }

    void printArray()
    {
        for (int i = 0; i < size; i++)
            cout << arr[i] << " ";
        cout << endl;
    }
};

int main()
{
    int choice;
    int size;

    cout << "Enter the size of the array: ";
    cin >> size;

    int arr[size];
    cout << "Enter the elements of the array:" << endl;
    for (int i = 0; i < size; i++)
    {
        cin >> arr[i];
    }

    HeapSort heap(arr, size);

    while (true)
    {
        cout << "********** Heap Sort Menu **********" << endl;
        cout << "1. Sort Array" << endl;
        cout << "2. Print Sorted Array" << endl;
        cout << "3. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice)
        {
        case 1:
            heap.sort();
            cout << "Array sorted successfully!" << endl;
            break;

        case 2:
            cout << "Sorted array: ";
            heap.printArray();
            break;

        case 3:
            cout << "Exiting the program." << endl;
            return 0;

        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    }

    return 0;
}
