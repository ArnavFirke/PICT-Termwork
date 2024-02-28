import numpy as np
class sort():
    def partition(self, a, lb, ub):
        start = lb
        end = ub
        pivot = a[lb]
        while (start < end):
            while (start <= ub and a[start] <= pivot):
                start += 1

            while (end >= lb and a[end] > pivot):
                end -= 1

            if (start < end):
                a[start], a[end] = a[end], a[start]

        a[lb], a[end] = a[end], a[lb]    # Very Imp Step
        return end

    def quicksort(self, a, lb, ub):
        if (lb < ub):
            loc = self.partition(a, lb, ub)
            self.quicksort(a, lb, loc-1)
            self.quicksort(a, loc+1, ub)
        return a

n = int(input("Enter the number of elements:"))
arr = np.zeros((n), dtype=float)
for i in range(n):
    arr[i] = float(input("Enter the element:"))

obj = sort()
qarr = obj.quicksort(arr, 0, arr.size-1)


print("The sorted array is:\n", qarr)
# for k in range(qarr.size-1, qarr.size-6, -1):
#     print(qarr[k])
