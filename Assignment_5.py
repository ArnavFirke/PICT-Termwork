import numpy as np


class sort():
    def insertion(self, a):
        print("Using Insertion sort:")
        for i in range(1, a.size):
            temp = a[i]
            j = i-1
            while j >= 0 and a[j] > temp:
                a[j+1] = a[j]
                j -= 1
            a[j+1] = temp
        return a

    def shell(self, a):
        print("Using Shell sort:")
        gap = a.size//2
        while gap >= 1:
            for j in range(gap, n):
                i = j-gap
                while i >= 0:
                    if a[i+gap] > a[i]:
                        break
                    else:
                        a[i], a[i+gap] = a[i+gap], a[i]
                    i -= gap
            gap = gap//2
        return a


print("""Operations are
    1.Add Array
    2.Insertion Sort
    3.Shell short
    4.exit""")
while (True):
    m = int(input("Enter the operation number:"))
    if m == 1:
        n = int(input("Enter the number of elements:"))
        arr = np.zeros((n), dtype=float)
        for i in range(n):
            arr[i] = float(input("Enter the element:"))

        obj = sort()
    elif m == 2:
        iarr = obj.insertion(arr)
        print("The sorted array is:\n", iarr)

    elif m == 3:
        sarr = obj.shell(arr)
        print("The sorted array is:\n", sarr)
        print("Top 5 scores are:")
        for k in range(sarr.size-1, sarr.size-6, -1):
            print(sarr[k])

    elif m == 4:
        print("Exited successfully")
        break
    else:
        print("Enter vaild operation")
