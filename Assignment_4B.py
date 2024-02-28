import numpy as np

fib=np.array((),dtype=int)
a,b=0,1
for i in range(50):
    fib=np.append(fib,a)
    a,b=b,a+b
    
class Search():
    def sort(self,a):
        for i in range(a.size):
            for j in range((a.size)-i-1): 
                if a[j] > a[j+1]:
                    a[j], a[j+1] = a[j+1], a[j]
        return a
                    
    def binary(self,a,k):
        print("Using Binary Search:")
        low=0
        high=(a.size)-1
        while low<=high:
            mid=(low+high)//2
            if(a[mid]==k):
                print(f"The element is found at {mid}th index\n")
                break
            elif a[mid]<k:
                low=mid+1
            elif a[mid]>k:
                high=mid-1
    
    def rbin(self,low,high,k):
        mid=(low+high)//2
        if arr[mid]==k:
            # print(f"The element is found at {mid}th index")
            return mid
        elif arr[mid]<k:
            return self.rbin(mid+1,high,k)
        elif arr[mid]>k:
            return self.rbin(low,mid-1,k)               
         
    def fibonacci(self,a,k):
        print("Using Fibonacci Search:")
        j=0
        while fib[j]<a.size:  
           j+=1
        off=-1
        while j>1:
            i = min(off+fib[j-2], a.size-1)
            if k==a[i]:
                return i
            elif k>a[i]:
                j=j-1
                off=i
            else:
                j=j-2

        if a[a.size-1] ==k:
            return a.size -1
        else:
            return -1 

    def fibonaccianSearch(self,arr, x, n):
        print("Using Fibonacci Search:")  
        fibMMm2 = 0  
        fibMMm1 = 1
        fibM = fibMMm2 + fibMMm1  

        while (fibM < n):
            fibMMm2 = fibMMm1
            fibMMm1 = fibM
            fibM = fibMMm2 + fibMMm1
            
        offset = -1
    
        while (fibM > 1):
            i = min(offset+fibMMm2, n-1)
            if (arr[i] < x):
                fibM = fibMMm1
                fibMMm1 = fibMMm2
                fibMMm2 = fibM - fibMMm1
                offset = i
    
            elif (arr[i] > x):
                fibM = fibMMm2
                fibMMm1 = fibMMm1 - fibMMm2
                fibMMm2 = fibM - fibMMm1
 
            else:
                return i
    
        if(fibMMm1 and arr[n-1] == x):
            return n-1
    
        return -1
            
            
print("""Operations are
    1.Add Array  
    2.Binary Search
    3.Fibonacci Search
    4.exit""")
while(True):
    m=int(input("Enter the operation number:"))
    if m==1:
        n=int(input("\nEnter the number of elements:"))
        arr=np.zeros((n),dtype=int)
        for i in range(n):
            arr[i]=int(input("Enter the element:"))

        obj=Search()
        arr=obj.sort(arr)
        print("The sorted array is:\n",arr)
        ser=int(input("Enter the element you want to search:")) 
        print("\n")
         
    elif m==2:
        obj.binary(arr,ser)
        print(f"The element is found at {obj.rbin(0,arr.size-1,ser)}th index\n")
        
    elif m==3:
        print(f"element is at {obj.fibonaccianSearch(arr,ser,(arr.size))}th index\n")
        print(f"element is at {obj.fibonacci(arr,ser)}th index\n")
        
    elif m==4:
        print("Exited successfully")
        break  
    else:
        print("Enter valid operation")